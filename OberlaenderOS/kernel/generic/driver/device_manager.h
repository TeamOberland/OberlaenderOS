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
typedef struct _device_manager {
    device_id_t nextDeviceId;
    device_node_t loadedDevice[MAX_DEVICE_COUNT];
} device_manager_t;

extern device_manager_t* global_device_manager;

device_manager_t* device_manager_init(void);

void device_manager_register_driver(device_manager_t* dm, driver_t* driver);

device_id_t device_manager_add_device(device_manager_t* dm, driver_t* driver, void* deviceInfo);
void device_manager_remove_device(device_manager_t* dm, driver_t* driver, device_id_t device);

#endif /* DEVICE_MANAGER_H_ */
