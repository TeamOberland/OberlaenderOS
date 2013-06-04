/*
 * device_manager.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "device_manager.h"
#include <stdlib.h>

typedef union device_id
{
    struct
    {
        uint8_t device_number : 4;
        driver_id_t driver_id : 4;
    }device_info;
    device_id_t device_id;
} device_id_u_t;


device_manager_t* global_device_manager;

device_manager_t* device_manager_init(void)
{
    device_manager_t* dm = malloc(sizeof(device_manager_t));
    int i ;

    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
            dm->loadedDevice[i].driver = NULL;
            dm->loadedDevice[i].device = -1;
    }

    return dm;
}

void device_manager_register_driver(device_manager_t* dm, driver_t* driver)
{
    if(driver != NULL && driver->init != NULL)
    {
        driver->deviceManager = dm;
        driver->driver_id=device_manager_get_next_driverId();
        driver->init();
    }
}

driver_id_t device_manager_get_next_driverId()
{
    driver_id_t max=0;
    uint8_t i = 0;
    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
        if(global_device_manager->loadedDevice[i].driver!=NULL&&global_device_manager->loadedDevice[i].driver->driver_id>max)
        {
            max = global_device_manager->loadedDevice[i].driver->driver_id;
        }
    }
    return ++max;
}

device_id_t device_manager_get_next_deviceId(driver_t* driver)
{
    device_id_u_t maxDeviceId;
    int i ;

    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
            if(global_device_manager->loadedDevice[i].driver->driver_id == driver->driver_id)
            {
                if(global_device_manager->loadedDevice[i].device>maxDeviceId.device_id)
                {
                    maxDeviceId.device_id = (uint8_t)global_device_manager->loadedDevice[i].device;
                }
            }
    }

    if(maxDeviceId.device_id==0)
    {
        maxDeviceId.device_info.driver_id = driver->driver_id;
    }

    maxDeviceId.device_info.device_number++;
    return maxDeviceId.device_id;
}

device_id_t device_manager_add_device(device_manager_t* dm, driver_t* driver, void* deviceInfo)
{
    int i ;
    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
        if(dm->loadedDevice[i].driver == NULL)
        {
            dm->loadedDevice[i].driver = driver;
            dm->loadedDevice[i].device = device_manager_get_next_deviceId(driver);
            return dm->loadedDevice[i].device;
        }
    }
    return (device_id_t)0;
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
            return;
        }
    }
}
