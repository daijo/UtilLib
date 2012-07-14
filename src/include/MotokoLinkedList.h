/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __MotokoLINKEDLIST_H__
#define __MotokoLINKEDLIST_H__

#include <stdbool.h>

#include "MotokoHeap.h"

typedef struct __MotokoLinkedList MotokoLinkedList;

/* Returns a retained list. Will call release on all the elements when deallocated. */ 
MotokoLinkedList* linkedList();
/*MotokoLinkedList* initLinkedListFromArray(MotokoLinkedList* list, MotokoArray* array, int size);*/

/* Add elements, will be retained by the list. */
int addLast(MotokoLinkedList *list, MotokoMemory* data);
void addFirst(MotokoLinkedList *list, MotokoMemory* data);
/* Returns the index where the element is added. If list is too short it will be placed last. */
int addAtIndex(MotokoLinkedList *list, MotokoMemory* data, int index);

MotokoMemory* getFirst(MotokoLinkedList* list);
MotokoMemory* getLast(MotokoLinkedList* list);
MotokoMemory* getEqual(MotokoLinkedList* list, MotokoMemory* data, int (*compareFunction)(void*, void*));
MotokoMemory* getByIndex(MotokoLinkedList* list, int index);
/* The elements isn't copied but they are retained again so all lists can be safely released. */
MotokoLinkedList* getRest(MotokoLinkedList* list);

/* Remove elements, will be autoreleased by the list (you need to retain the data you want to keep 
 * and empty the pool at some point). */
MotokoMemory* removeFirst(MotokoLinkedList* list);
MotokoMemory* removeLast(MotokoLinkedList* list);
MotokoMemory* removeEqual(MotokoLinkedList* list, MotokoMemory* data, int (*compareFunction)(void*, void*));
MotokoMemory* removeByIndex(MotokoLinkedList* list, int index);

/* Applies the mapping function on all the elements. The mapping function modify it's input data. */
void map(MotokoLinkedList* list, void (*mappingFunction)(MotokoMemory*));
/* The memory acc act both as start value and as the result.
 * The reducing function should accumulate its result in its first parameter. */
void reduce(MotokoLinkedList* list, void (*reducingFunction)(MotokoMemory*, MotokoMemory*), MotokoMemory* acc);

int count(MotokoLinkedList *list);
bool isEmpty(MotokoLinkedList *list);

#endif
