/*
 * main_martin.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#ifdef Martin

#include <oos/types.h>
#include <oos/device.h>
#include "kernel/generic/driver/device.h"
#include "kernel/generic/driver/device_manager.h"
#include "driver/uart/uart_driver.h"
#include <oos/uart.h>
#include <oos/ipc.h>


#define mouse_event_none        0
#define mouse_event_left_down   1
#define mouse_event_left_up     2
#define mouse_event_right_down  3
#define mouse_event_right_up    4

#define SCREEN_WIDTH    1366
#define SCREEN_HEIGHT   768

typedef struct{
    uint32_t x;
    uint32_t y;
} mouse_position_t;


typedef struct
{
    int32_t x;
    int32_t y;
    int32_t mouse_event;

} mouse_input_t;

extern device_manager_t* global_device_manager;
device_handle_t mouse_input_handler;

mouse_position_t global_mouse_position;

bool_t mouse_click_fetched;

int32_t __check_mouse_border(int32_t value, int32_t maxValue)
{
    if(&value > maxValue)
    {
        return maxValue;
    }
    else if(&value < 0)
    {
        return 0;
    }
    return value;
}

void __mouse_position_calculation(mouse_input_t* input)
{
    int32_t newMousePositionX = global_mouse_position.x + input->x;
    int32_t newMousePositionY = global_mouse_position.y + input->y;

    // Check if over the boarders
    global_mouse_position.x = check_mouse_border(newMousePositionX, SCREEN_WIDTH);
    global_mouse_position.y = check_mouse_border(newMousePositionY, SCREEN_HEIGHT);

    if(input->mouse_event != 0)
    {
        mouse_click_fetched = TRUE;
    }
}

bool_t is_mouse_clicked()
{
    if(mouse_click_fetched)
    {
        mouse_click_fetched = FALSE;
        return TRUE;
    }
    return FALSE;
}


void martin_setup_device_manager(void)
{
    global_device_manager = device_manager_init();
    device_manager_register_driver(global_device_manager, &uart_driver);
}

void init_mouse_handler(void)
{
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 3);
    mouse_input_handler = device_open(global_device_manager, uartDevice);
    device_ioctl(global_device_manager,mouse_input_handler,UART_DRIVER_INIT,(uint32_t)&uart_protocol_rs232);

    global_mouse_position.x = SCREEN_WIDTH / 2;
    global_mouse_position.y = SCREEN_HEIGHT / 2;

    mouse_click_fetched = FALSE;
}


void mouse_read_input(void)
{
    int32_t mouseInput[3];

    device_read(global_device_manager, mouse_input_handler, &mouseInput, sizeof(mouse_input_t));

    mouse_input_t input;
    input.x = mouseInput[0];
    input.y = mouseInput[1];
    input.mouse_event = mouseInput[2];

    __mouse_position_calculation(&input);
}

void main_martin(void)
{
    setup_kernel();
    martin_setup_device_manager();
    init_mouse_handler();

    while(TRUE)
    {
        mouse_read_input();
    }
}




#endif
