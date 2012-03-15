/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>

#include "PWSLinkedList.h"

typedef struct __ListNode ListNode;
struct __ListNode {
	PWSMemory *data;
	ListNode *previous;
	ListNode *next;
};

struct __PWSLinkedList {
	ListNode *head;
        ListNode *tail;
        int count;
	bool reversed;
};

static ListNode* initNodeWithData(PWSMemory *data)
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

int addLast(PWSLinkedList *list, PWSMemory* data)
{
	ListNode* node = initNodeWithData(data);
	node->previous = list->tail;
	if (list->tail != NULL)
		list->tail->next = node;
	list->tail = node;
	return list->count++;
}

/*void addFirst(PWSLinkedList *list, PWSMemory* data)
{
}

int addAtIndex(PWSLinkedList *list, PWSMemory* data, int index)
{
}

PWSMemory* getFirst(PWSLinkedList* list)
{
}

PWSLinkedList* getRest(PWSLinkedList* list)
{
}

PWSMemory* getLast(PWSLinkedList* list)
{
}

PWSMemory* getByReference(PWSLinkedList* list, PWSMemory* data)
{
}

PWSMemory* getByValue(PWSLinkedList* list, PWSMemory* data)
{
}

PWSMemory* getByIndex(PWSLinkedList* list, int index)
{
}

PWSMemory* removeFirst(PWSLinkedList* list)
{
}

PWSMemory* removeLast(PWSLinkedList* list)
{
}

PWSMemory* removeByReference(PWSLinkedList* list, PWSMemory* data)
{
}

PWSMemory* removeByValue(PWSLinkedList* list, PWSMemory* data)
{
}

PWSMemory* removeByIndex(PWSLinkedList* list, int index)
{
}

void map(PWSLinkedList* list, void* (*mappingFunction)(void*))
{
}

PWSMemory* reduce(PWSLinkedList* list, void* (*reducingFunction)(void*, void*), void* startValue)
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
