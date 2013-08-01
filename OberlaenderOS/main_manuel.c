/*
 * main_manuel.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "kernel/generic/kernel.h"

#include "kernel/generic/scheduler/scheduler.h"
#include <oos/scheduler.h>
#include "kernel/generic/driver/driver.h"
#include "kernel/generic/driver/device_manager.h"
#include <oos/dmx.h>

#include "driver/gpio/gpio_driver.h"
#include "driver/dmx/dmx_driver.h"
#include "driver/video/video_driver.h"
#include "kernel/genarch/io/expansion.h"
#include <oos/device.h>
#include <oos/uart.h>
#include "kernel/generic/log/logger.h"
#include <string.h>

extern void task_blink_led0(void);
extern void task_blink_led1(void);
extern void task_gpio_led0(void);
//extern void main_matthias(void);

extern void task_ipc_server(void);
extern void task_ipc_client(void);
extern void play_game(void);
extern void task_blink_dmx_led(void);

void setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
    device_manager_register_driver(global_device_manager, &uart_driver);
    device_manager_register_driver(global_device_manager, &dmx_driver);
    device_manager_register_driver(global_device_manager, &video_driver);
}

typedef struct dmx_protocol_par_complex_t {
    uint8_t pan;
    uint8_t til;
    uint8_t colorWheel;
    uint8_t shutter;
    uint8_t goboWheel;
    uint8_t goboRotation;
} dmx_protocol_par_complex_t;



void dmx_wait(uint32_t bits)
{
    while(bits--)
    {
    }
}
#define DEVICE_TYPE_GPIO  0x0001
#define DEVICE_TYPE_UART  0x0002
#define DEVICE_TYPE_VIDEO 0x0003
#define DEVICE_TYPE_RS232  0x0004
#define DEVICE_TYPE_DMX  0x0005

void dmx_sending_signal()
{


    uint32_t i;
    dmx_protocol_par_t data;
    dmx_protocol_par_complex_t dataComplex;
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_DMX, 1);
    device_handle_t handle= device_open(global_device_manager,uartDevice);
    device_ioctl(global_device_manager,handle,UART_DRIVER_INIT,(uint32_t)&uart_protocol_dmx);

    data.mode=0x2;
    data.function=0;


    uint32_t j = 0;
    while(TRUE)
    {
        dataComplex.colorWheel=j%256;
        dataComplex.goboRotation=1;
        dataComplex.goboWheel=j%256;
        dataComplex.pan=j%256;
        dataComplex.shutter=  6;
        dataComplex.til=j%256;
        j+=3;
        device_write(global_device_manager,handle,&dataComplex, sizeof(dataComplex));
        for (i = 0; i < 100000; ++i);
    }

    int red;
    int blue;
    int green;
    while(TRUE)
    {

        for (green = 0; green < 255; ++green) {
            data.green = green;  //green
            device_write(global_device_manager,handle,&data, sizeof(data));
        }
        data.green = 0;  //green
        for (blue = 0; blue < 255; ++blue) {
            data.blue = blue;  //blue
            device_write(global_device_manager,handle,&data, 5);
        }
        data.blue = 0;//blue
        for (red = 0; red < 255; ++red) {
            data.red = red;  //red
            device_write(global_device_manager,handle,&data, 5);
        }
        data.red = 0;  //red

        for (green = 0; green < 255; ++green) {
            data.green = green;  //green
            device_write(global_device_manager,handle,&data, 5);
            for (i = 0; i < 2000; ++i) {

            }
        }
        for (blue = 0; blue < 255; ++blue) {
            data.blue = blue;  //red
            device_write(global_device_manager,handle,&data, 5);
            for (i = 0; i < 2000; ++i) {

            }
        }
        for (red = 0; red < 255; ++red) {
            data.red = red;  //red
            device_write(global_device_manager,handle,&data, 5);
            for (i = 0; i < 2000; ++i) {

            }
        }



        data.blue=255;
        data.red =255;
        data.green=255;



//        uint32_t j = 0;
//        while(TRUE)
//        {
//            dataComplex.colorWheel=j;
//            dataComplex.goboRotation=j;
//            dataComplex.goboWheel=j;
//            dataComplex.pan=j;
//            dataComplex.shutter=j;
//            dataComplex.til=j;
//            j++;
//            device_write(global_device_manager,handle,&dataComplex, sizeof(dataComplex));
//        }



        device_write(global_device_manager,handle,&data, 5);

//        for (i = 0; i < 100000; ++i) {
//
//        }
    }
}

typedef struct mouse_input_t
{
    int32_t x;
    int32_t y;
    int32_t mouse;
} mouse_input_t;

void task_console_no_swi(void)
{
    char toRead[64];
    memset(&toRead,0,64);
    mouse_input_t mouseInput;
    memset(&mouseInput,0,sizeof(mouse_input_t));

    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 3);
    device_handle_t handle= device_open(global_device_manager,uartDevice);
    device_ioctl(global_device_manager,handle,UART_DRIVER_INIT,(uint32_t)&uart_protocol_rs232);
    char* message = "\r\n welcome to oberlaenderOS\r\n\0";
    device_write(global_device_manager,handle,message,strlen(message));
    message="possible commands are:\r\n\0";
    device_write(global_device_manager,handle,message,strlen(message));
    message ="echo\r\n pwd\r\n\0";
    device_write(global_device_manager,handle,message,strlen(message));
    uint8_t i = 0;
    uint32_t j = 0;
    while(TRUE)
    {
//        if(i>=64)
//        {
//            i=0;
//        }
//
//        device_read(global_device_manager,handle,&toRead[i],1);
//
//        //line ending
//        if(i>0&&toRead[i-1]==13&&toRead[i]==10)
//        {
//            message="trying to execute your command:\r\n\0";
//            device_write(global_device_manager,handle,message,strlen(message));
//        }
//        i++;
//
//        device_write(global_device_manager,handle,&toRead[i-1],1);

        device_read(global_device_manager,handle,&mouseInput,sizeof(mouse_input_t));

        if(mouseInput.mouse!=0)
        {
           printf("blub");
        }



        //printf("%i\r\n",toRead[i]);
//
//        for (j = 0; j < 1000; ++j) {
//
//        }
    }

    device_close(global_device_manager,handle);
    while(TRUE);
}



uint32_t saved_R14;
void main_manuel(void)
{
    main_matthias();
    return;
    saved_R14=0;
    printf("Setup kernel\n");
    setup_kernel();
    setup_device_manager();
    loggerInit();

    log_debug("\r\n\r\nSystem init...");

   //task_console_no_swi();
    //dmx_sending_signal();
    play_game();
//    __enable_interrupts();
//    __switch_to_user_mode();

//    scheduler_add_process(global_scheduler, task_blink_led0);
//    scheduler_add_process(global_scheduler, task_blink_led1);
//    scheduler_add_process(global_scheduler, task_gpio_led0);
//    scheduler_add_process(global_scheduler, task_blink_dmx_led);
//    scheduler_add_process(global_scheduler, task_console);
//    scheduler_add_process(global_scheduler, task_ipc_server);
//    scheduler_add_process(global_scheduler, task_ipc_client);
    //scheduler_start(10000000);
    //api_scheduler_run();

    /* led_test1(); */

    /* timer_test(); */

    /* gptimer_test(); */

    /* swi_test();*/

    /* ipc_test(); */

    /* display_test(); */
}


