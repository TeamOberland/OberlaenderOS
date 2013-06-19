/*
 * video_driver.c
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#include "video_driver.h"
#include "../../kernel/arch/omap3530/interrupts/clocks.h"
#include "../../kernel/generic/driver/device_manager.h"
#include <oos/video.h>
#include <stdlib.h>
#include <string.h>

static videomode_t video_modes[] = {

        // 640x480@72Hz
        VIDEO_MODE(640, 480, 128, 24, 40, 28, 9, 3, 2, 14),
        // 800x600@60Hz
        VIDEO_MODE(800, 600, 88, 40, 128, 23, 1, 4, 2, 11),
        // 1024x768@60Hz
        VIDEO_MODE(1024, 768, 160, 24, 136, 29, 3, 6, 1, 13),
        // 1280x1024@60Hz
        VIDEO_MODE(1280, 1024, 248, 48, 112, 38, 1, 3, 1, 8) };

driver_t video_driver = { NULL, DEVICE_TYPE_VIDEO, video_driver_init, video_driver_open, video_driver_close, video_driver_read,
        video_driver_write, video_driver_ioctl };

static bitmap_t* framebuffer1;
static bitmap_t* framebuffer2;
static rastport_t* rastport;

static void omap3530_video_init(void)
{
    DISPC_REG(DISPC_IRQENABLE) = 0x00000;
    DISPC_REG(DISPC_IRQSTATUS) = 0x1FFFF;

    // initialize clocks
    *((memory_mapped_io_t) (Clock_Control_Reg_CM + CM_CLKSEL2_PLL)) = (432 << 8) | 12;
    *((memory_mapped_io_t) (Clock_Control_Reg_CM + CM_CLKEN_PLL)) = 0x00370037;
    *((memory_mapped_io_t) (DSS_CM + CM_CLKSEL)) = (16 << 8) | 6;

    // initialize display subsystem
    DSS_REG(DSS_SYSCONFIG) = DSS_AUTOIDLE;
    DSS_REG(DSS_CONTROL) = DSS_VENC_OUT_SEL | DSS_DAC_POWERDN_BGZ | DSS_DAC_DEMEN | DSS_VENC_CLOCK_4X_ENABLE;

    // initialize display controller
    DISPC_REG(DISPC_SYSCONFIG) = DISPC_MIDLEMODE_SMART | DISPC_SIDLEMODE_SMART | DISPC_ENWAKEUP | DISPC_AUTOIDLE;

    DISPC_REG(DISPC_CONFIG) = DISPC_LOADMODE_FRAME;

    DISPC_REG(DISPC_TRANS_COLOR(0)) = 0xFFFFFF;
    DISPC_REG(DISPC_TRANS_COLOR(1)) = 0x000000;

    DISPC_REG(DISPC_POL_FREQ) = DISPC_POL_IPC | DISPC_POL_IHS | DISPC_POL_IVS | (2 << DISPCB_POL_ACBI)
            | (8 << DISPCB_POL_ACB);

    DISPC_REG(DISPC_DIVISOR) = (1 << DISPCB_DIVISOR_LCD) | (2 << DISPCB_DIVISOR_PCD);
    DISPC_REG(DISPC_GFX_ATTRIBUTES) = 0;

    // TRM p.2319 (Table 15-47)
    DISPC_REG(DISPC_VIDn_CONV_COEF0(1)) = 296 | (409 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF1(1)) = 0 | (298 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF2(1)) = ((-208) & 0xffff) | (-100 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF3(1)) = 298 | (0 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF4(1)) = 517;

    DISPC_REG(DISPC_VIDn_CONV_COEF0(2)) = 296 | (409 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF1(2)) = 0 | (298 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF2(2)) = ((-208) & 0xffff) | (-100 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF3(2)) = 298 | (0 << 16);
    DISPC_REG(DISPC_VIDn_CONV_COEF4(2)) = 517;

    DISPC_REG(DISPC_CONTROL) = DISPC_GPOUT1 | DISPC_GPOUT0 | DISPC_TFTDATALINES_24 | DISPC_STDITHERENABLE | DISPC_GOLCD
            | DISPC_STNTFT | DISPC_LCDENABLE;

    while ((DISPC_REG(DISPC_CONTROL) & DISPC_GOLCD))
        ;
}

static void omap3530_video_set_resolution(uint16_t width, uint16_t height)
{
    uint32_t i;
    for (i = 0; i < (sizeof(video_modes) / sizeof(videomode_t)); i++)
    {
        if (video_modes[i].width == width && video_modes[i].height == height)
        {
            // TODO: Ensure the framebuffers are the same size

            DISPC_REG(DISPC_SIZE_LCD) = video_modes[i].sizeLcd;
            DISPC_REG(DISPC_TIMING_H) = video_modes[i].timingH;
            DISPC_REG(DISPC_TIMING_V) = video_modes[i].timingV;

            DISPC_REG(DISPC_DIVISOR) &= ~0xFFFF;
            DISPC_REG(DISPC_DIVISOR) |= video_modes[i].dispcDivisor;

            *((memory_mapped_io_t) (DSS_CM + CM_CLKSEL)) &= 0xFFFF;
            *((memory_mapped_io_t) (DSS_CM + CM_CLKSEL)) |= video_modes[i].dssDivisor;

            DISPC_REG(DISPC_CONTROL) &= ~DISPC_GOLCD;
            DISPC_REG(DISPC_CONTROL) |= DISPC_GOLCD;

            while ((DISPC_REG(DISPC_CONTROL) & DISPC_GOLCD))
                ;

            return;
        }
    }
}

static void omap3530_video_attach_framebuffer(bitmap_t* framebuffer)
{
    uint32_t videoSize;
    videoSize = DISPC_REG(DISPC_SIZE_LCD);

    // update the buffer info
    DISPC_REG(DISPC_GFX_BA(0)) = (uint32_t)framebuffer->data;
    DISPC_REG(DISPC_GFX_BA(1)) = (uint32_t)framebuffer->data;
    DISPC_REG(DISPC_GFX_POSITION) = 0x00000000;
    DISPC_REG(DISPC_GFX_SIZE) = videoSize;
    DISPC_REG(DISPC_GFX_FIFO_THRESHOLD) = (0x3ff << 16) | 0x3c0;
    DISPC_REG(DISPC_GFX_ROW_INC) = 1;
    DISPC_REG(DISPC_GFX_PIXEL_INC) = 1;
    DISPC_REG(DISPC_GFX_WINDOW_SKIP) = 0;
    DISPC_REG(DISPC_GFX_ATTRIBUTES) = DISPC_GFXFORMAT_RGBA32 | DISPC_GFXBURSTSIZE_16x32 | DISPC_GFXENABLE;

    // notify the hardware
    DISPC_REG(DISPC_CONTROL) &= ~DISPC_GOLCD;
    DISPC_REG(DISPC_CONTROL) |= DISPC_GOLCD;

    while(DISPC_REG(DISPC_CONTROL) & DISPC_GOLCD);

}

static void omap3530_video_driver_redraw(void)
{
    // do the doublebuffer!
    if(rastport->target == framebuffer1)
    {
        omap3530_video_attach_framebuffer(framebuffer1);
        memcpy(framebuffer2->data, framebuffer1->data, VIDEO_FRAMEBUFFER_SIZE);
        rastport->currentPixel = framebuffer2->data;
        rastport->target = framebuffer2;
    }
    else
    {
        omap3530_video_attach_framebuffer(framebuffer2);
        memcpy(framebuffer1->data, framebuffer2->data, VIDEO_FRAMEBUFFER_SIZE);
        rastport->currentPixel = framebuffer1->data;
        rastport->target = framebuffer1;
    }
}

static device_id_t video_main;
static bool_t video_main_isopen = FALSE;

void video_driver_init(void)
{
    // create frame buffers and drawing context
    framebuffer1 = malloc(sizeof(bitmap_t));
    framebuffer1->width = VIDEO_RESOLUTION_WIDTH;
    framebuffer1->height = VIDEO_RESOLUTION_HEIGHT;
    framebuffer1->format = BITMAP_FORMAT_ARGB32;
    framebuffer1->stride = VIDEO_RESOLUTION_WIDTH * (BITMAP_FORMAT_ARGB32_BPP/8);
    framebuffer1->data = malloc(VIDEO_FRAMEBUFFER_SIZE);
    memset(framebuffer1->data,0, VIDEO_FRAMEBUFFER_SIZE);

    framebuffer2 = malloc(sizeof(bitmap_t));
    framebuffer2->width = VIDEO_RESOLUTION_WIDTH;
    framebuffer2->height = VIDEO_RESOLUTION_HEIGHT;
    framebuffer2->format = BITMAP_FORMAT_ARGB32;
    framebuffer2->stride = VIDEO_RESOLUTION_WIDTH * (BITMAP_FORMAT_ARGB32_BPP/8);
    framebuffer2->data = malloc(VIDEO_FRAMEBUFFER_SIZE);
    memset(framebuffer2->data,0, VIDEO_FRAMEBUFFER_SIZE);

    rastport = malloc(sizeof(rastport_t));
    rastport->x = 0;
    rastport->y = 0;
    rastport->currentPixel = framebuffer1->data;
    rastport->target = framebuffer1;

    // setup video subsystem
    omap3530_video_init();

    omap3530_video_set_resolution(VIDEO_RESOLUTION_WIDTH, VIDEO_RESOLUTION_HEIGHT);

    omap3530_video_attach_framebuffer(framebuffer1);

    // register device
    video_main = device_manager_add_device(global_device_manager, &video_driver, NULL);
}

int16_t video_driver_open(device_id_t device)
{
    if (device != video_main)
    {
        return 1;
    }
    if (video_main_isopen)
    {
        return 1;
    }
    video_main_isopen = TRUE;
    return 0;
}

int16_t video_driver_close(device_id_t device)
{
    if (device != video_main)
    {
        return 1;
    }
    if (video_main_isopen)
    {
        video_main_isopen = FALSE;
        return 0;
    }
    return 1;
}

int16_t video_driver_read(device_id_t device, void* buffer, uint32_t count)
{
    if (device != video_main)
    {
        return -1;
    }
    return 0;
}

int16_t video_driver_write(device_id_t device, void* buffer, uint32_t count)
{
    if (device != video_main)
    {
        return -1;
    }

    video_element_t* elm = buffer;
    bool_t redraw = FALSE;
    int i;
    int elementCount = count / sizeof(video_element_t);
    for (i = 0; i < elementCount; i++)
    {
        rastport_draw(rastport, elm);
        if (elm->redraw)
        {
            redraw = TRUE;
        }
        elm++;
    }

    if (redraw)
    {
        omap3530_video_driver_redraw();
    }

    return 0;
}

int32_t video_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg)
{
    return 0;
}
