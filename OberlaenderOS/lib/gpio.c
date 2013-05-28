/*
 * gpio.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "gpio.h"
#include "syscalls.h"

int16_t api_gpio_export(uint32_t gpio, bool_t output)
{
    int16_t result = 0;
    syscall(SYSCALL_GPIO_EXPORT, gpio, (uint32_t)output, (uint32_t)&result);
    return result;
}
