/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdbool.h>

#include "Heap.h"

typedef struct __LinkedList LinkedList;

/* Returns a retained list. Will call release on all the elements when deallocated. */ 
LinkedList* util_linkedList();
/*LinkedList* initLinkedListFromArray(LinkedList* list, Array* array, int size);*/

/* Add elements, will be retained by the list. */
int util_list_add_last(LinkedList *list, Memory* data);
void util_list_add_first(LinkedList *list, Memory* data);
/* Returns the index where the element is added. If list is too short it will be placed last. */
int util_list_add_at_index(LinkedList *list, Memory* data, int index);

Memory* util_list_first(LinkedList* list);
Memory* util_list_last(LinkedList* list);
Memory* util_list_equal(LinkedList* list, Memory* data, int (*compareFunction)(void*, void*));
Memory* util_list_index(LinkedList* list, int index);
/* The elements isn't copied but they are retained again so all lists can be safely released. */
LinkedList* util_list_rest(LinkedList* list);

/* Remove elements, will be autoreleased by the list (you need to retain the data you want to keep 
 * and empty the pool at some point). */
Memory* util_list_remove_first(LinkedList* list);
Memory* util_list_remove_last(LinkedList* list);
Memory* util_list_remove_equal(LinkedList* list, Memory* data, int (*compareFunction)(void*, void*));
Memory* util_list_remove_index(LinkedList* list, int index);

/* Applies the mapping function on all the elements. The mapping function modify it's input data. */
void util_list_map(LinkedList* list, void (*mappingFunction)(Memory*));
/* The memory acc act both as start value and as the result.
 * The reducing function should accumulate its result in its first parameter. */
void util_list_reduce(LinkedList* list, void (*reducingFunction)(Memory*, Memory*), Memory* acc);

int util_list_count(LinkedList *list);
bool util_list_is_empty(LinkedList *list);

#endif
