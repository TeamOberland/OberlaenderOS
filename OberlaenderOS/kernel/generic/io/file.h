/*
 * file.h
 *
 *  Created on: 29.05.2013
 *      Author: Daniel
 */

#ifndef FILE_H_
#define FILE_H_

#include <oos/types.h>
#include <oos/file.h>
#include "mount.h"

//
// Setup
void file_init(void);


//
// API

int32_t file_mount(mountpoint_t* mountpoint);
void file_unmount(mountpoint_t* mountpoint);

file_handle_t file_open(mountpoint_t* mountpoint, const char* path, const char* mode);
void file_close(file_handle_t handle);

int32_t file_flush(file_handle_t handle);
int32_t file_getc(file_handle_t handle);
char* file_gets(char* s, int32_t length, file_handle_t handle);
int32_t file_putc(int32_t c, file_handle_t handle);
int32_t file_puts(char* s, file_handle_t handle);
int32_t file_write(void* buffer, int32_t size, int32_t count, file_handle_t handle);
int32_t file_read(void* buffer, int32_t size, int32_t count, file_handle_t handle);
int32_t file_seek(file_handle_t handle, int32_t offset, int32_t origin);
int32_t file_getpos(file_handle_t handle, uint32_t* position);
int32_t file_tell(file_handle_t handle);
int32_t file_eof(file_handle_t handle);
int32_t file_remove(mountpoint_t* mountpoint, const char* filename);

dir_handle_t file_opendir(mountpoint_t* mountpoint, const char* path);
int32_t file_readdir(dir_handle_t dirls, api_file_direntry_t *entry);
int32_t file_closedir(dir_handle_t dir);

int32_t file_createdir(mountpoint_t* mountpoint, const char* path);
int32_t file_isdir(mountpoint_t* mountpoint, const char* path);

#endif /* FILE_H_ */
