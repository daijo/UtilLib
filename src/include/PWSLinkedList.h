/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __PWSLINKEDLIST_H__
#define __PWSLINKEDLIST_H__

#include <stdbool.h>

#include "PWSHeap.h"

typedef struct __PWSLinkedList PWSLinkedList;

/* Returns a retained list. Will call release on all the elements when deallocated. */ 
PWSLinkedList* linkedList();
/*PWSLinkedList* initLinkedListFromArray(PWSLinkedList* list, PWSArray* array, int size);*/

/* Add elements, will be retained by the list. */
int addLast(PWSLinkedList *list, PWSMemory* data);
void addFirst(PWSLinkedList *list, PWSMemory* data);
/* Returns the index where the element is added. If list is too short it will be placed last. */
int addAtIndex(PWSLinkedList *list, PWSMemory* data, int index);

PWSMemory* getFirst(PWSLinkedList* list);
/* The elements isn't copied but they are retained again so all lists can be safely released. */
PWSLinkedList* getRest(PWSLinkedList* list);
PWSMemory* getLast(PWSLinkedList* list);
PWSMemory* getEqual(PWSLinkedList* list, PWSMemory* data, int (*compareFunction)(void*, void*));
PWSMemory* getByIndex(PWSLinkedList* list, int index);

/* Remove elements, will be autoreleased by the list. */
PWSMemory* removeFirst(PWSLinkedList* list);
PWSMemory* removeLast(PWSLinkedList* list);
PWSMemory* removeEqual(PWSLinkedList* list, PWSMemory* data, int (*compareFunction)(void*, void*));
PWSMemory* removeByIndex(PWSLinkedList* list, int index);

/* Applies the mapping function on all the elements. The mapping function modify it's input data. */
void map(PWSLinkedList* list, void (*mappingFunction)(PWSMemory*));
/* The memory acc act both as start value and as the result.
 * The reducing function should accumulate its result in its first parameter. */
void reduce(PWSLinkedList* list, void (*reducingFunction)(PWSMemory*, PWSMemory*), PWSMemory* acc);

int count(PWSLinkedList *list);
bool isEmpty(PWSLinkedList *list);

#endif
