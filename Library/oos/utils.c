/*
 * utils.c
 *
 *  Created on: 07.06.2013
 *      Author: Daniel
 */

#include <oos/utils.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* substring(const char* str, uint32_t begin, int32_t len)
{
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin)
        return 0;

    if(len < 0)
    {
        len = strlen(str) - begin;
    }

    if (len == 0 || strlen(str) < (begin + len))
        return 0;

    char* sub = malloc(len + 1);
    memcpy(sub, str + begin, len);
    sub[len] = '\0';
    return sub;
}
