/*
 * file.h
 *
 *  Created on: 29.05.2013
 *      Author: Daniel
 */

#ifndef FILE_H_
#define FILE_H_

#include "../../../lib/types.h"
#include "../../../lib/file.h"

//
// Setup
void file_init(void);


//
// API

file_handle_t file_open(const char* path, const char* mode);
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
int32_t file_remove(const char* filename);

api_file_dir_t* file_opendir(const char* path, api_file_dir_t *dir);
int32_t file_readdir(api_file_dir_t* dirls, api_file_direntry_t *entry);
int32_t file_closedir(api_file_dir_t* dir);

int32_t file_createdir(const char* path);
int32_t file_isdir(const char* path);

#endif /* FILE_H_ */
