/*
 * gpio_driver.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "../../lib/types.h"
#include "../../kernel/generic/driver/driver.h"

void gpio_driver_init(void);
int16_t gpio_driver_open(device_id_t device);
int16_t gpio_driver_close(device_id_t device);
int16_t gpio_driver_read(device_id_t device, void* buffer, uint32_t count);
int16_t gpio_driver_write(device_id_t device, void* buffer, uint32_t count);
int32_t gpio_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg);

#define MAX_GPIO_DEVICES 255
#define GPIO_DRIVER_ID 0x0001
extern driver_t gpio_driver;

#define GPIO_DRV_IOCTL_SET_DIR 1
#define GPIO_DRV_IOCTL_DIR_OUT 0
#define GPIO_DRV_IOCTL_DIR_IN 1


typedef struct {
    bool_t used;
    device_id_t device;
    uint32_t gpio;
} registered_gpio_t;




#endif /* GPIO_DRIVER_H_ */
