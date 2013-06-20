/*
 * main.c
 */

#include <oos/oosio.h>

void main(void)
{
    int i;
    while(1)
    {
        api_print_test();
        //api_printf("Hello World\n");
        for(i = 0; i < 1000000; i++);
    }
}
