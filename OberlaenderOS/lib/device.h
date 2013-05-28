/*
 * device.h
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#ifndef DEVICE_API_H_
#define DEVICE_API_H_

#include "types.h"

typedef int16_t device_handle_t;

device_handle_t api_device_open(device_id_t device);
void api_device_close(device_handle_t handle);
void api_device_read(device_handle_t handle, void* buffer, uint32_t count);
void api_device_write(device_handle_t handle, void* buffer, uint32_t count);


#endif /* DEVICE_H_ */
