/*
 * file.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "file.h"
#include "syscalls.h"

file_handle_t api_fopen(const char* path, const char* mode)
{
    file_handle_t handle;
    syscall(SYSCALL_FILE_OPEN, (uint32_t) path, (uint32_t) mode, (uint32_t) &handle, 0, 0);
    return handle;
}

void api_fclose(file_handle_t handle)
{
    syscall(SYSCALL_FILE_CLOSE, (uint32_t) handle, 0, 0, 0, 0);
}

int32_t api_fflush(file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_FLUSH, (uint32_t) handle, (uint32_t)&r, 0, 0, 0);
    return r;
}

int32_t api_fgetc(file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_GETC, (uint32_t) handle, (uint32_t)&r, 0, 0, 0);
    return r;
}

char* api_fgets(char* s, int32_t length, file_handle_t handle)
{
    char* r = NULL;
    syscall(SYSCALL_FILE_GETS, (uint32_t) s, (uint32_t)length, (uint32_t)handle, (uint32_t)&r, 0);
    return r;
}

int32_t api_fputc(int32_t c, file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_PUTC, (uint32_t)c, (uint32_t) handle, (uint32_t)&r, 0, 0);
    return r;
}

int32_t api_fputs(char* s, file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_PUTS, (uint32_t)s, (uint32_t) handle, (uint32_t)&r, 0, 0);
    return r;
}

int32_t api_fwrite(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_WRITE, (uint32_t)buffer, (uint32_t) size, (uint32_t) count, (uint32_t) handle, (uint32_t)&r);
    return r;
}

int32_t api_fread(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_READ, (uint32_t)buffer, (uint32_t) size, (uint32_t) count, (uint32_t) handle, (uint32_t)&r);
    return r;
}

int32_t api_fseek(file_handle_t handle, int32_t offset, int32_t origin)
{
    int32_t r;
    syscall(SYSCALL_FILE_SEEK, (uint32_t)handle, (uint32_t) offset, (uint32_t) origin, (uint32_t) &r, 0);
    return r;
}

int32_t api_fgetpos(file_handle_t handle, uint32_t* position)
{
    int32_t r;
    syscall(SYSCALL_FILE_GETPOS, (uint32_t)handle, (uint32_t) position, (uint32_t) &r, 0, 0);
    return r;
}

int32_t api_ftell(file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_TELL, (uint32_t)handle, (uint32_t) &r, 0, 0, 0);
    return r;
}

int32_t api_feof(file_handle_t handle)
{
    int32_t r;
    syscall(SYSCALL_FILE_EOF, (uint32_t)handle, (uint32_t) &r, 0, 0, 0);
    return r;
}

int32_t api_fremove(const char* filename)
{
    int32_t r;
    syscall(SYSCALL_FILE_REMOVE, (uint32_t)filename, (uint32_t) &r, 0, 0, 0);
    return r;
}

dir_handle_t api_opendir(const char* path)
{
    dir_handle_t r = NULL;
    syscall(SYSCALL_FILE_OPENDIR, (uint32_t)path, (uint32_t)&r, 0, 0, 0);
    return r;
}

int32_t api_readdir(dir_handle_t dirls, api_file_direntry_t *entry)
{
    int32_t r;
    syscall(SYSCALL_FILE_READDIR, (uint32_t)dirls, (uint32_t)entry, (uint32_t)&r, 0, 0);
    return r;
}

int32_t api_closedir(dir_handle_t dir)
{
    int32_t r;
    syscall(SYSCALL_FILE_CLOSEDIR, (uint32_t)dir, (uint32_t)&r, 0, 0, 0);
    return r;
}

int32_t api_createdir(const char* path)
{
    int32_t r;
    syscall(SYSCALL_FILE_CREATEDIR, (uint32_t)path, (uint32_t)&r, 0, 0, 0);
    return r;
}

int32_t api_isdir(const char* path)
{
    int32_t r;
    syscall(SYSCALL_FILE_ISDIR, (uint32_t)path, (uint32_t)&r, 0, 0, 0);
    return r;
}
