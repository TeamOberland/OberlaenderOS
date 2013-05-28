/*
 * device.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "device.h"
#include "../../../lib/device.h"

device_handle_t device_open(device_manager_t* dm, device_id_t deviceId)
{
    // TODO tell the appropriate driver to open a new handle
    return 0;
}

void device_close(device_handle_t handle)
{
    // TODO tell the appropriate driver to close the given handle
}

void device_read(device_handle_t handle, void* buffer, uint32_t count)
{
    // TODO: tell the appropriate driver to fill the buffer
}

void device_write(device_handle_t handle, void* buffer, uint32_t count)
{
    // TODO: tell the appropriate driver to write the data to the device from the buffer
}
