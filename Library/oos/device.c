/*
 * device.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include <oos/device.h>
#include <oos/syscalls.h>

device_id_t api_device_build_id(driver_id_t deviceType, uint8_t deviceNumber)
{
    device_id_u_t u;
    u.device_info.driver_id = deviceType;
    u.device_info.device_number = deviceNumber;
    return u.device_id;
}

device_handle_t api_device_open(device_id_t device)
{
    device_handle_t handle = 0;
    syscall_data_t data;
    data.swiNumber=SYSCALL_DEVICE_OPEN;
    data.arg1 = (uint32_t) device;
    data.arg2 = (uint32_t) &handle;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;

    syscall(&data);
    return handle;
}

void api_device_close(device_handle_t handle)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_DEVICE_CLOSE;
    data.arg1 = (uint32_t) handle;
    data.arg2 = 0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;


    syscall(&data);
}

void api_device_read(device_handle_t handle, void* buffer, uint32_t count)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_DEVICE_READ;
    data.arg1 = (uint32_t) handle;
    data.arg2 =(uint32_t)buffer;
    data.arg3= count;
    data.arg4 = 0;
    data.arg5 = 0;

    syscall(&data);
}

void api_device_write(device_handle_t handle, void* buffer, uint32_t count)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_DEVICE_WRITE;
    data.arg1 = (uint32_t) handle;
    data.arg2 =(uint32_t)buffer;
    data.arg3= count;
    data.arg4 = 0;
    data.arg5 = 0;

    syscall(&data);
}

int32_t api_device_ioctl(device_handle_t handle, uint32_t cmd, uint32_t arg)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_DEVICE_IOCTL;
    data.arg1 = (uint32_t) handle;
    data.arg2 =cmd;
    data.arg3= arg;
    data.arg4 = 0;
    data.arg5 = 0;

    syscall(&data);
    return data.arg4;
}
