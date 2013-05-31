/*
 * uart_driver.c
 *
 *  Created on: 31.05.2013
 *      Author: Manuel
 */

#include "uart_driver.h"
#include "../kernel/generic/driver/device_manager.h"

driver_t uart_driver = {
    NULL,
    uart_driver_init,
    uart_driver_open,
    uart_driver_close,
    uart_driver_read,
    uart_driver_write
};


static device_id_t uart_driver_export(uint32_t uart, bool_t output)
{

}

static int32_t uart_driver_unexport(uint32_t uart)
{
}


void uart_driver_init(void)
{
}

int16_t uart_driver_open(device_id_t device)
{
}

int16_t uart_driver_close(device_id_t device)
{
}

int16_t uart_driver_read(device_id_t device, void* buffer, uint32_t count)
{
}

int16_t uart_driver_write(device_id_t device, void* buffer, uint32_t count)
{

}



