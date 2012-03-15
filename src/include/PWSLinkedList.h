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
PWSLinkedList* initLinkedList();
/*PWSLinkedList* initLinkedListFromArray(PWSArray* array, int size);*/
void freeLinkedList(PWSLinkedList *list); /* Deprecated, call release directly on list. */

/* Add elements, will be retained by the list. */
int addLast(PWSLinkedList *list, PWSMemory* data);
void addFirst(PWSLinkedList *list, PWSMemory* data);
int addAtIndex(PWSLinkedList *list, PWSMemory* data, int index);

PWSMemory* getFirst(PWSLinkedList* list);
/* The elements isn't copied but they are retained again so all list can be safely released. */
PWSLinkedList* getRest(PWSLinkedList* list);

PWSMemory* getLast(PWSLinkedList* list);
PWSMemory* getByReference(PWSLinkedList* list, PWSMemory* data);
PWSMemory* getByValue(PWSLinkedList* list, PWSMemory* data, int (*compareFunction)(void*, void*));
PWSMemory* getByIndex(PWSLinkedList* list, int index);

/* Remove elements, will me autoreleased by the list. */
PWSMemory* removeFirst(PWSLinkedList* list);
PWSMemory* removeLast(PWSLinkedList* list);
PWSMemory* removeByReference(PWSLinkedList* list, PWSMemory* data);
PWSMemory* removeByValue(PWSLinkedList* list, PWSMemory* data, int (*compareFunction)(void*, void*));
PWSMemory* removeByIndex(PWSLinkedList* list, int index);

void map(PWSLinkedList* list, void* (*mappingFunction)(void*));
PWSMemory* reduce(PWSLinkedList* list, void* (*reducingFunction)(void*, void*), void* startValue);

void reverse(PWSLinkedList* list);

int count(PWSLinkedList *list);
bool isEmpty(PWSLinkedList *list);

#endif
