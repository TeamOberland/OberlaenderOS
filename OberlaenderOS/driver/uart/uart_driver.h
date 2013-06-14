/*
 * uart_driver.h
 *
 *  Created on: 31.05.2013
 *      Author: Manuel
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_


#include "../../lib/types.h"
#include "../../lib/device.h"
#include "../../kernel/generic/driver/driver.h"
#include "../../kernel/genarch/uart/uart.h"

void uart_driver_init(void);
int16_t uart_driver_open(device_id_t device);
int16_t uart_driver_close(device_id_t device);
int16_t uart_driver_read(device_id_t device, void* buffer, uint32_t count);
int16_t uart_driver_write(device_id_t device, void* buffer, uint32_t count);
int32_t uart_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg);

#define MAX_UART_DEVICES 3
#define UART_DRIVER_ID 0x0002
extern driver_t uart_driver;

typedef struct {
    bool_t used;
    uint8_t uart_port;
    device_id_t device;
    bool_t initialized;
} registered_uart_t;

#endif /* UART_DRIVER_H_ */
