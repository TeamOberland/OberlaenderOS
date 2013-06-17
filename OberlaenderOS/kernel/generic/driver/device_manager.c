/*
 * device_manager.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "device_manager.h"
#include <oos/device.h>
#include <stdlib.h>

device_manager_t* global_device_manager;

device_manager_t* device_manager_init(void)
{
    device_manager_t* dm = malloc(sizeof(device_manager_t));
    int i,j;

    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
            dm->loadedDevice[i].driver = NULL;
            dm->loadedDevice[i].device = 0;
            for(j = 0; j< MAX_HANDLE_COUNT; j++)
            {
                    dm->loadedDevice[i].handles[j]=-1;
            }
    }
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

device_id_t device_manager_get_next_deviceId(driver_t* driver)
{
    device_id_u_t maxDeviceId;
    maxDeviceId.device_id=0;
    int i ;

    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
            if(global_device_manager->loadedDevice[i].driver!=NULL&&global_device_manager->loadedDevice[i].driver->driver_id == driver->driver_id)
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
        maxDeviceId.device_info.device_number =0;
    }

    maxDeviceId.device_info.device_number++;
    return maxDeviceId.device_id;
}

device_node_t* device_manager_get_device_node(device_manager_t* dm,device_id_t device)
{
    int i;
    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
        if(dm->loadedDevice[i].device==device)
        {
            return &dm->loadedDevice[i];
        }
    }

    return NULL;
}

device_handle_t device_manager_create_device_handle(device_manager_t* dm, device_id_t deviceId)
{
    device_node_t* node = device_manager_get_device_node(dm,deviceId);
    if(node!=NULL)
    {
        device_handle_t handle;
        int i;
        for(i = 0; i < MAX_HANDLE_COUNT; i++)
        {
            if(node->handles[i]==-1)
            {
                handle = (deviceId<<8)+i+1;
                return handle;
            }
        }
    }
    else
    {

    }

    return -1;
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
