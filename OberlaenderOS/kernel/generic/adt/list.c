#include "list.h"
#include "stdint.h"

/*
 * list.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */




uint32_t list_member(const node_t *node, const list_t *list)
{
    bool found = false;
    node_t *hlp = list->head.next;

    while (hlp != &list->head) {
        if (hlp == node_t) {
            found = true;
            break;
        }
        hlp = hlp->next;
    }

    return found;
}

uint32_t list_count(const list_t *list)
{
    unsigned int count = 0;

    list_foreach(*list, link) {
        count++;
    }

    return count;
}
