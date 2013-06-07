/*
 * mount.c
 *
 *  Created on: 07.06.2013
 *      Author: Daniel
 */

#include "mount.h"
#include "../../genarch/io/mount.h"
#include "../../../lib/types.h"
#include "../../../lib/utils.h"
#include "file.h"
#include <string.h>
#include <stdlib.h>

mountpoint_manager_t global_mountpoint_manager;

static mountpoint_handler_t dev_handler = { NULL, NULL,

NULL, NULL,

NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

static mountpoint_handler_t fat_handler = { file_mount, file_unmount,

file_open, file_close,

file_flush, file_getc,

file_gets,
file_putc,
file_puts,
file_write,
file_read,
file_seek,
file_getpos,
file_tell,
file_eof,
file_remove,

file_opendir,
file_readdir,
file_closedir,
file_createdir,
file_isdir
};

void mountpoint_manager_init(mountpoint_manager_t* manager)
{
    int i;
    manager->handlers[MOUNTPOINT_TYPE_DEV] = &dev_handler;
    manager->handlers[MOUNTPOINT_TYPE_FAT] = &fat_handler;

    for (i = 0; i < MAX_MOUNTPOINTS; i++)
    {
        manager->mountpoints[i].id = INVALID_MOUNTPOINT_ID;
    }
}

bool_t mountpoint_manager_add_mountpoint(mountpoint_manager_t* manager, const char* name, mountpoint_id_t id,
        mountpoint_type_t type)
{
    uint8_t i;
    for (i = 0; i < MAX_MOUNTPOINTS; i++)
    {
        if (manager->mountpoints[i].id == INVALID_MOUNTPOINT_ID)
        {
            manager->mountpoints[i].id = id;
            strcpy(manager->mountpoints[i].name, name);
            manager->mountpoints[i].type = type;
            manager->handlers[manager->mountpoints[i].type]->mount(&manager->mountpoints[i]);
            return TRUE;
        }
    }
    return FALSE;
}

bool_t mounpoint_manager_remove_mountpoint_name(mountpoint_manager_t* manager, const char* name)
{
    uint8_t i;
    for (i = 0; i < MAX_MOUNTPOINTS; i++)
    {
        if (strcmp(manager->mountpoints[i].name, name) == 0)
        {
            manager->handlers[manager->mountpoints[i].type]->unmount(&manager->mountpoints[i]);
            manager->mountpoints[i].id = INVALID_MOUNTPOINT_ID;
            return TRUE;
        }
    }
    return FALSE;
}

bool_t mountpoint_manager_remove_mountpoint_id(mountpoint_manager_t* manager, mountpoint_id_t id)
{
    uint8_t i;
    for (i = 0; i < MAX_MOUNTPOINTS; i++)
    {
        if (manager->mountpoints[i].id == id)
        {
            manager->handlers[manager->mountpoints[i].type]->unmount(&manager->mountpoints[i]);
            manager->mountpoints[i].id = INVALID_MOUNTPOINT_ID;
            return TRUE;
        }
    }
    return FALSE;
}

void mountpoint_manager_default_mountpoints(mountpoint_manager_t* manager)
{
    mountpoint_manager_add_mountpoint(manager, "dev", 0x0101, MOUNTPOINT_TYPE_DEV);
    __mount_defaults(manager);
}

#define MAX_PATH_PARTS 10
static char** split_path(const char* path, uint32_t* count)
{
    char** result = malloc(MAX_PATH_PARTS * sizeof(char*));
    int len = strlen(path);
    char* cur;
    if (len == 0 || path[0] != '/')
    {
        *count = 0;
        return NULL;
    }

    *count = 0;
    cur = strtok((char*)path, "/");
    while (cur != NULL)
    {
        result[*count] = cur;
        *count += 1;
        cur = strtok(NULL, "/");
    }

    return result;
}

static mountpoint_t* mount_find_mountpoint(const char* name)
{
    int i;
    // search for mountpoint
    for (i = 0; i < MAX_MOUNTPOINTS; i++)
    {
        if (global_mountpoint_manager.mountpoints[i].id != INVALID_MOUNTPOINT_ID
                && strcmp(global_mountpoint_manager.mountpoints[i].name, name))
        {
            return &global_mountpoint_manager.mountpoints[i];
        }
    }
    return NULL;
}

file_handle_t mount_open(const char* path, const char* mode)
{
    mount_handle_t* m;
    uint32_t pathCount;
    char** pathParts;

    pathCount = 0;
    pathParts = split_path(path, &pathCount);

    if (pathCount == 1 || pathParts == NULL)
    {
        return (file_handle_t) 0;
    }

    // search for mountpoint
    char* nodeName = pathParts[1];
    char* subPath = substring(path, 1 + strlen(nodeName), -1);
    mountpoint_t* mp = mount_find_mountpoint(nodeName);
    if (mp != NULL)
    {
        m = malloc(sizeof(mount_handle_t));
        m->mountPoint = mp;
        m->internalHandle = global_mountpoint_manager.handlers[mp->type]->open(mp, subPath, mode);
        free(subPath);
        return (file_handle_t) m;
    }
    free(subPath);
    return (file_handle_t) 0;
}

void mount_close(file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    global_mountpoint_manager.handlers[mh->mountPoint->type]->close(mh->internalHandle);
    free(mh);
}

int32_t mount_flush(file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->flush(mh->internalHandle);
}

int32_t mount_getc(file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->getc(mh->internalHandle);
}

char* mount_gets(char* s, int32_t length, file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->gets(s, length, mh->internalHandle);
}

int32_t mount_putc(int32_t c, file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->putc(c, mh->internalHandle);
}

int32_t mount_puts(char* s, file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->puts(s, mh->internalHandle);
}

int32_t mount_write(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->write(buffer, size, count, mh->internalHandle);
}

int32_t mount_read(void* buffer, int32_t size, int32_t count, file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->write(buffer, size, count, mh->internalHandle);
}

int32_t mount_seek(file_handle_t handle, int32_t offset, int32_t origin)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->seek(mh->internalHandle, offset, origin);
}

int32_t mount_getpos(file_handle_t handle, uint32_t* position)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->getpos(mh->internalHandle, position);
}

int32_t mount_tell(file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->tell(mh->internalHandle);
}

int32_t mount_eof(file_handle_t handle)
{
    mount_handle_t* mh = (mount_handle_t*) handle;
    return global_mountpoint_manager.handlers[mh->mountPoint->type]->eof(mh->internalHandle);
}

int32_t mount_remove(const char* filename)
{
    int32_t r;
    uint32_t pathCount;
    char** pathParts;

    pathCount = 0;
    pathParts = split_path(filename, &pathCount);

    if (pathCount == 1 || pathParts == NULL)
    {
        return 0;
    }

    // search for mountpoint
    char* nodeName = pathParts[1];
    char* subPath = substring(filename, 1 + strlen(nodeName), 1);
    mountpoint_t* mp = mount_find_mountpoint(nodeName);
    if (mp != NULL)
    {
        r = global_mountpoint_manager.handlers[mp->type]->remove(mp, subPath);
        free(subPath);
        return r;
    }
    free(subPath);
    return 0;
}

dir_handle_t mount_opendir(const char* path)
{
    mount_dir_handle_t* result;
    uint32_t pathCount;
    char** pathParts;

    pathCount = 0;
    pathParts = split_path(path, &pathCount);

    if (pathCount == 1 || pathParts == NULL)
    {
        // TODO: handle for root-directory
        return 0;
    }

    // search for mountpoint
    char* nodeName = pathParts[1];
    char* subPath = substring(path, 1 + strlen(nodeName),-1);
    mountpoint_t* mp = mount_find_mountpoint(nodeName);
    if (mp != NULL)
    {
        result = malloc(sizeof(mount_dir_handle_t));
        result->mountPoint = mp;
        result->internalHandle = global_mountpoint_manager.handlers[mp->type]->opendir(mp, subPath);
        free(subPath);
        return (dir_handle_t)result;
    }
    free(subPath);
    return 0;
}

int32_t mount_readdir(dir_handle_t dirls, api_file_direntry_t *entry)
{
    // TODO: Check for root directory
    mount_dir_handle_t* dh = (mount_dir_handle_t*)dirls;
    return global_mountpoint_manager.handlers[dh->mountPoint->type]->readdir(dh->internalHandle, entry);
}

int32_t mount_closedir(dir_handle_t dir)
{
    // TODO: Check for root directory
    mount_dir_handle_t* dh = (mount_dir_handle_t*)dir;
    int32_t ret = global_mountpoint_manager.handlers[dh->mountPoint->type]->closedir(dh->internalHandle);
    free(dh);
    return ret;
}

int32_t mount_createdir(const char* path)
{
    int32_t r;
    uint32_t pathCount;
    char** pathParts;

    pathCount = 0;
    pathParts = split_path(path, &pathCount);

    if (pathCount == 1 || pathParts == NULL)
    {
        return 0;
    }

    // search for mountpoint
    char* nodeName = pathParts[1];
    char* subPath = substring(path, 1 + strlen(nodeName), -1);
    mountpoint_t* mp = mount_find_mountpoint(nodeName);
    if (mp != NULL)
    {
        r = global_mountpoint_manager.handlers[mp->type]->createdir(mp, subPath);
        free(subPath);
        return r;
    }
    free(subPath);
    return 0;
}

int32_t mount_isdir(const char* path)
{
    int32_t r;
    uint32_t pathCount;
    char** pathParts;

    pathCount = 0;
    pathParts = split_path(path, &pathCount);

    if (pathCount == 1 || pathParts == NULL)
    {
        return 0;
    }

    // search for mountpoint
    char* nodeName = pathParts[1];
    char* subPath = substring(path, 1 + strlen(nodeName), -1);
    mountpoint_t* mp = mount_find_mountpoint(nodeName);
    if (mp != NULL)
    {
        r = global_mountpoint_manager.handlers[mp->type]->isdir(mp, subPath);
        free(subPath);
        return r;
    }
    free(subPath);
    return 0;
}
