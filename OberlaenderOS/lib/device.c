/*
 * device.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "device.h"
#include "syscalls.h"

device_handle_t api_device_open(device_id_t device)
{
    device_handle_t handle = 0;
    syscall(SYSCALL_DEVICE_OPEN, (uint32_t) device, (uint32_t) &handle, 0, 0, 0);
    return handle;
}

void api_device_close(device_handle_t handle)
{
    syscall(SYSCALL_DEVICE_CLOSE, (uint32_t) &handle,0, 0, 0,0);
}

void api_device_read(device_handle_t handle, void* buffer, uint32_t count)
{
    syscall(SYSCALL_DEVICE_READ, (uint32_t)handle, (uint32_t)buffer, count, 0, 0);
}

void api_device_write(device_handle_t handle, void* buffer, uint32_t count)
{
    syscall(SYSCALL_DEVICE_WRITE, (uint32_t)handle, (uint32_t)buffer, count, 0, 0);
}

int32_t api_device_ioctl(device_handle_t handle, uint32_t cmd, uint32_t arg)
{
    int32_t res = 0;
    syscall(SYSCALL_DEVICE_IOCTL, (uint32_t)handle, cmd, arg, (uint32_t)&res, 0);
    return res;
}
