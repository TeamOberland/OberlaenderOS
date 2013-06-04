/*
 * driver.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "../../../lib/types.h"

struct _device_manager;
typedef struct {
    // back reference to device manager
    struct _device_manager* deviceManager;
    driver_id_t driver_id;
    // initializing
    void    (*init)(void);
    // device specific functions
    int16_t (*open)(device_id_t device);
    int16_t (*close)(device_id_t device);
    int16_t (*read)(device_id_t device, void* buffer, uint32_t count);
    int16_t (*write)(device_id_t device, void* buffer, uint32_t count);

} driver_t;

#endif /* DRIVER_H_ */
