/*
 * bitmap.c
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#include "bitmap.h"
#include "../../lib/video.h"
#include "../../kernel/generic/io/mount.h"
#include <stdlib.h>

// TODO: the drawing/pixel setting is quite bullshit.
// we need better pixel offset calculation

static uint32_t rastport_get_bpp(rastport_t* rast)
{
    switch(rast->target->format)
    {
        case BITMAP_FORMAT_RGB16:
            return 16;
        case BITMAP_FORMAT_RGB23:
            return 24;
        case BITMAP_FORMAT_ARGB32:
            return 32;
    }
    return 0;
}

static inline void rastport_set_color(void* px, color_t c)
{
    *((color_t*)px) = c;
}

static void rastport_move_to(rastport_t* rast, uint32_t x, uint32_t y)
{
    uint32_t bytePerPixel = rastport_get_bpp(rast) / 8;
    rast->x = x;
    rast->y = y;
    rast->currentPixel = ((uint8_t*) rast->target->data) + (x * bytePerPixel) + (y * rast->target->stride);
}

static void rastport_draw_pixel(rastport_t* rast, video_element_t* elm)
{
    rastport_move_to(rast, elm->data.pixel.x, elm->data.pixel.y);
    rastport_set_color(rast->currentPixel, elm->color);
}

static uint32_t max(uint32_t x, uint32_t y)
{
    return x > y ? x : y;
}

static uint32_t min(uint32_t x, uint32_t y)
{
    return x < y ? x : y;
}

#define RAW_IMAGE_BYTE_PER_PIXEL 4
static void rastport_raw_image(rastport_t* rast, video_element_t* elm)
{
    file_handle_t fh = mount_open(elm->data.raw_image.path, "rb");
    if(!fh)
    {
        return;
    }

    // read image size
    uint32_t width = 0;
    uint32_t height = 0;
    mount_read(&width, sizeof(uint32_t), 1, fh);
    mount_read(&height, sizeof(uint32_t), 1, fh);

    // calculate the intersection of the bounding rects
    uint32_t x1 = max(0, elm->data.raw_image.x);
    uint32_t x2 = min(rast->target->width, elm->data.raw_image.x + width);
    uint32_t y1 = max(0, elm->data.raw_image.y);
    uint32_t y2 = min(rast->target->height, elm->data.raw_image.y + height);

    // if there is an intersection we copy the pixels row by row
    uint32_t targetW = x2 - x1;
    uint32_t targetH = y2 - y1;
    uint32_t bufSize = targetW * RAW_IMAGE_BYTE_PER_PIXEL;
    uint8_t* buf = malloc(bufSize);
    uint32_t row;

    if (x2 >= x1 && y2 >= y1)
    {
        for(row = 0; row < targetH; row++)
        {
            // read a row
            mount_read(buf, bufSize, 1, fh);
            // move target pointer
            rastport_move_to(rast, elm->data.rectangle.x, elm->data.rectangle.y + row);
            // copy the data
            memcpy(rast->currentPixel, buf, bufSize);
        }
    }
    free(buf);
    mount_close(fh);
}

static void rastport_fill_rect(rastport_t* rast, video_element_t* elm)
{
    if(elm->data.rectangle.h == 0 || elm->data.rectangle.w == 0) return;

    uint32_t x,y;

    // manually fill first row
    rastport_move_to(rast, elm->data.rectangle.x, elm->data.rectangle.y);
    void* src = rast->currentPixel;
    for(x = 0; x < elm->data.rectangle.w; x++)
    {
        rastport_move_to(rast, elm->data.rectangle.x + x, elm->data.rectangle.y);
        rastport_set_color(rast->currentPixel, elm->color);
    }

    // memcopy further rows
    for(y = 1; y < elm->data.rectangle.h; y++)
    {
        rastport_move_to(rast, elm->data.rectangle.x, elm->data.rectangle.y + y);
        memcpy(rast->currentPixel, src, rast->target->stride);
    }

    // ensure correct position
    rastport_move_to(rast, elm->data.rectangle.x, elm->data.rectangle.y);
}

static void rastport_draw_line(rastport_t* rast, video_element_t* elm)
{
    uint32_t x1,y1,x2,y2;
    uint32_t dx, dy;
    uint32_t stepY, stepX;
    uint32_t err, err2;

    x1 = elm->data.line.x1;
    y1 = elm->data.line.y1;
    x2 = elm->data.line.x2;
    y2 = elm->data.line.y2;

    dx = abs(x1 - x2);
    dy = abs(y1 - y2);

    stepX = (x1 < x2) ? 1 : -1;
    stepY = (y1 < y2) ? 1 : -1;

    rastport_move_to(rast, x1, y2);

    while(x1 != x2 || y1 != y2)
    {
        rastport_move_to(rast, x1, y1);
        rastport_set_color(rast->currentPixel, elm->color);

        err2 = 2*err;

        if(err2 > dy)
        {
            err += dy;
            x1 += stepX;
        }

        if(err2 < dx)
        {
            err += dx;
            y1 = stepY;
        }
    }
}

void rastport_draw(rastport_t* rast, video_element_t* elm)
{
    switch (elm->type)
    {
        case VIDEO_ELEMENT_DRAW_PIXEL:
            rastport_draw_pixel(rast, elm);
            break;
        case VIDEO_ELEMENT_FILL_RECT:
            rastport_fill_rect(rast, elm);
            break;
        case VIDEO_ELEMENT_DRAW_LINE:
            rastport_draw_line(rast, elm);
            break;
        case VIDEO_ELEMENT_DRAW_RAW_IMAGE:
            rastport_raw_image(rast, elm);
            break;
    }
}
