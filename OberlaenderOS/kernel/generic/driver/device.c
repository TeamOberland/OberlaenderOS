/*
 * device.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "device.h"
#include <oos/device.h>


device_handle_t device_open(device_manager_t* dm, device_id_t deviceId)
{
    device_handle_t handle = device_manager_create_device_handle(dm,deviceId);
    device_node_t* node = device_manager_get_device_node(dm,deviceId);

    if(node->driver->open(deviceId)==0)
    {
        return handle;
    }

    device_close(dm,handle);
    return -1;
}

void device_close(device_manager_t* dm, device_handle_t handle)
{
    device_node_t* node =device_manager_get_device_node(dm,(handle>>8));
    node->driver->close(handle>>8);
}

void device_read(device_manager_t* dm, device_handle_t handle, void* buffer, uint32_t count)
{
    device_node_t* node =device_manager_get_device_node(dm,(handle>>8));
    node->driver->read(handle>>8,buffer,count);
}

void device_write(device_manager_t* dm, device_handle_t handle, void* buffer, uint32_t count)
{
    device_node_t* node =device_manager_get_device_node(dm,(handle>>8));
    node->driver->write(handle>>8,buffer,count);
}

int32_t device_ioctl(device_manager_t* dm, device_handle_t handle, uint32_t cmd, uint32_t arg)
{
    device_node_t* node =device_manager_get_device_node(dm,(handle>>8));
    return node->driver->ioctl(handle>>8,cmd, arg);
}
