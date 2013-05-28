/*
 * device_manager.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "device_manager.h"
#include <stdlib.h>

device_manager_t* global_device_manager;

device_manager_t* device_manager_init(void)
{
    device_manager_t* dm = malloc(sizeof(device_manager_t));
    return dm;
}

void device_manager_register_driver(device_manager_t* dm, driver_t* driver)
{
    if(driver != NULL && driver->init != NULL)
    {
        driver->deviceManager = dm;
        driver->init();
    }
}

device_id_t device_manager_add_device(device_manager_t* dm, driver_t* driver, void* deviceInfo)
{
    int i ;
    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
        if(dm->loadedDevice[i].driver == NULL)
        {
            dm->loadedDevice[i].driver = driver;
            dm->loadedDevice[i].device = dm->nextDeviceId;
            dm->nextDeviceId = dm->nextDeviceId+1;
            return dm->loadedDevice[i].device;
        }
    }
    return -1;
}

void device_manager_remove_device(device_manager_t* dm, driver_t* driver, device_id_t device)
{
    int i ;
    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
        if(dm->loadedDevice[i].driver == driver && dm->loadedDevice[i].device == device)
        {
            dm->loadedDevice[i].driver = NULL;
            dm->loadedDevice[i].device = -1;
            dm->nextDeviceId = dm->nextDeviceId-1;
            return;
        }
    }
}
