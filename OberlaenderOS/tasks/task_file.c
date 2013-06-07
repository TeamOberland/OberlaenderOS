/*
 * task_file.c
 *
 *  Created on: 05.06.2013
 *      Author: Daniel
 */

#include "../lib/file.h"
#include <stdlib.h>
#include <string.h>

#define TEST_DIR "/"
char* concat(const char* c1, const char* c2)
{
    char* c3 = malloc(strlen(c1) + strlen(c2) + 1);
    c3[0] = '\0';
    strcat(c3, c1);
    strcat(c3, c2);
    return c3;
}


void task_file(void)
{
    dir_handle_t dir = api_opendir(TEST_DIR);
    if(!dir)
    {
        printf("Opendir failed!\n");
        return;
    }

    api_file_direntry_t entry;
    file_handle_t f;
    int32_t c;
    char* fname;
    while(api_readdir(&dir, &entry) == 0)
    {
        printf("Found file: %s\n", entry.filename);
        printf("   Size: 0x%x\n", entry.size);
        printf("~~~~ Contents\n");

        fname = concat(TEST_DIR, entry.filename);
        f = api_fopen(fname, "r");
        free(fname);
        if(!f)
        {
            printf("  Could not open file\n");
        }
        else
        {
            while(!api_feof(f))
            {
                c = api_fgetc(f);
                printf("%c", c);
                fflush(stdout);
            }
        }

        printf("\n~~~~ Contents END\n");
    }

    api_closedir(&dir);
}
