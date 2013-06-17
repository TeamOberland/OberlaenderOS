/*
 * logger.c
 *
 *  Created on: 14.06.2013
 *      Author: Manuel
 */

#include <oos/types.h>
#include <oos/device.h>
#include "../driver/device.h"
#include "../driver/device_manager.h"

extern device_manager_t* global_device_manager;
device_handle_t logger;

void loggerInit()
{return;
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 3);
    logger= device_open(global_device_manager,uartDevice);
}

static void log(char* type, char* format, va_list args)
{return;
    char formatted[255];
    char* lineFeed = "\r\n";
    device_write(global_device_manager,logger,type,strlen(type));
    device_write(global_device_manager,logger,lineFeed,strlen(lineFeed));

    device_write(global_device_manager,logger,formatted,255);
    device_write(global_device_manager,logger,lineFeed,strlen(lineFeed));
}

void  log_debug(char* format, ...)
{return;

    va_list args;
    va_start(args, format);

    log("debug:", format, args);

    va_end(args);
}
