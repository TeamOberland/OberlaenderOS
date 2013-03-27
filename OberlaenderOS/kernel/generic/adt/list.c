/*
 * list.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "list.h"

bool list_member(const node_t *node, const list_t *list)
{
    bool found = false;
    node_t *hlp = list->head.next;

    while (hlp != &list->head) {
        if (hlp == node) {
            found = true;
            break;
        }
        hlp = hlp->next;
    }

    return found;
}

uint32_t list_count(const list_t *list)
{
    uint32_t count = 0;

        list_foreach(*list) {
                count++;
        }

    return count;
}

/*
 * Initalizes the node by setting its pointers to null
 */
void link_initialize(node_t *node)
{
    node->next=NULL;
    node->prev=NULL;
}

/*
 * initializes the circulating list by setting the pointers to head
 */
void init_list(list_t *list)
{
    list->head.next=&list->head;
    list->head.prev=&list->head;
}

/*
 * inserting node_to_insert before node
 */
void list_insert_before(node_t *node_to_insert, node_t *node)
{
    node_to_insert->next=node;
    node_to_insert->prev=node->prev;
    node->prev->next=node_to_insert;
    node->prev=node_to_insert;
}

/*
 *  inserting node_to_insert avter node
 */
void list_insert_after(node_t *node_to_insert, node_t *node)
{
    node_to_insert->prev = node;
    node_to_insert->next = node->next;
    node->next->prev = node_to_insert;
    node->next = node_to_insert;
}

/*
 * insert at the beginning of the list
 */
 void list_prepend(node_t *node_to_insert, list_t *list)
{
        list_insert_after(node_to_insert, &list->head);
}

 /*
  * insert at the end of the list
  */
void list_append(node_t *node_to_insert, list_t *list)
{
        list_insert_before(node_to_insert, &list->head);
}

/*
 * remove element from the list
 */
void list_remove(node_t *node)
{
    if ((node->prev != NULL) && (node->next != NULL)) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    link_initialize(node);
}

/*
 * checks if list is empty
 */
int list_empty(const list_t *list)
{
    return (list->head.next == &list->head);
}

/*
 * counts all elements in this list
 */
node_t *list_first(const list_t *list)
{
    return ((list->head.next == &list->head) ? NULL : list->head.next);
}

node_t *list_last(list_t *list)
{
    return ((list->head.prev == &list->head) ? NULL : list->head.prev);
}

