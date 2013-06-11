/*
 * gpio.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "gpio.h"
#include "syscalls.h"

device_id_t api_gpio_export(uint32_t gpio)
{
    device_id_t result = 0;
    syscall(SYSCALL_GPIO_EXPORT, gpio, (uint32_t)&result, 0, 0, 0);
    return result;
}
