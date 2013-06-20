/*
 * dmx_driver.c
 *
 *  Created on: 19.06.2013
 *      Author: Manuel
 */

#include <oos/device.h>
#include "dmx_driver.h"
#include "../gpio/gpio_driver.h"
#include "../uart/uart_driver.h"
#include <oos/uart.h>
#include "../../kernel/generic/io/uart.h"
#include "../../kernel/generic/driver/device_manager.h"

#define DEVICE_TYPE_DMX  0x0005
device_handle_t gpio_pin11_handle;
    device_handle_t gpio_pin6_handle;
    device_id_t gpio_pin11;
    device_id_t gpio_pin6;
    uint8_t one = 1;
    uint8_t cero = 0;
driver_t dmx_driver = {
    NULL,
    DEVICE_TYPE_DMX,
    dmx_driver_init,
    dmx_driver_open,
    dmx_driver_close,
    dmx_driver_read,
    dmx_driver_write,
    dmx_driver_ioctl
};

registered_uart_t registered_dmx;

int16_t dmx_uart_write(device_id_t device, void* buffer, uint32_t count)
{
    uint8_t* castedBuffer = ((uint8_t*)buffer);
         int i = 0;
         for (; i < count; i++) {
             // block while queue is full
             while (!uart_is_empty_write_queue(registered_dmx.uart_port));
             uart_write(registered_dmx.uart_port, &castedBuffer[i]);
         }

         return 0;
}

void dmx_driver_init(void)
{
    device_id_t id;
    id = device_manager_add_device(global_device_manager,&dmx_driver,&registered_dmx);
    registered_dmx.used = FALSE;
    registered_dmx.initialized = FALSE;
    registered_dmx.device= id;
    registered_dmx.uart_port=2;
}

int16_t dmx_driver_open(device_id_t device)
{
    registered_dmx.used=true;
    return 0;
}
int16_t dmx_driver_close(device_id_t device)
{
    gpio_driver_close(gpio_pin11);
    gpio_driver_close(gpio_pin6);
    registered_dmx.used=FALSE;
    uart_disable(registered_dmx.uart_port);
}

int16_t dmx_driver_read(device_id_t device, void* buffer, uint32_t count)
{
    return -1;
}
int16_t dmx_driver_write(device_id_t device, void* buffer, uint32_t count)
{
    int a,i;

    while(!uart_is_empty_write_queue(registered_dmx.uart_port));
    a = 240; //~204 microseconds during testing
    for(i = 0; i < a; i++);
    set_expansion_pin_mode(6,MODE_GPIO);
    //reset
    gpio_driver_write(gpio_pin6,&cero,1);
    a = 240; //~204 microseconds during testing
    for(i = 0; i < a; i++);
    a = 10; //~10 microseconds
    gpio_driver_write(gpio_pin6_handle, &one, 1);
    for(i = 0; i < a; i++);

    set_expansion_pin_mode(6,MODE_UART);
    char ceroByte=0;
    dmx_uart_write(device,&ceroByte,1);
    return dmx_uart_write(device, buffer, count);
}



int32_t dmx_driver_ioctl(device_id_t device, uint32_t cmd, uint32_t arg)
{

        switch(cmd)
        case UART_DEVICE_INIT:
            if(dmx_init(registered_dmx.uart_port,(uart_protocol_format_t*)arg)==0)
            {
                gpio_pin11 = gpio_export(135);
                gpio_pin6 = gpio_export(146);
                gpio_pin11_handle = gpio_driver_open(gpio_pin11);
                gpio_pin6_handle = gpio_driver_open(gpio_pin6);
                gpio_driver_ioctl(gpio_pin11_handle, GPIO_DRV_IOCTL_SET_DIR, GPIO_DRV_IOCTL_DIR_OUT);
                gpio_driver_ioctl(gpio_pin6_handle, GPIO_DRV_IOCTL_SET_DIR, GPIO_DRV_IOCTL_DIR_OUT);
                gpio_driver_write(gpio_pin11_handle, &one, 1);

                registered_dmx.initialized=TRUE;
                return 0;
            }
            else
            {
                return 2;
            }

    return 1;
}
