/*
 * main.c
 */

#include <stdio.h>

void main(void)
{
    int i;
    while(1)
    {
        printf("Hello World\n");
        for(i = 0; i < 1000000; i++);
    }
}
