/*
 * bitmap.h
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <oos/types.h>
#include <oos/video.h>

/**
 * A structure storing the pixeldata
 */
typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t format;
    uint32_t stride;
    void* data;
} bitmap_t;

/**
 * A structure representing a drawing surface / context
 */
typedef struct
{
    uint32_t x;
    uint32_t y;
    void* currentPixel;
    bitmap_t* target;
} rastport_t;

#define BITMAP_FORMAT_RGB16   6
#define BITMAP_FORMAT_RGB23   9
#define BITMAP_FORMAT_ARGB32  12

#define BITMAP_FORMAT_RGB16_BPP   16
#define BITMAP_FORMAT_RGB23_BPP   24
#define BITMAP_FORMAT_ARGB32_BPP  32

void rastport_draw(rastport_t* rast, video_element_t* elm);


#endif /* BITMAP_H_ */
