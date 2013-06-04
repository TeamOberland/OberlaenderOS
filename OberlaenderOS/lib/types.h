/*
 * types.h
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

typedef void (*irq_listener)(void);

typedef volatile unsigned int * memory_mapped_io_t;

typedef int8_t bool_t;

#define TRUE 1
#define FALSE 0
typedef uint8_t driver_id_t;
typedef uint8_t device_id_t;

#endif /* TYPES_H_ */
