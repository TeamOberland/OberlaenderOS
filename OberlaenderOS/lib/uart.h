/*
 * uart.h
 *
 *  Created on: 12.06.2013
 *      Author: Manuel
 */

#ifndef UART_LIB_H_
#define UART_LIB_H_

#define UART_DRIVER_INIT 0x01

#define UART_PROTOCOL_BAUDRATE_16X115_2 0x001A
//250kbit
#define UART_PROTOCOL_BAUDRATE_DMX      0x00D
#define UART_PROTOCOL_NB_STOP_1         0x0
#define UART_PROTOCOL_NB_STOP_2         0x1
#define UART_PROTOCOL_PARITY_NONE       0x0
#define UART_FLOW_CONTROL_DISABLE_FLAG  0x0
#define UART_PROTOCOL_DATA_LENGTH_5     0x0
#define UART_PROTOCOL_DATA_LENGTH_6     0x1
#define UART_PROTOCOL_DATA_LENGTH_7     0x2
#define UART_PROTOCOL_DATA_LENGTH_8     0x3

/* UART Mode Select */
#define UART_MDR1_MODE_SELECT_16X          0x000
#define UART_MDR1_MODE_SELECT_SIR          0x001
#define UART_MDR1_MODE_SELECT_16X_AUTOBAUD 0x002
#define UART_MDR1_MODE_SELECT_13X          0x003
#define UART_MDR1_MODE_SELECT_MIR          0x004
#define UART_MDR1_MODE_SELECT_FIR          0x005
#define UART_MDR1_MODE_SELECT_CIR          0x006
#define UART_MDR1_MODE_SELECT_DISABLE      0x007


#define UART_DEVICE_INIT 0x01

/*
 * UART protocol format
 */
typedef struct uart_protocol_format_t {
    uint32_t baudrate;
    uint8_t datalength;
    uint8_t stopbit;
    uint8_t parity;
    uint8_t flowControl;
} uart_protocol_format_t;

/*
 * UART RS232 configuration
 * BAUD RATE: 115200
 * DATA: 8 bit
 * PARITY: none
 * STOP: 1bit
 * FLOW CONTROL: none (Critical)
 */

static struct uart_protocol_format_t uart_protocol_rs232 = {
        UART_PROTOCOL_BAUDRATE_16X115_2,
  UART_PROTOCOL_DATA_LENGTH_8,
  UART_PROTOCOL_NB_STOP_1,
  UART_PROTOCOL_PARITY_NONE,
  UART_FLOW_CONTROL_DISABLE_FLAG
};

static struct uart_protocol_format_t uart_protocol_dmx = {
  UART_PROTOCOL_BAUDRATE_DMX,
  UART_PROTOCOL_DATA_LENGTH_7,
  UART_PROTOCOL_NB_STOP_2,
  UART_PROTOCOL_PARITY_NONE,
  UART_FLOW_CONTROL_DISABLE_FLAG
};


#endif /* UART_LIB_H_ */
