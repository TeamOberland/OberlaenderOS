/*
 * uart.h
 *
 *  Created on: 29.05.2013
 *      Author: Manuel
 */

#ifndef UART_H_
#define UART_H_

#include "../../../../lib/types.h"
#include "../../../genarch/uart/uart.h"


/*
 * UART module base addresses
 * Size 1 Kb
 * OMAP35x s:2740
 */
#define UART1 0x4806A000 /* UART only */
#define UART2 0x4806C000 /* UART only */
#define UART3 0x49020000 /* UART, IrDA, CIR */


/*
 * UART Registers offset
 * 8 bit width
 */
#define UART_DLL_REG        0x000 /* RW */
#define UART_RHR_REG        0x000 /* R FIFO read */
#define UART_THR_REG        0x000 /* W FIFO transmission */
#define UART_DLH_REG        0x004 /* RW */
#define UART_IER_REG        0x004 /* RW */

#define UART_MVR_REG        0x050 /* R */
#define UART_SYSC_REG       0x054 /* RW */
#define UART_SYSS_REG       0x058 /* R */
#define UART_WER_REG        0x05C /* RW */

#define UART_MDR1_REG       0x020 /* RW Mode Definition CIR/IrDA */
#define UART_LSR_REG        0x014 /* R */

#define UART_LSR_RX_FIFO_E  0 /* 0 BIT */
#define UART_LSR_TX_FIFO_E  5 /* 5 BIT */
#define UART_LSR_TX_SR_E    6 /* 6 BIT */

/* UART LCR register bits*/
#define UART_LCR_CHAR_LEN_0 0 /* 0 and 1 bit */
#define UART_LCR_CHAR_LEN_1 1
#define UART_LCR_NB_STOP    2
#define UART_LCR_PARITY_EN  3
#define UART_LCR_PARITY_T1  4
#define UART_LCR_PARITY_T2  5
#define UART_LCR_BREAK_EN   6
#define UART_LCR_DIV_EN     7

#define UART_EFR_REG        0x008 /* RW */

/*PDF: 2752*/
/*no parity configuration mode 8bits word length*/
//#define UART_LCR_MODE_CONFIG  0x083
#define UART_LCR_MODE_CONFIG 0x00BF

/* for configuration */
#define UART_LCR_REG        0x00C /* RW */





void omap_uart_software_reset(uint8_t uartPort);
inline uint32_t omap_uart_get_baseadress(uint8_t uartPort);
inline void omap_uart_waitfor_resetdone(uint8_t uartPort);
inline void omap_uart_set_mode(uint8_t uartPort,uint32_t mode);
void omap_uart_load_configuration(uint8_t uartPort,uint8_t uart_mode, uart_protocol_format_t configuration);



#endif
