/*
 * main.c
 */

#include <oos/oosio.h>

void main(void)
{
    int i;
    while(1)
    {
        api_printf("Hello World__\n");
        for(i = 0; i < 1000000; i++);
    }
}
