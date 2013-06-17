/*
 * file.c
 *
 *  Created on: 29.05.2013
 *      Author: Daniel
 */

#include "file.h"
#include <oos/file.h>
#include <oos/types.h>
#include "fatlib/fat_filelib.h"
#include "../../genarch/io/media.h"
#include <stdlib.h>

//
// Setup

// fatlib compatible functions
static int media_read (uint32 sector, uint8 *buffer, uint32 sectorCount)
{
    return (!__media_read((uint32_t)sector, (void*)buffer, (uint32_t)(sectorCount * FAT_SECTOR_SIZE)));
}
static int media_write(uint32 sector, uint8 *buffer, uint32 sectorCount)
{
    return (!__media_write((uint32_t)sector, (void*)buffer, (uint32_t)(sectorCount * FAT_SECTOR_SIZE)));
}

void file_init(void)
{
    // Initialize media system
    __media_init();

    // Initialize File IO Library
    fl_init();
}

int32_t file_mount(mountpoint_t* mountpoint)
{
    // TODO: how can we pass the mountpoint to media_read and write?
    if(fl_attach_media(media_read, media_write) != FAT_INIT_OK)
    {
        return -1;
    }
    return 0;
}

void file_unmount(mountpoint_t* mountpoint)
{
}

//
// API

file_handle_t file_open(mountpoint_t* mountpoint, const char* path, const char* mode)
{
    return fl_fopen(path, mode);
}

void file_close(file_handle_t handle)
{
    fl_fclose(handle);
}

int32_t file_flush(file_handle_t handle)
{
    return fl_fflush(handle);
}

int32_t file_getc(file_handle_t handle)
{
    return fl_fgetc(handle);
}

char* file_gets(char* s, int32_t length, file_handle_t handle)
{
    return fl_fgets(s, length, handle);
}

int32_t file_putc(int32_t c, file_handle_t handle)
{
    return fl_fputc(c, handle);
}

int32_t file_puts(char* s, file_handle_t handle)
{
    return fl_fputs(s, handle);
}

int32_t file_write(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    return fl_fwrite(buffer, size, count, handle);
}

int32_t file_read(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    return fl_fread(buffer, size, count, handle);
}

int32_t file_seek(file_handle_t handle, int32_t offset, int32_t origin)
{
    return fl_fseek(handle, offset, origin);
}

int32_t file_getpos(file_handle_t handle, uint32_t* position)
{
    return fl_fgetpos(handle, (uint32*) position);
}

int32_t file_tell(file_handle_t handle)
{
    return fl_ftell(handle);
}

int32_t file_eof(file_handle_t handle)
{
    return fl_feof(handle);
}

int32_t file_remove(mountpoint_t* mountpoint, const char* filename)
{
    return fl_remove(filename);
}

dir_handle_t file_opendir(mountpoint_t* mountpoint, const char* path)
{
    FL_DIR* dir = malloc(sizeof(FL_DIR));
    return (dir_handle_t) fl_opendir(path, dir);
}

int32_t file_readdir(dir_handle_t dirls, api_file_direntry_t* entry)
{
    return fl_readdir((FL_DIR*) dirls, (fl_dirent*) entry);
}

int32_t file_closedir(dir_handle_t dir)
{
    int32_t res = fl_closedir((FL_DIR*) dir);
    free(dir);
    return res;
}

int32_t file_createdir(mountpoint_t* mountpoint, const char* path)
{
    return fl_createdirectory(path);
}

int32_t file_isdir(mountpoint_t* mountpoint, const char* path)
{
    return fl_is_dir(path);
}

