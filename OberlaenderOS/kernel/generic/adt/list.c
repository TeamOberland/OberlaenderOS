/*
 * list.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "list.h"
#include "../../types.h"
bool_t list_member(const node_t *node, const list_t *list)
{
    bool_t found = FALSE;
    node_t *hlp = list->head.next;

    while (hlp != &list->head) {
        if (hlp == node) {
            found = TRUE;
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
void node_initialize(node_t *node)
{
    node->next=NULL;
    node->prev=NULL;
    node->member=NULL;
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

    node_initialize(node);
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

node_t *node_next(node_t* node, list_t * list, bool_t circular)
{
    node_t* temp = node->next;
    if(temp==&list->head)
    {
        temp=temp->next;
        if(!circular || temp==&list->head)
            return NULL;
    }
    return temp;
}

