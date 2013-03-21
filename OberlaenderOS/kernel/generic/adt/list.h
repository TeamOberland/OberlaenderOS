/*
 * list.h
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#ifndef LIST_H_
#define LIST_H_




#define LIST_INITIALIZE(name) \
         list_t name = { \
                 .head = { \
                         .prev = &(name).head, \
                         .next = &(name).head \
                 } \
         }

#define list_get_instance(link, type, member) \
          ((type *) (((void *)(link)) - ((void *) &(((type *) NULL)->member))))

#define list_foreach(list, iterator) \
       for (link_t *iterator = (list).head.next; \
              iterator != &(list).head; iterator = iterator->next)

/** node in the double linked list */
typedef struct node
{
struct node *prev; //previous node
struct node *next; //following node
} node_t;

typedef struct list{
    node_t head; //link head does not contain data just the pointer
} list_t;

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

#endif /* LIST_H_ */
