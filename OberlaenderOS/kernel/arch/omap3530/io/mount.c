/*
 * mount.c
 *
 *  Created on: 07.06.2013
 *      Author: Daniel
 */


#include "../../../generic/io/mount.h"
#include "../../../genarch/io/mount.h"

void __mount_defaults(mountpoint_manager_t* manager)
{
    if(mountpoint_manager_add_mountpoint(manager, "sd", 0x0201, MOUNTPOINT_TYPE_FAT))
    {
        printf("SD-Card mounted!\n");
    }
    else
    {
        printf("SD-Card not mounted\n");
    }
}
