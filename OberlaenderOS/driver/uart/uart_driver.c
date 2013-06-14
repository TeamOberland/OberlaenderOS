/*
 * uart_driver.c
 *
 *  Created on: 31.05.2013
 *      Author: Manuel
 */

#include "uart_driver.h"
#include "../../kernel/generic/driver/device_manager.h"
#include "../../kernel/generic/io/uart.h"
#include "../../lib/uart.h"

driver_t uart_driver = {
    NULL,
    DEVICE_TYPE_UART,
    uart_driver_init,
    uart_driver_open,
    uart_driver_close,
    uart_driver_read,
    uart_driver_write,
    uart_driver_ioctl
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
    device_id_t id;
    uint8_t i = 0;
    for (i = 0; i < MAX_UART_DEVICES; i++)
    {
        id = device_manager_add_device(global_device_manager,&uart_driver,&registered_uarts[i]);
        registered_uarts[i].used = FALSE;
        registered_uarts[i].initialized = FALSE;
        registered_uarts[i].device= id;
        registered_uarts[i].uart_port=i+1;


    }
}

int16_t uart_driver_open(device_id_t device)
{
    registered_uart_t* reg = uart_get_registered(device);
    if (reg != NULL)
    {
        reg->used=TRUE;
        return 0;
    }
    return 1;
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
        while (uart_is_empty_read_queue(reg->uart_port));

        // block while waiting for data
        uart_read(reg->uart_port, &castedBuffer[i]);
    }

    return 0;
}

int16_t uart_driver_write(device_id_t device, void* buffer, uint32_t count)
{
    uint8_t* castedBuffer = ((uint8_t*)buffer);
    registered_uart_t* reg = uart_get_registered(device);
    if (reg != NULL)
    {
        int i = 0;
        for (; i < count; i++) {
            // block while queue is full
            while (!uart_is_empty_write_queue(reg->uart_port));
            uart_write(reg->uart_port, &castedBuffer[i]);
        }
        return 0;
    }
    return 1;
}

int32_t uart_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg)
{
    registered_uart_t* reg = uart_get_registered(device);
    if(reg!=NULL)
    {
        switch(cmd)
        case UART_DEVICE_INIT:
            if(uart_init(reg->uart_port,(uart_protocol_format_t*)arg)==0)
            {
                reg->initialized=TRUE;
                return 0;
            }
            else
            {
                return 2;
            }
    }

    return 1;
}


