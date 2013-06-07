/*
 * file.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef FILE_API_H_
#define FILE_API_H_

#include "types.h"

// C-Like api

#define API_FILE_SEEK_SET 0
#define API_FILE_SEEK_CUR 1
#define API_FILE_SEEK_END 2
#define API_FILE_EOF (-1)

typedef struct
{
    uint32_t sector;
    uint32_t cluster;
    uint8_t offset;
} api_file_dir_t;

#define MAX_LONG_FILENAME         260
typedef struct
{
    char filename[MAX_LONG_FILENAME];
    uint8_t is_dir;
    uint32_t cluster;
    uint32_t size;
} api_file_direntry_t;

file_handle_t api_fopen(const char* path, const char* mode);
void api_fclose(file_handle_t handle);

int32_t api_fflush(file_handle_t handle);
int32_t api_fgetc(file_handle_t handle);
char* api_fgets(char* s, int32_t length, file_handle_t handle);
int32_t api_fputc(int32_t c, file_handle_t handle);
int32_t api_fputs(char* s, file_handle_t handle);
int32_t api_fwrite(void* buffer, int32_t size, int32_t count, file_handle_t handle);
int32_t api_fread(void* buffer, int32_t size, int32_t count, file_handle_t handle);
int32_t api_fseek(file_handle_t handle, int32_t offset, int32_t origin);
int32_t api_fgetpos(file_handle_t handle, uint32_t* position);
int32_t api_ftell(file_handle_t handle);
int32_t api_feof(file_handle_t handle);
int32_t api_fremove(const char* filename);

api_file_dir_t* api_opendir(const char* path, api_file_dir_t *dir);
int32_t api_readdir(api_file_dir_t* dirls, api_file_direntry_t *entry);
int32_t api_closedir(api_file_dir_t* dir);

int32_t api_createdir(const char* path);
int32_t api_isdir(const char* path);


#endif /* FILE_API_H_ */
