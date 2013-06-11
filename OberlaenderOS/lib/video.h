/*
 * video.h
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#ifndef VIDEO_API_H_
#define VIDEO_API_H_

#include "types.h"

typedef union {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } components;
    uint32_t rgb;
} color_t;


#define VIDEO_ELEMENT_DRAW_PIXEL 0
#define VIDEO_ELEMENT_FILL_RECT 1
#define VIDEO_ELEMENT_DRAW_LINE 2
#define VIDEO_ELEMENT_DRAW_RAW_IMAGE 3

typedef struct {

    color_t color;
    uint8_t type;
    bool_t redraw;

    union {

        struct {
            uint32_t x;
            uint32_t y;
        } pixel;

        struct {
            uint32_t x;
            uint32_t y;
            uint32_t w;
            uint32_t h;
        } rectangle;

        struct {
            uint32_t x1;
            uint32_t y1;
            uint32_t x2;
            uint32_t y2;
        } line;

        struct {
            uint32_t x;
            uint32_t y;
            char* path;
        } raw_image;

    } data;



} video_element_t;

void api_video_draw_pixel(color_t color, uint32_t x, uint32_t y, bool_t redraw);
void api_video_fill_rect(color_t color, uint32_t x, uint32_t y, uint32_t w, uint32_t h, bool_t redraw);
void api_video_fill_line(color_t color, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool_t redraw);
void api_video_draw_raw_image(uint32_t x, uint32_t y, char* path, bool_t redraw);


#endif /* VIDEO_H_ */
