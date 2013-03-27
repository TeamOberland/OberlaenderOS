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

typedef volatile unsigned int * memory_mapped_io_t;

typedef int8_t bool_t;

#define TRUE 1
#define FALSE 0

#define NULL ((void*)0)

#endif /* TYPES_H_ */
