/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __PWSLINKEDLIST_H__
#define __PWSLINKEDLIST_H__

#include <stdbool.h>

#include "PWSData.h"

typedef struct __PWSLinkedList PWSLinkedList;

PWSLinkedList* initLinkedList();
/*PWSLinkedList* initLinkedListFromArray(PWSArray* array, int size);*/
void freeLinkedList(PWSLinkedList *list); /* free remaining data? */

int addLast(PWSLinkedList *list, PWSData* data);
void addFirst(PWSLinkedList *list, PWSData* data);
int addAtIndex(PWSLinkedList *list, PWSData* data, int index);

PWSData* getFirst(PWSLinkedList* list);
PWSLinkedList* getRest(PWSLinkedList* list); /* deep copy data? */
PWSData* getLast(PWSLinkedList* list);
PWSData* getByReference(PWSLinkedList* list, PWSData* data);
PWSData* getByValue(PWSLinkedList* list, PWSData* data, int (*compareFunction)(void*, void*));
PWSData* getByIndex(PWSLinkedList* list, int index);

PWSData* removeFirst(PWSLinkedList* list);
PWSData* removeLast(PWSLinkedList* list);
PWSData* removeByReference(PWSLinkedList* list, PWSData* data);
PWSData* removeByValue(PWSLinkedList* list, PWSData* data, int (*compareFunction)(void*, void*));
PWSData* removeByIndex(PWSLinkedList* list, int index);

void map(PWSLinkedList* list, void* (*mappingFunction)(void*));
PWSData* reduce(PWSLinkedList* list, void* (*reducingFunction)(void*, void*), void* startValue);

void reverse(PWSLinkedList* list);

int count(PWSLinkedList *list);
bool isEmpty(PWSLinkedList *list);

#endif
