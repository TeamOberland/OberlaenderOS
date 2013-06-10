/*
 * mount.h
 *
 *  Created on: 07.06.2013
 *      Author: Daniel
 */

#ifndef MOUNT_H_
#define MOUNT_H_

#include "../../../lib/types.h"
#include "../../../lib/file.h"

typedef uint16_t mountpoint_id_t;

typedef enum
{
    MOUNTPOINT_TYPE_DEV, MOUNTPOINT_TYPE_FAT
} mountpoint_type_t;

#define MAX_MOUNTPOINT_NAME 50
typedef struct
{
    mountpoint_id_t id;
    mountpoint_type_t type;
    char name[MAX_MOUNTPOINT_NAME];
} mountpoint_t;

typedef struct
{
    void (*mount)(mountpoint_t* mountpoint);
    void (*unmount)(mountpoint_t* mountpoint);

    file_handle_t (*open)(mountpoint_t* mountpoint, const char* path, const char* mode);
    void (*close)(file_handle_t handle);

    int32_t (*flush)(file_handle_t handle);
    int32_t (*getc)(file_handle_t handle);

    char* (*gets)(char* s, int32_t length, file_handle_t handle);
    int32_t (*putc)(int32_t c, file_handle_t handle);
    int32_t (*puts)(char* s, file_handle_t handle);
    int32_t (*write)(void* buffer, int32_t size, int32_t count, file_handle_t handle);
    int32_t (*read)(void* buffer, int32_t size, int32_t count, file_handle_t handle);
    int32_t (*seek)(file_handle_t handle, int32_t offset, int32_t origin);
    int32_t (*getpos)(file_handle_t handle, uint32_t* position);
    int32_t (*tell)(file_handle_t handle);
    int32_t (*eof)(file_handle_t handle);
    int32_t (*remove)(mountpoint_t* mountpoint, const char* filename);

    dir_handle_t (*opendir)(mountpoint_t* mountpoint, const char* path);
    int32_t (*readdir)(dir_handle_t dirls, api_file_direntry_t *entry);
    int32_t (*closedir)(dir_handle_t dir);

    int32_t (*createdir)(mountpoint_t* mountpoint, const char* path);
    int32_t (*isdir)(mountpoint_t* mountpoint, const char* path);

} mountpoint_handler_t;

#define MAX_MOUNTPOINTS 10
#define MAX_MOUNTPOINT_TYPES 2
#define INVALID_MOUNTPOINT_ID 0
typedef struct
{
    mountpoint_t mountpoints[MAX_MOUNTPOINTS];
    mountpoint_handler_t* handlers[MAX_MOUNTPOINT_TYPES];
} mountpoint_manager_t;

extern mountpoint_manager_t global_mountpoint_manager;

void mountpoint_manager_init(mountpoint_manager_t* manager);
bool_t mountpoint_manager_add_mountpoint(mountpoint_manager_t* manager, const char* name, mountpoint_id_t id,
        mountpoint_type_t type);
bool_t mounpoint_manager_remove_mountpoint_name(mountpoint_manager_t* manager, const char* name);
bool_t mountpoint_manager_remove_mountpoint_id(mountpoint_manager_t* manager, mountpoint_id_t id);
void mountpoint_manager_default_mountpoints(mountpoint_manager_t* manager);

typedef struct
{
    mountpoint_t* mountPoint;
    file_handle_t internalHandle;
} mount_handle_t;

typedef struct
{
    mountpoint_t* mountPoint;
    dir_handle_t internalHandle;
} mount_dir_handle_t;


file_handle_t mount_open(const char* path, const char* mode);
void mount_close(file_handle_t handle);

int32_t mount_flush(file_handle_t handle);
int32_t mount_getc(file_handle_t handle);
char* mount_gets(char* s, int32_t length, file_handle_t handle);
int32_t mount_putc(int32_t c, file_handle_t handle);
int32_t mount_puts(char* s, file_handle_t handle);
int32_t mount_write(void* buffer, int32_t size, int32_t count, file_handle_t handle);
int32_t mount_read(void* buffer, int32_t size, int32_t count, file_handle_t handle);
int32_t mount_seek(file_handle_t handle, int32_t offset, int32_t origin);
int32_t mount_getpos(file_handle_t handle, uint32_t* position);
int32_t mount_tell(file_handle_t handle);
int32_t mount_eof(file_handle_t handle);
int32_t mount_remove(const char* filename);

dir_handle_t mount_opendir(const char* path);
int32_t mount_readdir(dir_handle_t dirls, api_file_direntry_t *entry);
int32_t mount_closedir(dir_handle_t dir);

int32_t mount_createdir(const char* path);
int32_t mount_isdir(const char* path);

#endif /* MOUNT_H_ */
