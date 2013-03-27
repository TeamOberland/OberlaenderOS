
#ifndef LISTHOWTO_H_
#define LISTHOWTO_H_

#include "list.h"
/*
 * listHowTo.h
 *
 *  Created on: 26.03.2013
 *      Author: Manuel
 */


typedef struct listItem
{
    node_t node;
    uint32_t value;
} listItem_t;

void tutorial()
{
    list_t *list = malloc(sizeof(list_t));
    init_list(list);
    listItem_t *item = malloc(sizeof(listItem_t));
    list_append(item,list);

    int i = list_count(list);
    printf(i);

}


#endif /* LISTHOWTO_H_ */
