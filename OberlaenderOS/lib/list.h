/*
 * list.h
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#ifndef LIST_H_
#define LIST_H_

#include "types.h"

/** node in the double linked list */
typedef struct node
{
    struct node *prev; //previous node
    struct node *next; //following node
    void *member;
} node_t;

typedef struct list
{
    node_t head; //node head does not contain data just the pointer
} list_t;

#define LIST_INITIALIZE(name) \
         list_t name = { \
                 .head = { \
                         .prev = &(name).head, \
                         .next = &(name).head \
                 } \
         }

#define list_foreach(list) \
        node_t* iterator;\
        for(iterator=(list).head.next;iterator!=&(list).head;iterator=iterator->next)

/*
 * Initalizes the node by setting its pointers to null
 */
void node_initialize(node_t *node);

/*
 * initializes the circulating list by setting the pointers to head
 */
void init_list(list_t *list);
/*
 * inserting node_to_insert before node
 */
void list_insert_before(node_t *node_to_insert, node_t *node);

/*
 *  inserting node_to_insert avter node
 */
void list_insert_after(node_t *node_to_insert, node_t *node);
/*
 * insert at the beginning of the list
 */
void list_prepend(node_t *node_to_insert, list_t *list);
/*
 * insert at the end of the list
 */
void list_append(node_t *node_to_insert, list_t *list);
/*
 * remove element from the list
 */
void list_remove(node_t *node);

/*
 * checks if list is empty
 */
int list_empty(const list_t *list);

node_t *list_first(const list_t *list);

node_t *list_last(list_t *list);

node_t *node_next(node_t* node, list_t *, bool_t);

extern bool_t list_member(const node_t *, const list_t *);
/*
 * counts all elements in this list
 */
extern uint32_t list_count(const list_t *);

#endif /* LIST_H_ */
