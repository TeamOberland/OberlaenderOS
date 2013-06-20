/*
 * dmx_driver.h
 *
 *  Created on: 19.06.2013
 *      Author: Manuel
 */

#ifndef dmx_DRIVER_H_
#define dmx_DRIVER_H_

#include <oos/types.h>
#include "../uart/uart_driver.h"
#include "../../kernel/generic/driver/driver.h"
#include "../../kernel/genarch/uart/uart.h"
#include "../shared/driver_shared.h"


void dmx_driver_init(void);
int16_t dmx_driver_open(device_id_t device);
int16_t dmx_driver_close(device_id_t device);
int16_t dmx_driver_read(device_id_t device, void* buffer, uint32_t count);
int16_t dmx_driver_write(device_id_t device, void* buffer, uint32_t count);
int32_t dmx_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg);

#define DMX_DRIVER_ID 0x0005
extern driver_t dmx_driver;


#endif /* dmx_DRIVER_H_ */
