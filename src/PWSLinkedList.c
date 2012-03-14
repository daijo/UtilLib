/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>

#include "PWSLinkedList.h"

typedef struct __ListNode ListNode;
struct __ListNode {
	PWSData *data;
	ListNode *previous;
	ListNode *next;
};

struct __PWSLinkedList {
	ListNode *head;
        ListNode *tail;
        int count;
	bool reversed;
};

static ListNode* initNodeWithData(PWSData *data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	memset(node, 0, sizeof(ListNode));
	node->data = data;
	return node;
}

PWSLinkedList* initLinkedList()
{
	PWSLinkedList* list = (PWSLinkedList*)malloc(sizeof(PWSLinkedList));
	memset(list, 0, sizeof(PWSLinkedList)); /* count and reversed = 0/false */
        return list;
}

/*PWSLinkedList* initLinkedListFromArray(PWSArray* array, int size)
{

}*/

void freeLinkedList(PWSLinkedList *list)
{
	free(list); /* For now we assume all elements have been removed and freed. */
}

int addLast(PWSLinkedList *list, PWSData* data)
{
	ListNode* node = initNodeWithData(data);
	node->previous = list->tail;
	if (list->tail != NULL)
		list->tail->next = node;
	list->tail = node;
	return list->count++;
}

/*void addFirst(PWSLinkedList *list, PWSData* data)
{
}

int addAtIndex(PWSLinkedList *list, PWSData* data, int index)
{
}

PWSData* getFirst(PWSLinkedList* list)
{
}

PWSLinkedList* getRest(PWSLinkedList* list)
{
}

PWSData* getLast(PWSLinkedList* list)
{
}

PWSData* getByReference(PWSLinkedList* list, PWSData* data)
{
}

PWSData* getByValue(PWSLinkedList* list, PWSData* data)
{
}

PWSData* getByIndex(PWSLinkedList* list, int index)
{
}

PWSData* removeFirst(PWSLinkedList* list)
{
}

PWSData* removeLast(PWSLinkedList* list)
{
}

PWSData* removeByReference(PWSLinkedList* list, PWSData* data)
{
}

PWSData* removeByValue(PWSLinkedList* list, PWSData* data)
{
}

PWSData* removeByIndex(PWSLinkedList* list, int index)
{
}

void map(PWSLinkedList* list, void* (*mappingFunction)(void*))
{
}

PWSData* reduce(PWSLinkedList* list, void* (*reducingFunction)(void*, void*), void* startValue)
{
}

void reverse(PWSLinkedList* list)
{
}

int count(PWSLinkedList *list)
{
}

bool isEmpty(PWSLinkedList *list)
{
}*/
