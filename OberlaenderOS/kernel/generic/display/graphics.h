/*
 * graphics.h
 *
 *  Created on: 07.05.2013
 *      Author: Daniel
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "../../../lib/types.h"

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t format;
    uint32_t stride;
    void*    pixel;
} bitmap_t;

typedef struct {
    // current drawing info
    uint32_t x;
    uint32_t y;
    void* point;
    uint32_t color;

    // target
    bitmap_t* bitmap;
} graphics_context_t;



#endif /* GRAPHICS_H_ */
