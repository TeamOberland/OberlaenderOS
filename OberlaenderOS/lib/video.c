/*
 * video.c
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */

#include "video.h"
#include "device.h"
#include <stdlib.h>
#include <string.h>

static device_id_t main_video_device = 0;

static void api_video_draw(video_element_t* elm)
{
    if(main_video_device == 0)
    {
        main_video_device = api_device_build_id(DEVICE_TYPE_VIDEO, 1);
    }
    device_handle_t dh = api_device_open(main_video_device);
    if(dh)
    {
        api_device_write(dh, elm, sizeof(video_element_t));
        api_device_close(dh);
    }
}

void api_video_draw_pixel(color_t color, uint32_t x, uint32_t y, bool_t redraw)
{
    video_element_t* elm = malloc(sizeof(video_element_t));

    elm->redraw = redraw;
    elm->color = color;
    elm->type = VIDEO_ELEMENT_DRAW_PIXEL;

    elm->data.pixel.x = x;
    elm->data.pixel.y = y;

    api_video_draw(elm);

    free(elm);
}

void api_video_fill_rect(color_t color, uint32_t x, uint32_t y, uint32_t w, uint32_t h, bool_t redraw)
{
    video_element_t* elm = malloc(sizeof(video_element_t));

    elm->redraw = redraw;
    elm->color = color;
    elm->type = VIDEO_ELEMENT_FILL_RECT;

    elm->data.rectangle.x = x;
    elm->data.rectangle.y = y;

    elm->data.rectangle.w = w;
    elm->data.rectangle.h = h;

    api_video_draw(elm);

    free(elm);
}

void api_video_fill_line(color_t color, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool_t redraw)
{
    video_element_t* elm = malloc(sizeof(video_element_t));

    elm->redraw = redraw;
    elm->color = color;
    elm->type = VIDEO_ELEMENT_DRAW_LINE;

    elm->data.line.x1 = x1;
    elm->data.line.y1 = y1;

    elm->data.line.x2 = x2;
    elm->data.line.y2 = y2;

    api_video_draw(elm);

    free(elm);
}

void api_video_draw_raw_image(uint32_t x, uint32_t y, char* path, bool_t redraw)
{
    char* pathCopy = malloc(strlen(path) + 1);
    memcpy(pathCopy, path, strlen(path) + 1);

    video_element_t* elm = malloc(sizeof(video_element_t));

    elm->redraw = redraw;
    elm->type = VIDEO_ELEMENT_DRAW_RAW_IMAGE;

    elm->data.raw_image.x = x;
    elm->data.raw_image.y = y;
    elm->data.raw_image.path = pathCopy;

    api_video_draw(elm);

    free(elm);
    free(pathCopy);
}
