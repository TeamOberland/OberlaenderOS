/*
 * task_display.c
 *
 *  Created on: 10.06.2013
 *      Author: Daniel
 */
#include "../lib/video.h"
#include "../lib/types.h"

void task_video(void)
{
    api_video_draw_raw_image( 0, 0, "/sd/Banner.raw", TRUE);
//    color_t c;
//    c.rgb = 0xFF0000FF;
//    api_video_fill_rect(c, 0,0, 1024, 768, TRUE);
    while (TRUE)
        ;
}
