/*
 * video_driver.h
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#ifndef VIDEO_DRIVER_H_
#define VIDEO_DRIVER_H_

#include "bitmap.h"
#include <oos/types.h>
#include <oos/video.h>
#include "../../kernel/generic/driver/driver.h"


#define VIDEO_RESOLUTION_WIDTH 1024
#define VIDEO_RESOLUTION_HEIGHT 768

#define VIDEO_BPP 4
#define VIDEO_FRAMEBUFFER_SIZE (VIDEO_RESOLUTION_HEIGHT*VIDEO_RESOLUTION_WIDTH*VIDEO_BPP)

// hbp - horizontal back porch
// hfp - horizontal front porch
// hsw - horizontal synchronization pulse width

// vbp - vertical back porch
// vfp - vertical front porch
// vsw - vertical synchronization pulse width

// didv - dispc divisor
// dsdv - dss divisor

#define VIDEO_MODE(w,h,hbp,hfp,hsw,vbp,vfp,vsw, didv, dsdv) \
		{ w,h, ((h - 1) << 16) | (w - 1), \
		(hbp << DISPCB_HBP) | (hfp << DISPCB_HFP) | (hsw << DISPCB_HSW), \
		(vbp << DISPCB_VBP) | (vfp << DISPCB_VFP) | (vsw << DISPCB_VSW), \
		didv, dsdv }

typedef struct {
    uint16_t width;
    uint16_t height;
    uint32_t sizeLcd;
    uint32_t timingH;
    uint32_t timingV;
    uint32_t dispcDivisor;
    uint32_t dssDivisor;
} videomode_t;


void video_driver_init(void);
int16_t video_driver_open(device_id_t device);
int16_t video_driver_close(device_id_t device);
int16_t video_driver_read(device_id_t device, void* buffer, uint32_t count);
int16_t video_driver_write(device_id_t device, void* buffer, uint32_t count);
int32_t video_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg);

//
// omap3530
//

#define DISPC_BASE              0x48050400

#define DISPC_SYSCONFIG         (0x0010)
    #define DISPC_MIDLEMODE_FORCE (0x00 << 12)
    #define DISPC_MIDLEMODE_NEVER (0x01 << 12)
    #define DISPC_MIDLEMODE_SMART (0x01 << 13)

    #define DISPC_SIDLEMODE_FORCE (0x00 <<3)
    #define DISPC_SIDLEMODE_NEVER (0x01 << 3)
    #define DISPC_SIDLEMODE_SMART (0x01 << 4)

    #define DISPC_AUTOIDLE        (0x01 << 0)
    #define DISPC_SOFTRESET       (0x01 << 1)
    #define DISPC_ENWAKEUP        (0x01 << 2)

#define DISPC_SYSSTATUS         (0x0014)
#define DISPC_IRQSTATUS         (0x0018)
#define DISPC_IRQENABLE         (0x001C)
#define DISPC_CONTROL           (0x0040)
    #define DISPC_LCDENABLE           (0x01 << 0)
    #define DISPC_DIGITALENABLE       (0x01 << 1)
    #define DISPC_MONOCOLOR           (0x01 << 2)
    #define DISPC_STNTFT              (0x01 << 3)
    #define DISPC_M8B                 (0x01 << 4)
    #define DISPC_GOLCD               (0x01 << 5)
    #define DISPC_GODIGITAL           (0x01 << 6)
    #define DISPC_STDITHERENABLE      (0x01 << 7)
    #define DISPC_TFTDATALINES_12     (0x00 << 8)
    #define DISPC_TFTDATALINES_16     (0x01 << 8)
    #define DISPC_TFTDATALINES_18     (0x02 << 8)
    #define DISPC_TFTDATALINES_24     (0x03 << 8)
    #define DISPC_STALLMODE           (0x01 << 11)
    #define DISPC_OVERLAYOPTIMISATION (0x01 << 12)
    #define DISPC_GPIN0               (0x01 << 13)
    #define DISPC_GPIN1               (0x01 << 14)
    #define DISPC_GPOUT0              (0x01 << 15)
    #define DISPC_GPOUT1              (0x01 << 16)
    #define DISPC_PCKFREEENABLE       (0x01 << 27)
    #define DISPC_LCDENABLESIGNAL     (0x01 << 28)
    #define DISPC_LCDENABLEPOL        (0x01 << 29)
    #define DISPC_DITHER_FRAMES_0     (0x00 << 30)
    #define DISPC_DITHER_FRAMES_2     (0x01 << 30)
    #define DISPC_DITHER_FRAMES_4     (0x02 << 30)

#define DISPC_CONFIG            (0x0044)
    #define DISPC_PIXELGATED            (0x01 << 0)
    #define DISPC_LOADMODE_EVERY        (0x00 << 1)
    #define DISPC_LOADMODE_MANUAL       (0x01 << 1)
    #define DISPC_LOADMODE_FRAME        (0x02 << 1)
    #define DISPC_LOADMODE_FIRST        (0x03 << 1)
    #define DISPC_PALETTEGAMMATABLE     (0x01 << 3)
    #define DISPC_PIXELDATAGATED        (0x01 << 4)
    #define DISPC_PIXELCLOCKGATED       (0x01 << 5)
    #define DISPC_HSYNCGATED            (0x01 << 6)
    #define DISPC_VSYNCGATED            (0x01 << 7)
    #define DISPC_ACBIASGATED           (0x01 << 8)
    #define DISPC_FUNCGATED             (0x01 << 9)
    #define DISPC_TCKLCDENABLE          (0x01 << 10)
    #define DISPC_TCKLCDSELECTION       (0x01 << 11)
    #define DISPC_TCKDIGENABLE          (0x01 << 12)
    #define DISPC_TCKDIGSELECTION       (0x01 << 13)
    #define DISPC_FIFOMERGE             (0x01 << 14)
    #define DISPC_CPR                   (0x01 << 15)
    #define DISPC_FIFOHANDCHECK         (0x01 << 16)
    #define DISPC_FIFOFILLING           (0x01 << 17)
    #define DISPC_LCDALPHABLENDERENABLE (0x01 << 18)
    #define DISPC_TVALPHABLENDERENABLE  (0x01 << 19)

#define DISPC_DEFAULT_COLOR(m)  (0x004c + (m*0x04))
#define DISPC_TRANS_COLOR(m)    (0x0054 + (m*0x04))
#define DISPC_LINE_STATUS       (0x005C)
#define DISPC_LINE_NUMBER       (0x0060)
#define DISPC_TIMING_H          (0x0064)
    #define DISPCB_HSW 0
    #define DISPCB_HFP 8
    #define DISPCB_HBP 20

#define DISPC_TIMING_V          (0x0068)
    #define DISPCB_VSW 0
    #define DISPCB_VFP 8
    #define DISPCB_VBP 20

#define DISPC_POL_FREQ          (0x006C)
    #define DISPCB_POL_ACB      0
    #define DISPCB_POL_ACBI     8
    #define DISPC_POL_IVS       (0x01 << 12)
    #define DISPC_POL_IHS       (0x01 << 13)
    #define DISPC_POL_IPC       (0x01 << 14)
    #define DISPC_POL_IEO       (0x01 << 15)
    #define DISPC_POL_RF        (0x01 << 16)
    #define DISPC_POL_ONOFF     (0x01 << 17)

#define DISPC_DIVISOR           (0x0070)
    #define DISPCB_DIVISOR_PCD 0
    #define DISPCB_DIVISOR_LCD 16

#define DISPC_GLOBAL_ALPHA      (0x0074)
#define DISPC_SIZE_DIG          (0x0078)
#define DISPC_SIZE_LCD          (0x007C)

#define DISPC_GFX_BA(j)             (0x0080 + (j*0x04))
#define DISPC_GFX_POSITION          (0x0088)
#define DISPC_GFX_SIZE              (0x008C)
#define DISPC_GFX_ATTRIBUTES        (0x00A0)
    #define DISPC_GFXENABLE         (0x01 << 0)

    #define DISPC_GFXFORMAT_BITMAP1 (0  << 1)
    #define DISPC_GFXFORMAT_BITMAP2 (1  << 1)
    #define DISPC_GFXFORMAT_BITMAP4 (2  << 1)
    #define DISPC_GFXFORMAT_BITMAP8 (3  << 1)
    #define DISPC_GFXFORMAT_RGB12   (4  << 1)
    #define DISPC_GFXFORMAT_ARGB16  (5  << 1)
    #define DISPC_GFXFORMAT_RGB16   (6  << 1)
    #define DISPC_GFXFORMAT_RGB32   (8  << 1)
    #define DISPC_GFXFORMAT_RGB24   (9  << 1)
    #define DISPC_GFXFORMAT_ARGB32  (12 << 1)
    #define DISPC_GFXFORMAT_RGBA32  (13 << 1)
    #define DISPC_GFXFORMAT_RGBx    (14 << 1)

    #define DISPC_GFXREPLICATIONENABLE (1 << 5)

    #define DISPC_GFXBURSTSIZE_4x32  (0 << 6)
    #define DISPC_GFXBURSTSIZE_8x32  (1 << 6)
    #define DISPC_GFXBURSTSIZE_16x32 (2 << 6)

    #define DISPC_GFXCHANNELOUT     (1 << 8)
    #define DISPC_GFXNIBBLEMODE     (1 << 9)
    #define DISPC_GFXENDIANNESS     (1 << 10)
    #define DISPC_GFXFIFOPRELOAD    (1 << 11)

    #define DISPC_GFXROTATION_0     (0 << 12)
    #define DISPC_GFXROTATION_90    (1 << 12)
    #define DISPC_GFXROTATION_180   (2 << 12)
    #define DISPC_GFXROTATION_270   (3 << 12)

    #define DISPC_GFXARBITRATION    (1 << 14)
    #define DISPC_GFXSELFREFRESH    (1 << 15)

#define DISPC_GFX_FIFO_THRESHOLD    (0x00A4)
#define DISPC_GFX_FIFO_SIZE_STATUS  (0x00A8)
#define DISPC_GFX_ROW_INC           (0x00AC)
#define DISPC_GFX_PIXEL_INC         (0x00B0)
#define DISPC_GFX_WINDOW_SKIP       (0x00B4)
#define DISPC_GFX_TABLE_BA          (0x00B8)

#define DISPC_DATA_CYCLE(k)         (0x01D4 (k*0x04))
#define DISPC_CPR_COEF_R            (0x0220)
#define DISPC_CPR_COEF_G            (0x0224)
#define DISPC_CPR_COEF_B            (0x0228)
#define DISPC_GFX_PRELOAD           (0x022C)

#define DISPC_VIDn_BAj(n,j)            (0x00BC + ((n - 1) * 0x90) + (j * 0x04))
#define DISPC_VIDn_POSITION(n)         (0x00C4 + ((n - 1) * 0x90))
#define DISPC_VIDn_SIZE(n)             (0x00C8 + ((n - 1) * 0x90))
#define DISPC_VIDn_ATTRIBUTES(n)       (0x00CC + ((n - 1) * 0x90))
#define DISPC_VIDn_FIFO_THRESHOLD(n)   (0x00D0 + ((n - 1) * 0x90))
#define DISPC_VIDn_FIFO_SIZE_STATUS(n) (0x00D4 + ((n - 1) * 0x90))
#define DISPC_VIDn_ROW_INC(n)          (0x00D8 + ((n - 1) * 0x90))
#define DISPC_VIDn_PIXEL_INC(n)        (0x00DC + ((n - 1) * 0x90))
#define DISPC_VIDn_FIR(n)              (0x00E0 + ((n - 1) * 0x90))
#define DISPC_VIDn_PICTURE_SIZE(n)     (0x00E4 + ((n - 1) * 0x90))
#define DISPC_VIDn_ACCUl(n,l)          (0x00E8 + ((n - 1) * 0x90) + (l * 0x04))
#define DISPC_VIDn_FIR_COEF_Hi(n,i)    (0x00F0 + ((n - 1) * 0x90) + (i * 0x08))
#define DISPC_VIDn_FIR_COEF_HVi(n,i)   (0x00F4 + ((n - 1) * 0x90) + (i * 0x08))
#define DISPC_VIDn_CONV_COEF0(n)       (0x0130 + ((n - 1) * 0x90))
#define DISPC_VIDn_CONV_COEF1(n)       (0x0134 + ((n - 1) * 0x90))
#define DISPC_VIDn_CONV_COEF2(n)       (0x0138 + ((n - 1) * 0x90))
#define DISPC_VIDn_CONV_COEF3(n)       (0x013C + ((n - 1) * 0x90))
#define DISPC_VIDn_CONV_COEF4(n)       (0x0140 + ((n - 1) * 0x90))
#define DISPC_VIDn_FIR_COEF_Vi(n,i)    (0x01E0 + ((n - 1) * 0x20) + (i * 0x04))
#define DISPC_VIDn_PRELOAD(n)          (0x0230 + ((n - 1) * 0x04))





#define DISPC_REG(offset) (*((memory_mapped_io_t)(DISPC_BASE + offset)))

#define DSS_BASE 0x48050000

#define DSS_REVISIONNUMBER    (0x0000)

#define DSS_SYSCONFIG         (0x0010)
    #define DSS_AUTOIDLE                (0x01 << 0)
    #define DSS_SOFTRESET               (0x01 << 1)

#define DSS_SYSSTATUS         (0x0014)
    #define DSS_RESETDONE               (0x01 << 0)

#define DSS_IRQSTATUS         (0x0018)
    #define DSS_DISPC_IRQ               (0x01 << 0)
    #define DSS_DSI_IRQ                 (0x01 << 1)

#define DSS_CONTROL           (0x0040)
    #define DSS_DSS1_CLK_SWITCH         (0x01 << 0)
    #define DSS_DSI_CLK_SWITCH          (0x01 << 1)
    #define DSS_VENC_CLOCK_MODE         (0x01 << 2)
    #define DSS_VENC_CLOCK_4X_ENABLE    (0x01 << 3)
    #define DSS_DAC_DEMEN               (0x01 << 4)
    #define DSS_DAC_POWERDN_BGZ         (0x01 << 5)
    #define DSS_VENC_OUT_SEL            (0x01 << 6)


#define DSS_SDI_CONTROL       (0x0044)
#define DSS_PLL_CONTROL       (0x0048)
#define DSS_SDI_STATUS        (0x005C)

#define DSS_REG(offset) (*((memory_mapped_io_t)(DSS_BASE + offset)))

extern driver_t video_driver;

#endif /* VIDEO_DRIVER_H_ */
