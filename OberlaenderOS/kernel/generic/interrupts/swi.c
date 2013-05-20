/*
 * swi.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "swi.h"
#include "../../types.h"


#include <time.h>
#include "../../../api/syscalls.h"
#include "../../../api/system.h"

void swi_get_time(timestamp_t *ts)
{
    time_t t;
    time(&t);

    struct tm *tm = localtime(&t);

    ts->sec = tm->tm_sec;
    ts->min = tm->tm_min;
    ts->hour = tm->tm_hour;
    ts->mday = tm->tm_mday;
    ts->mon = tm->tm_mon + 1;
    ts->year = 1900 + tm->tm_year;
    ts->wday = tm->tm_wday;
    ts->yday = tm->tm_yday;
}

#define RESULT_SIZE 26
void swi_format_time(timestamp_t *ts, char* target)
{
    static const char wday_name[][4] = {
       "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
     };
     static const char mon_name[][4] = {
       "Jan", "Feb", "Mar", "Apr", "May", "Jun",
       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
     };

    sprintf(target, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
            wday_name[ts->wday],
            mon_name[ts->mon - 1],
            ts->mday, ts->hour,
            ts->min, ts->sec,
            ts->year);
}

#pragma INTERRUPT(swi_handle, SWI)
bool_t swi_handle(uint32_t swiNumber, uint32_t arg1, uint32_t arg2)
{
    printf("[SWI] SoftwareInterrupt: %i\n", swiNumber);
    switch(swiNumber)
    {
        case SYSCALL_GETTIME:

            swi_get_time((timestamp_t*)arg1);

            break;
        case SYSCALL_FORMATTIME:

            swi_format_time((timestamp_t*)arg1, (char*)arg2);

            break;
        default:
            return FALSE;
    }
    return TRUE;
}
