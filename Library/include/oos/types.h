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

typedef void (*irq_listener)(void);

typedef volatile unsigned int * memory_mapped_io_t;

typedef int8_t bool_t;

#define TRUE 1
#define FALSE 0
#ifndef NULL
#define NULL 0
#endif

#define SET_BIT(addr, offset) *addr |= (1 << offset);
#define CLEAR_BIT(addr, offset) *addr &= ~(1 << offset);
#define TOGGLE_BIT(addr, offset) *(addr) ^= (1 << offset);
#define READ_BIT(addr, offset) (*(addr) & (1 << offset));

typedef uint8_t driver_id_t;
typedef uint8_t device_id_t;
typedef union device_id
{
    struct
    {
        uint8_t device_number : 4;
        driver_id_t driver_id : 4;
    }device_info;
    device_id_t device_id;
} device_id_u_t;

typedef void* file_handle_t;
typedef void* dir_handle_t;


#endif /* TYPES_H_ */
