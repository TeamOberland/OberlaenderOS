/*
 * gpio_driver.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "../lib/types.h"
#include "../kernel/generic/driver/driver.h"

void gpio_driver_init(void);
int16_t gpio_driver_open(device_id_t device);
int16_t gpio_driver_close(device_id_t device);
int16_t gpio_driver_read(device_id_t device, void* buffer, uint32_t count);
int16_t gpio_driver_write(device_id_t device, void* buffer, uint32_t count);

#define MAX_GPIO_DEVICES 255
extern driver_t gpio_driver;

typedef struct {
    bool_t used;
    device_id_t device;
    uint32_t gpio;
    bool_t output;
} registered_gpio_t;




#endif /* GPIO_DRIVER_H_ */
