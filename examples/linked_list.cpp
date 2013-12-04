#include <Arduino.h>
#include "abSprite.h"
#include "linked_list.h"

/* ll_new
 * 
 * Makes a new empty linked list.
 */
linked_list *ll_new()
{
  linked_list *list = (linked_list *) malloc(sizeof(linked_list));
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  return list;
}

/* ll_length
 * 
 * Returns the number of elements in a linked list.
 */
int ll_length(linked_list *list)
{
  return list->length;
}

/* ll_prepend
 * 
 * Adds an element on to the front of the linked list.
 */
void ll_prepend(linked_list *list, abSprite* x)
{
  ll_node *node = (ll_node *) malloc(sizeof(ll_node));
  node->value = x;
  node->next = list->head;
  list->head = node;
  
  list->length++;

  if (list->tail == NULL) {
    list->tail = node;
  }
}

/* ll_append
 *
 * Adds an element on to the back of the linked list.
 */
void ll_append(linked_list *list, abSprite* x)
{
  ll_node *node = (ll_node *) malloc(sizeof(ll_node));
  node->value = x;
  node->next = NULL;

  if (list->tail == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
  
  list->length++;
}

/* ll_pop_front
 *
 * Removes the element from the front of the list and returns it.
 * NOTE: DO NOT CALL THIS ON AN EMPTY LIST.
 */
abSprite* ll_pop_front(linked_list *list)
{
  abSprite* rv = list->head->value;

  ll_node *tmp = list->head;
  list->head = list->head->next;
  free(tmp);

  if (list->head == NULL) {
    list->tail = NULL;
  }

  list->length--;

  return rv;
}

/* ll_pop_back
 *
 * Removes the element at the back of the list and returns it.
 * NOTE: DO NOT CALL THIS ON AN EMPTY LIST
 */
abSprite* ll_pop_back(linked_list *list)
{
  abSprite* old_tail_value = list->tail->value;

  ll_node *cur_node = list->head;

  if (cur_node->next != NULL) {
    // Since we don't have a `prev` pointer at each node,
    // we'll have to walk through each element until the next
    // node is the tail.
    while (cur_node->next != list->tail) {
      cur_node = cur_node->next;
    }
    // At this point: cur_node->next == list->tail
    // So, we free the old tail node, set the current node
    // to be the new tail, and return the old tail's value.
    ll_node *old_tail = list->tail;
    list->tail = cur_node;
    free(old_tail);

    // this is the new end of the list
    cur_node->next = NULL; 
  } else {
    // 1-element list
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
  }
  
  list->length--;
  return old_tail_value;
}

/* ll_lookup
 * 
 * Returns the element at the index position in the linked list.
 * NOTE: YOU MUST BE SURE index < ll_length(list).
 */
abSprite* ll_lookup(linked_list *list, int index)
{
  ll_node *n = list->head;

  for (int i=0; i<index; i++) {
    n = n->next;
  }
  
  return n->value;
}

/* ll_remove
 *
 * Removes the element with the same address as the parameter from
 * the list
 */
void ll_remove(linked_list *list, abSprite *toRemove) {
  ll_node *curnode = list->head;

  // if head is the sprite, update head ptr
  if (curnode->value == toRemove) {
	list->head = curnode->next;
	if (list->tail == curnode) {
	  list->tail = NULL;
	}
	return;
  }

  while (curnode) {
	if (curnode->next) {
	  // if the next node contains the sprite, remove it
	  if (curnode->next->value == toRemove) {
		curnode->next = curnode->next->next;
		// if last element was the one to remove, update tail
		if (curnode->next == NULL) {
		  list->tail = curnode;
		}
		return;
	  }
	}
	curnode = curnode->next;
  }
}

/* ll_free
 *
 * Cleans up all of the memory for the linked list.
 */
void ll_free(linked_list *list)
{
  while (list->tail != NULL) {
    ll_pop_front(list);
  }

  free(list);
}
