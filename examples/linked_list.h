#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "abSprite.h"

/* Linked List (of abSprites) */
typedef struct ll_node {
  abSprite *value;
  ll_node *next;
} ll_node;

typedef struct linked_list {
  ll_node *head;
  ll_node *tail;
  int length;
} linked_list;

/* ll_new
 * 
 * Makes a new empty linked list.
 */
linked_list *ll_new();

/* ll_length
 * 
 * Returns the number of elements in a linked list.
 */
int ll_length(linked_list *list);

/* ll_prepend
 * 
 * Adds an element on to the front of the linked list.
 */
void ll_prepend(linked_list *list, abSprite* x);

/* ll_append
 *
 * Adds an element on to the back of the linked list.
 */
void ll_append(linked_list *list, abSprite* x);

/* ll_pop_front
 *
 * Removes the element from the front of the list and returns it.
 * NOTE: DO NOT CALL THIS ON AN EMPTY LIST.
 */
abSprite* ll_pop_front(linked_list *list);

/* ll_pop_back
 *
 * Removes the element at the back of the list and returns it.
 * NOTE: DO NOT CALL THIS ON AN EMPTY LIST
 */
abSprite* ll_pop_back(linked_list *list);

/* ll_lookup
 * 
 * Returns the element at the index position in the linked list.
 * NOTE: YOU MUST BE SURE index < ll_length(list).
 */
abSprite* ll_lookup(linked_list *list, int index);

/* ll_remove
 *
 * Removes the element with the same address as the parameter from
 * the list
 */
void ll_remove(linked_list *list, abSprite *toRemove);

/* ll_free
 *
 * Cleans up all of the memory for the linked list.
 */
void ll_free(linked_list *list);

#endif
