/*
 * file.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include <oos/file.h>
#include <oos/syscalls.h>

file_handle_t api_fopen(const char* path, const char* mode)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_OPEN;
    data.arg1 = (uint32_t) path;
    data.arg2 =(uint32_t)mode;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;

    syscall(&data);
    return (file_handle_t)data.arg3;
}

void api_fclose(file_handle_t handle)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_CLOSE;
    data.arg1 = (uint32_t) handle;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
}

int32_t api_fflush(file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_FLUSH;
    data.arg1 = (uint32_t) handle;
    data.arg2 = 0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

int32_t api_fgetc(file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_GETC;
    data.arg1 = (uint32_t) handle;
    data.arg2 = 0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

char* api_fgets(char* s, int32_t length, file_handle_t handle)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_GETS;
    data.arg1 = (uint32_t) s;
    data.arg2 =(uint32_t)length;
    data.arg3= (uint32_t)handle;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return (char*)data.arg4;
}

int32_t api_fputc(int32_t c, file_handle_t handle)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_PUTC;
    data.arg1 = (uint32_t) c;
    data.arg2 =(uint32_t)handle;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg3;
}

int32_t api_fputs(char* s, file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_PUTS;
    data.arg1 = (uint32_t)s;
    data.arg2 =(uint32_t)handle;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg3;
}

int32_t api_fwrite(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_WRITE;
    data.arg1 = (uint32_t) buffer;
    data.arg2 =(uint32_t)size;
    data.arg3=  (uint32_t)count;
    data.arg4 = (uint32_t) handle;
    data.arg5 = 0;
    syscall(&data);
    return data.arg5;
}

int32_t api_fread(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_READ;
    data.arg1 = (uint32_t) buffer;
    data.arg2 =(uint32_t)size;
    data.arg3=  (uint32_t)count;
    data.arg4 = (uint32_t) handle;
    data.arg5 = 0;
    syscall(&data);
    return data.arg5;
}

int32_t api_fseek(file_handle_t handle, int32_t offset, int32_t origin)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_SEEK;
    data.arg1 = (uint32_t) handle;
    data.arg2 =(uint32_t)offset;
    data.arg3= (uint32_t)origin;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg4;
}

int32_t api_fgetpos(file_handle_t handle, uint32_t* position)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_GETPOS;
    data.arg1 = (uint32_t) handle;
    data.arg2 =(uint32_t)position;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg3;
}

int32_t api_ftell(file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_TELL;
    data.arg1 = (uint32_t) handle;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

int32_t api_feof(file_handle_t handle)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_EOF;
    data.arg1 = (uint32_t) handle;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

int32_t api_fremove(const char* filename)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_REMOVE;
    data.arg1 = (uint32_t) filename;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

dir_handle_t api_opendir(const char* path)
{
    dir_handle_t r = NULL;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_OPENDIR;
    data.arg1 = (uint32_t) path;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return (dir_handle_t)data.arg2;
}

int32_t api_readdir(dir_handle_t dirls, api_file_direntry_t *entry)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_READDIR;
    data.arg1 = (uint32_t) dirls;
    data.arg2 =(uint32_t)entry;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg3;
}

int32_t api_closedir(dir_handle_t dir)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_CLOSEDIR;
    data.arg1 = (uint32_t) dir;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

int32_t api_createdir(const char* path)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_CREATEDIR;
    data.arg1 = (uint32_t) path;
    data.arg2 = 0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}

int32_t api_isdir(const char* path)
{
    int32_t r;
    syscall_data_t data;
    data.swiNumber=SYSCALL_FILE_ISDIR;
    data.arg1 = (uint32_t) path;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
    return data.arg2;
}
