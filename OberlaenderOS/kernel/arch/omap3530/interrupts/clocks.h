/*
 * clocks.h
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#ifndef CLOCKS_H_
#define CLOCKS_H_

#define IVA2_CM                 0x48004000
#define OCP_System_Reg_CM       0x48004800
#define MPU_CM                  0x48004900
#define CORE_CM                 0x48004A00
#define SGX_CM                  0x48004B00
#define WKUP_CM                 0x48004C00
#define Clock_Control_Reg_CM    0x48004D00
#define DSS_CM                  0x48004E00
#define CAM_CM                  0x48004F00
#define PER_CM                  0x48005000
#define EMU_CM                  0x48005100
#define Global_Reg_CM           0x48005200
#define NEON_CM                 0x48005300
#define USBHOST_CM              0x48005400

#define CM_FCLKEN       0x0000
#define CM_ICLKEN       0x0010
#define CM_IDLEST       0x0020
#define CM_AUTOIDLE     0x0030
#define CM_CLKSEL       0x0040
#define CM_SLEEPDEP     0x0044
#define CM_CLKSTCTRL    0x0048
#define CM_CLKSTST      0x004C

#define CM_CLKEN_PLL 0x0000
#define CM_CLKEN2_PLL 0x0004
#define CM_IDLEST_CKGEN 0x0020
#define CM_IDLEST2_CKGEN 0x0024
#define CM_AUTOIDLE_PLL 0x0030
#define CM_AUTOIDLE2_PLL 0x0034
#define CM_CLKSEL1_PLL 0x0040
#define CM_CLKSEL2_PLL 0x0044
#define CM_CLKSEL3_PLL 0x0048
#define CM_CLKSEL4_PLL 0x004C
#define CM_CLKSEL5_PLL 0x0050
#define CM_CLKOUT_CTRL 0x0070

#define CM_CLKSEL_GPT2  0
#define CM_CLKSEL_GPT3  1
#define CM_CLKSEL_GPT4  2
#define CM_CLKSEL_GPT5  3
#define CM_CLKSEL_GPT6  4
#define CM_CLKSEL_GPT7  5
#define CM_CLKSEL_GPT8  6
#define CM_CLKSEL_GPT9  7

#endif /* CLOCKS_H_ */
