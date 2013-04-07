
#ifndef LISTHOWTO_H_
#define LISTHOWTO_H_

#include "list.h"
#include "stdio.h"
/*
 * listHowTo.h
 *
 *  Created on: 26.03.2013
 *      Author: Manuel
 */

/*
 * the first element must be node_t that it is possible to use the list in a generic way :-)
 */
typedef struct listItem
{
    node_t node;
    uint32_t value;
} listItem_t;

void tutorial()
{
    list_t *list = (list_t*) malloc(sizeof(list_t));
    init_list(list);

    //initialize a new item
    listItem_t *item1 = (listItem_t*)  malloc(sizeof(listItem_t));
    list_append((node_t*)item1,list);

    //initialize a new item
    listItem_t *item2 = (listItem_t*)  malloc(sizeof(listItem_t));
    list_append((node_t*)item2,list);

    //assign values
    item1->value=20;
    item2->value=30;

    //methods testing
    int i = list_count(list);
    listItem_t *itemFirst= (listItem_t*) list_first(list);
    i= itemFirst->value; //should be 20;

    i = 0;
    list_foreach(*list) {
            i+=1;
            printf("%i",i);
    }

}


#endif /* LISTHOWTO_H_ */

