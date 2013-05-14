/*
 * display.c
 *
 *  Created on: 07.05.2013
 *      Author: Daniel
 */

#include "../../../genarch/display/display.h"
#include "../interrupts/timer.h"


//#define DSS_BASE 0x48050000
//#define DSS_SYSCONFIG 0x010
//#define DSS_CONTROL 0x040
//
//#define DSS_VENC_OUT_SEL (1<<6)
//#define DSS_DAC_POWERDN_BGZ (1<<5)
//#define DSS_DAC_DEMEN (1<<4)
//#define DSS_VENC_CLOCK_4X_ENABLE (1<<3)
//
//
//
//#define DISPC_BASE 0x48050400
//
//#define DISPC_REVISION 0x000
//#define DISPC_SYSCONFIG 0x010
//#define DISPC_SYSSTATUS 0x014
//#define DISPC_IRQSTATUS 0x018
//#define DISPC_IRQENABLE 0x01C
//#define DISPC_CONTROL 0x040
//#define DISPC_CONFIG 0x044
//#define DISPC_DEFAULT_COLOR(m) (0x04C+((m) * 0x04))
//#define DISPC_TRANS_COLOR(m) (0x054+((m) * 0x04))
//#define DISPC_LINE_STATUS 0x05C
//#define DISPC_LINE_NUMBER 0x060
//#define DISPC_TIMING_H 0x064
//#define DISPC_TIMING_V 0x068
//#define DISPC_POL_FREQ 0x06C
//#define DISPC_DIVISOR 0x070
//#define DISPC_GLOBAL_ALPHA 0x074
//#define DISPC_SIZE_DIG 0x078
//#define DISPC_SIZE_LCD 0x07C
//#define DISPC_GFX_BAj (0x080+((j) * 0x04))
//#define DISPC_GFX_POSITION 0x088
//#define DISPC_GFX_SIZE 0x08C
//#define DISPC_GFX_ATTRIBUTES 0x0A0
//#define DISPC_GFX_FIFO_THRESHOLD 0x0A4
//#define DISPC_GFX_FIFO_SIZE_STATUS 0x0A8
//#define DISPC_GFX_ROW_INC 0x0AC
//#define DISPC_GFX_PIXEL_INC 0x0B0
//#define DISPC_GFX_WINDOW_SKIP 0x0B4
//#define DISPC_GFX_TABLE_BA 0x0B8
//#define DISPC_DATA_CYCLE(k) (0x1D4+((k) * 0x04))
//#define DISPC_CPR_COEF_R 0x220
//#define DISPC_CPR_COEF_G 0x224
//#define DISPC_CPR_COEF_B 0x228
//#define DISPC_GFX_PRELOAD 0x22C
//
//inline memory_mapped_io_t omap_display_get_register(uint32_t offset)
//{
//    return (memory_mapped_io_t)(DISPC_BASE + offset);
//}
//
//void __display_init()
//{
//    *(omap_display_get_register(DISPC_IRQENABLE)) = 0x00000;
//    *(omap_display_get_register(DISPC_IRQSTATUS)) = 0x1FFFF;
//
//    //
//    // initialize pixel clock to 72MHz
//    *((memory_mapped_io_t)(Clock_Control_Reg_CM + CM_CLKSEL2_PLL)) = (432 << 8) | 12;
//    *((memory_mapped_io_t)(Clock_Control_Reg_CM + CM_CLKEN_PLL)) = 0x00370037;
//
//    //
//    // Display subsystem initialization
//    *((memory_mapped_io_t)(DSS_CM + CM_CLKSEL_DSS)) = (16 << 8) | 12;
//    *((memory_mapped_io_t)(DSS_BASE + DSS_SYSCONFIG)) = 0x01;
//    *((memory_mapped_io_t)(DSS_BASE + DSS_CONTROL)) = DSS_VENC_OUT_SEL | DSS_DAC_POWERDN_BGZ | DSS_DAC_DEMEN | DSS_VENC_CLOCK_4X_ENABLE;
//
//
//}
