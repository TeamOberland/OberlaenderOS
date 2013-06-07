/*
 * file.c
 *
 *  Created on: 29.05.2013
 *      Author: Daniel
 */

#include "file.h"
#include "../../../lib/file.h"
#include "../../../lib/types.h"
#include "fatlib/fat_filelib.h"
#include "../../genarch/io/media.h"

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

    // TODO: dynamically mount media with according filesystem driver (not fixed mount)
    if (fl_attach_media(media_read, media_write) != FAT_INIT_OK)
    {
        printf("ERROR: Media attach failed\n");
        return;
    }
    else
    {
        printf("SUCCESS: Media attached\n");
    }
}

//
// API

file_handle_t file_open(const char* path, const char* mode)
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

int32_t file_remove(const char* filename)
{
    return fl_remove(filename);
}

api_file_dir_t* file_opendir(const char* path, api_file_dir_t *dir)
{
    // NOTE: api_file_dir_t and api_file_direntry_t have the same structure
    return (api_file_dir_t*) fl_opendir(path, (FL_DIR*) dir);
}

int32_t file_readdir(api_file_dir_t* dirls, api_file_direntry_t *entry)
{
    return fl_readdir((FL_DIR*) dirls, (fl_dirent*) entry);
}

int32_t file_closedir(api_file_dir_t* dir)
{
    return fl_closedir((FL_DIR*) dir);
}

int32_t file_createdir(const char* path)
{
    return fl_createdirectory(path);
}

int32_t file_isdir(const char* path)
{
    return fl_is_dir(path);
}

