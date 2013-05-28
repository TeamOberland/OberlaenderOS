/*
 * device_manager.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef DEVICE_MANAGER_H_
#define DEVICE_MANAGER_H_

#include "driver.h"

/**
 * A single entry of the device manager. It represents
 * a loaded device combined with the associated driver.
 */
typedef struct {
    device_id_t device; /**< the device which is loaded */
    driver_t* driver;   /**< the driver to control the device */
} device_node_t;

#define MAX_DEVICE_COUNT 10
typedef struct {
    device_node_t loadedDevice[MAX_DEVICE_COUNT];
} device_manager_t;

extern device_manager_t* global_device_manager;

device_manager_t* device_manager_init(void)
{
    device_manager_t* dm = malloc(sizeof(device_manager_t));
    return dm;
}

void device_manager_register_driver(device_manager_t* dm, driver_t* driver)
{
    if(driver != NULL && driver->load_devices != NULL)
    {
        driver->load_devices(dm);
    }
}

void device_manager_add_device(device_manager_t* dm, driver_t* driver, device_id_t device)
{
    int i ;
    for(i = 0; i < MAX_DEVICE_COUNT; i++)
    {
        if(dm->loadedDevice[i].driver == NULL)
        {
            dm->loadedDevice[i].driver = driver;
            dm->loadedDevice[i].device = device;
        }
    }
}




#endif /* DEVICE_MANAGER_H_ */
