/*
 * device.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "device.h"
#include "device_manager.h"
#include "../../../lib/device.h"

device_handle_t device_open(device_manager_t* dm, device_id_t deviceId);
void device_close(device_handle_t handle);
void device_read(device_handle_t handle, void* buffer, uint32_t count);
void device_write(device_handle_t handle, void* buffer, uint32_t count);

#endif /* DEVICE_H_ */
