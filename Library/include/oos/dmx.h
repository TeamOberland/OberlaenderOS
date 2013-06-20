/*
 * dmx.h
 *
 *  Created on: 20.06.2013
 *      Author: Manuel
 */

#ifndef DMX_LIB_H_
#define DMX_LIB_H_
#include "types.h"




typedef struct dmx_protocol_par_t {
    uint8_t mode;
    uint8_t green;
    uint8_t blue;
    uint8_t red;
    uint8_t function;
} dmx_protocol_par_t;



#endif /* DMX_LIB_H_ */
