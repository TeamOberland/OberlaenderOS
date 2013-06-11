/*
 * gpio.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef GPIO_API_H_
#define GPIO_API_H_

#include "types.h"

// NOTE: Copied from gpio_driver.h
#define GPIO_DRV_IOCTL_SET_DIR 1
#define GPIO_DRV_IOCTL_DIR_OUT 0
#define GPIO_DRV_IOCTL_DIR_IN 1

device_id_t api_gpio_export(uint32_t gpio);


#endif /* GPIO_H_ */
