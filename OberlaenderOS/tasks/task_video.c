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
    while (TRUE)
        ;
}
