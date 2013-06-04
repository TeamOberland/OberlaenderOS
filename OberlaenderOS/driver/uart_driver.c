/*
 * uart_driver.c
 *
 *  Created on: 31.05.2013
 *      Author: Manuel
 */

#include "uart_driver.h"
#include "../kernel/generic/driver/device_manager.h"
#include "../kernel/generic/io/uart.h"

driver_t uart_driver = {
    NULL,
    0,
    uart_driver_init,
    uart_driver_open,
    uart_driver_close,
    uart_driver_read,
    uart_driver_write
};

static registered_uart_t registered_uarts[MAX_UART_DEVICES];

static registered_uart_t* uart_get_registered(device_id_t device)
{
    int i;
    for (i = 0; i < MAX_UART_DEVICES; i++)
    {
        if (registered_uarts[i].device == device)
        {
            return &registered_uarts[i];
        }
    }
    return NULL;
}


void uart_driver_init(void)
{
    uint8_t i = 0;
    for (i = 0; i < MAX_UART_DEVICES; i++)
    {
        registered_uarts[i].used = FALSE;
        registered_uarts[i].device=i;
        registered_uarts[i].uart_port=i+1;
    }
}

int16_t uart_driver_open(device_id_t device)
{
    registered_uart_t* reg = uart_get_registered(device);
    if (reg != NULL)
    {
        reg->used=TRUE;
        uart_init(reg->uart_port);
    }
    return 0;
}

int16_t uart_driver_close(device_id_t device)
{
    registered_uart_t* reg = uart_get_registered(device);
    if (reg != NULL)
    {
        reg->used=FALSE;
        uart_disable(reg->uart_port);
    }
    return 0;
}

int16_t uart_driver_read(device_id_t device, void* buffer, uint32_t count)
{
    uint8_t* castedBuffer = ((uint8_t*)buffer);
    registered_uart_t* reg = uart_get_registered(device);
    int i = 0;

    for (; i < count; i++) {
        // block while waiting for data
        while (uart_is_empty_read_queue(reg->uart_port));
        uart_read(reg->uart_port, castedBuffer);
    }

    return i;
}

int16_t uart_driver_write(device_id_t device, void* buffer, uint32_t count)
{
    uint8_t* castedBuffer = ((uint8_t*)buffer);
    registered_uart_t* reg = uart_get_registered(device);
    if (reg != NULL)
    {
        int i = 0;
        for (; i < count; i++, castedBuffer++) {
            // block while queue is full
            while (!uart_is_empty_write_queue(reg->uart_port))
                ;
            uart_write(3, castedBuffer);
        }
    }
    return 0;
}


