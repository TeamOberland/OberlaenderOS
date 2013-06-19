/*
 * gpio.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include <oos/gpio.h>
#include <oos/syscalls.h>

device_id_t api_gpio_export(uint32_t gpio)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_GPIO_EXPORT;
    data.arg1 = (uint32_t) gpio;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}
