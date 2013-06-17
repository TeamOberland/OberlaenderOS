/*
 * oosio.c
 *
 *  Created on: 15.06.2013
 *      Author: Daniel
 */

#include <stdarg.h>
#include <stdio.h>
#include <oos/types.h>
#include <oos/syscalls.h>

#define API_PRINTF_MAXLENGTH 255
void api_printf(const char* format, ...)
{
    char parsed[API_PRINTF_MAXLENGTH];
    va_list args;
    va_start(args, format);
    vsprintf(parsed, format, args);
    va_end(args);

    syscall(SYSCALL_STDIO_PRINTF, (uint32_t) &parsed, 0, 0, 0, 0);
}
