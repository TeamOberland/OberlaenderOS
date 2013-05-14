/*
 * timer.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef TIMER_OMAP3530_H_
#define TIMER_OMAP3530_H_

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


/* Technical Reference Manual, Chapter 16 - Timers */

#define GPTIMER_COUNT 11
#define GPTIMER_FREQUENCY 32.768 /* kHz */

/*
 * GPTIMER Base addresses according to Technical Reference Manual (page 2632)
 */
#define GPTIMER1_BASE  0x48318000
#define GPTIMER2_BASE  0x49032000
#define GPTIMER3_BASE  0x49034000
#define GPTIMER4_BASE  0x49036000
#define GPTIMER5_BASE  0x49038000
#define GPTIMER6_BASE  0x4903A000
#define GPTIMER7_BASE  0x4903C000
#define GPTIMER8_BASE  0x4903E000
#define GPTIMER9_BASE  0x49040000
#define GPTIMER10_BASE 0x48086000
#define GPTIMER11_BASE 0x48088000

/*
 * Register offsets according to Technical Reference Manual (page 2633)
 */
#define GPTIMER_TIDR        0x000 /**< This register contains the IP revision code. */
#define GPTIMER_TIOCP_CFG   0x010 /**< This register controls the various parameters of the GP timer L4 interface. */
#define GPTIMER_TISTAT      0x014 /**< This register provides status information about the module, excluding the interrupt status information. */
#define GPTIMER_TISR        0x018 /**< This register shows which interrupt events are pending inside the module. */
#define GPTIMER_TIER        0x01C /**< This register controls (enable/disable) the interrupt events. */
#define GPTIMER_TWER        0x020 /**< This register controls (enable/disable) the wake-up feature on specific interrupt events. */
#define GPTIMER_TCLR        0x024 /**< This register controls optional features specific to the timer functionality. */
#define GPTIMER_TCRR        0x028 /**< This register holds the value of the internal counter. */
#define GPTIMER_TLDR        0x02C /**< This register holds the timer load values. */
#define GPTIMER_TTGR        0x030 /**< This register triggers a counter reload of timer by writing any value in it. */
#define GPTIMER_TWPS        0x034 /**< This register indicates if a Write-Posted is pending. */
#define GPTIMER_TMAR        0x038 /**< This register holds the value to be compared with the counter value. */
#define GPTIMER_TCAR1       0x03C /**< This register holds the first captured value of the counter register. */
#define GPTIMER_TSICR       0x040 /**< This register contains the bits that control the interface between the L4 interface and functional clock domains-posted mode and functional SW reset. */
#define GPTIMER_TCAR2       0x044 /**< This register holds the second captured value of the counter register */
#define GPTIMER_TPIR        0x048 /**<
                                   * This register is used for 1 ms tick generation. The TPIR register holds the value of the positive
                                   * increment. The value of this register is added with the value of the TCVR to define whether next
                                   * value loaded in TCRR will be the sub-period value or the over-period value.
                                   */
#define GPTIMER_TNIR        0x04C /**<
                                   * This register is used for 1 ms tick generation. The TNIR register holds the value of the negative
                                   * increment. The value of this register is added with the value of the TCVR to define whether next
                                   * value loaded in TCRR will be the sub-period value or the over-period value.
                                   */
#define GPTIMER_TCVR        0x050 /**<
                                   * This register is used for 1 ms tick generation. The TCVR register defines whether next value loaded
                                   * in TCRR will be the sub-period value or the over-period value.
                                   */
#define GPTIMER_TOCR        0x054 /**< This register is used to mask the tick interrupt for a selected number of ticks. */
#define GPTIMER_TOWR        0x058 /**< This register holds the number of masked overflow interrupts. */

#endif /* TIMER_H_ */
