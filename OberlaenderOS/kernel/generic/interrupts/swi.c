/*
 * swi.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include <oos/ipc.h>
#include <oos/device.h>
#include <oos/file.h>
#include "../ipc/ipc.h"
#include "../scheduler/scheduler.h"
#include "../../genarch/scheduler/context.h"
#include "../driver/driver.h"
#include "../io/gpio.h"
#include "../io/uart.h"
#include "../io/file.h"
#include "../driver/device.h"
#include "../driver/device_manager.h"
#include "../io/mount.h"
#include <oos/syscalls.h>


//
// IPC
//

void swi_ipc_register(const char* ns)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if (proc != NULL)
    {
        ipc_register(ns, proc->id);
    }
}

void swi_ipc_unregister(const char* ns)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if (proc != NULL)
    {
        ipc_unregister(ns, proc->id);
    }
}

void swi_ipc_send(const char* ns, ipc_message_data_t* message)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if (proc != NULL)
    {
        ipc_send(ns, proc->id, message);
    }
}

void swi_ipc_receive(const char* ns, ipc_message_data_t** message)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if (proc != NULL)
    {
        ipc_message_data_t* received = ipc_receive(ns, proc->id);
        *message = received;
    }
    else
    {
        *message = NULL;
    }
}

void swi_ipc_wait(const char* ns)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if (proc != NULL)
    {
        ipc_wait(ns, proc->id);
    }
}

//
// Scheduler
//

void swi_scheduler_run(void)
{
    scheduler_run(global_scheduler);
}


//
// GPIO
//


void swi_gpio_export(uint32_t gpio, device_id_t* deviceId)
{
    *deviceId = gpio_export(gpio);
}

//
// Device
//

void swi_device_open(device_id_t deviceId, device_handle_t* handle)
{
    *handle = device_open(global_device_manager, deviceId);
}

void swi_device_close(device_handle_t handle)
{
    device_close(global_device_manager,handle);
}

void swi_device_read(device_handle_t handle, void* buffer, uint32_t count)
{
    device_read(global_device_manager,handle, buffer, count);
}

void swi_device_write(device_handle_t handle, void* buffer, uint32_t count)
{
    log_debug("swi_device_write start");
    device_write(global_device_manager,handle, buffer, count);
    log_debug("swi_device_write end");
}

void swi_device_ioctl(device_handle_t handle, uint32_t cmd, uint32_t arg, int32_t* res)
{
    *res = device_ioctl(global_device_manager, handle, cmd, arg);
}

//
// File
//
void swi_file_open(const char* path, const char* mode, file_handle_t* handle)
{
    *handle = mount_open(path, mode);
}

void swi_file_close(file_handle_t handle)
{
    mount_close(handle);
}

void swi_file_flush(file_handle_t handle, int32_t* result)
{
    *result = mount_flush(handle);
}

void swi_file_getc(file_handle_t handle, int32_t* result)
{
    *result = mount_getc(handle);
}

void swi_file_gets(char* s, int32_t length,  file_handle_t handle,  char** result)
{
    *result = mount_gets(s, length, handle);
}

void swi_file_putc(int32_t c, file_handle_t handle,  int32_t* result)
{
    *result = mount_putc(c, handle);
}

void swi_file_puts(char* s, file_handle_t handle,  int32_t* result)
{
    *result = mount_puts(s, handle);
}

void swi_file_write(void* buffer, int32_t size, int32_t count, file_handle_t handle, int32_t* result)
{
    *result = mount_write(buffer, size, count, handle);
}

void swi_file_read(void* buffer, int32_t size, int32_t count, file_handle_t handle, int32_t* result)
{
    *result = mount_read(buffer, size, count, handle);
}

void swi_file_seek(file_handle_t handle, int32_t offset, int32_t origin, int32_t* result)
{
    *result = mount_seek(handle, offset, origin);
}

void swi_file_getpos(file_handle_t handle, uint32_t* position, int32_t* result)
{
    *result = mount_getpos(handle, position);
}

void swi_file_tell(file_handle_t handle, int32_t* result)
{
    *result = mount_tell(handle);
}

void swi_file_eof(file_handle_t handle, int32_t* result)
{
    *result = mount_eof(handle);
}

void swi_file_remove(const char* filename, int32_t* result)
{
    *result = mount_remove(filename);
}

void swi_file_opendir(const char* path, dir_handle_t* result)
{
    *result = mount_opendir(path);
}

void swi_file_readdir(dir_handle_t dirls, api_file_direntry_t* entry, int32_t* result)
{
    *result = mount_readdir(dirls, entry);
}

void swi_file_closedir(dir_handle_t dir, int32_t* result)
{
    *result = mount_closedir(dir);
}

void swi_file_createdir(const char* path, int32_t* result)
{
    *result = mount_createdir(path);
}

void swi_file_isdir(const char* path, int32_t* result)
{
    *result = mount_isdir(path);
}

void swi_stdio_printf(const char* text)
{
    printf(text);
}

// something is really wrong with this preprocessor
// the include <oos/syscalls.h> includes the defines but not the typedefs o.O
#ifndef SYSCALL_DATA
#define SYSCALL_DATA
typedef struct syscall_data
{
    uint32_t swiNumber;
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
    uint32_t arg4;
    uint32_t arg5;
} syscall_data_t;
#endif

void swi_dispatch(syscall_data_t* data)
{
//    printf("[SWI] Handle %i\n", swiNumber);
    switch (data->swiNumber)
    {
        // IPC
        case SYSCALL_IPC_REGISTER:
            swi_ipc_register((const char*) data->arg1);
            break;
        case SYSCALL_IPC_UNREGISTER:
            swi_ipc_unregister((const char*) data->arg1);
            break;
        case SYSCALL_IPC_SEND:
            swi_ipc_send((const char*) data->arg1, (ipc_message_data_t*) data->arg2);
            break;
        case SYSCALL_IPC_RECEIVE:
            swi_ipc_receive((const char*) data->arg1, (ipc_message_data_t**) data->arg2);
            break;
        case SYSCALL_IPC_WAIT:
            swi_ipc_wait((const char*) data->arg1);
            break;

     //
            // Scheduler
        case SYSCALL_SCHEDULER_RUN:
            swi_scheduler_run();
            break;

            //
            // GPIO
        case SYSCALL_GPIO_EXPORT:
            swi_gpio_export(data->arg1, (device_id_t*) data->arg2);
            break;

            // Device
        case SYSCALL_DEVICE_OPEN:
            swi_device_open((device_id_t) data->arg1, (device_handle_t*) data->arg2);
            break;
        case SYSCALL_DEVICE_CLOSE:
            swi_device_close((device_handle_t) data->arg1);
            break;
        case SYSCALL_DEVICE_READ:
            swi_device_read((device_handle_t) data->arg1, (void*) data->arg2, data->arg3);
            break;
        case SYSCALL_DEVICE_WRITE:
            swi_device_write((device_handle_t) data->arg1, (void*) data->arg2, data->arg3);
            break;
        case SYSCALL_DEVICE_IOCTL:
            swi_device_ioctl((device_handle_t) data->arg1, data->arg2, data->arg3, (int32_t*)&data->arg4);
            break;

            //
            // File
        case SYSCALL_FILE_OPEN:
            swi_file_open((const char*)data->arg1, (const char*)data->arg2, (file_handle_t*)data->arg3);
            break;
        case SYSCALL_FILE_CLOSE:
            swi_file_close((file_handle_t)data->arg1);
            break;
        case SYSCALL_FILE_FLUSH:
            swi_file_flush((file_handle_t) data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_GETC:
            swi_file_getc((file_handle_t)data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_GETS:
            swi_file_gets((char*)data->arg1, (int32_t)data->arg2, (file_handle_t)data->arg3, (char**)data->arg4);
            break;
        case SYSCALL_FILE_PUTC:
            swi_file_putc((int32_t)data->arg1, (file_handle_t)data->arg2, (int32_t*)data->arg3);
            break;
        case SYSCALL_FILE_PUTS:
            swi_file_puts((char*)data->arg1, (file_handle_t)data->arg2, (int32_t*)data->arg3);
            break;
        case SYSCALL_FILE_WRITE:
            swi_file_write((void*)data->arg1, (int32_t)data->arg2, (int32_t)data->arg3, (file_handle_t)data->arg4, (int32_t*)data->arg5);
            break;
        case SYSCALL_FILE_READ:
            swi_file_read((void*)data->arg1, (int32_t)data->arg2, (int32_t)data->arg3, (file_handle_t)data->arg4, (int32_t*)data->arg5);
            break;
        case SYSCALL_FILE_SEEK:
            swi_file_seek((file_handle_t)data->arg1, (int32_t)data->arg2, (int32_t)data->arg3, (int32_t*)data->arg4);
            break;
        case SYSCALL_FILE_GETPOS:
            swi_file_getpos((file_handle_t)data->arg1, (uint32_t*)data->arg2, (int32_t*)data->arg3);
            break;
        case SYSCALL_FILE_TELL:
            swi_file_tell((file_handle_t)data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_EOF:
            swi_file_eof((file_handle_t)data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_REMOVE:
            swi_file_remove((const char*)data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_OPENDIR:
            swi_file_opendir((const char*)data->arg1, (dir_handle_t*)data->arg2);
            break;
        case SYSCALL_FILE_READDIR:
            swi_file_readdir((dir_handle_t)data->arg1, (api_file_direntry_t*)data->arg2, (int32_t*)data->arg3);
            break;
        case SYSCALL_FILE_CLOSEDIR:
            swi_file_closedir((dir_handle_t)data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_CREATEDIR:
            swi_file_createdir((const char*)data->arg1, (int32_t*)data->arg2);
            break;
        case SYSCALL_FILE_ISDIR:
            swi_file_isdir((const char*)data->arg1, (int32_t*)data->arg2);
            break;

        case SYSCALL_STDIO_PRINTF:
            swi_stdio_printf((const char*)data->arg1);
            break;
    }
}



#pragma INTERRUPT(swi_handle, SWI)
#pragma TASK(swi_handle)
interrupt void swi_handle(syscall_data_t* data)
{
    asm(" SUB R13, R13, #4");
    asm(" STR R14, [R13]");
    __context_save();
    asm(" ADD R13, R13, #4");

    log_debug("2 swiHandle dispatch");
    swi_dispatch(data);

    log_debug("3 before context load");
    __context_load();
}
