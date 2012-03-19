/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "PWSLinkedList.h"
#include "PWSHeap.h"

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

static void deallocNode(PWSMemory* memory)
{
	ListNode* node = (ListNode*)memory;

	release(node->data), node->data = NULL;
	/* Other list nodes are intentionally not released. */
}

static void deallocList(PWSMemory* memory)
{
	PWSLinkedList* list = (PWSLinkedList*)memory;

	ListNode* node = list->head;
	while(node != NULL) {
		ListNode* tmp_node = node;
		node = node->next;
		release((PWSMemory*)tmp_node);
	}
}

static ListNode* nodeWithData(PWSMemory *data)
{
	ListNode* node = (ListNode*)alloc(sizeof(ListNode), &deallocNode);
	node->data = data;
	return node;
}

PWSLinkedList* linkedList()
{
	return (PWSLinkedList*)alloc(sizeof(PWSLinkedList), &deallocList);
}

/*PWSLinkedList* initLinkedListFromArray(PWSArray* array, int size)
{

}*/

int addLast(PWSLinkedList *list, PWSMemory* data)
{
	ListNode* node = nodeWithData(data);
	node->previous = list->tail;
	if (list->tail != NULL)
		list->tail->next = node;
	if (list->head == NULL)
		list->head = node;
	list->tail = node;

	return list->count++;
}

void addFirst(PWSLinkedList *list, PWSMemory* data)
{
	ListNode* node = nodeWithData(data);
	node->next = list->head;
	if (node->next != NULL)
		node->next->previous = node;
	list->head = node;
	if(list->tail == NULL)
		list->tail = node;
	list->count++;
}

/*int addAtIndex(PWSLinkedList *list, PWSMemory* data, int index)
{
}*/

PWSMemory* getFirst(PWSLinkedList* list)
{
	PWSMemory* data = NULL;
	
	if(list->head != NULL)
		data = list->head->data;

	return data;
}

/*PWSLinkedList* getRest(PWSLinkedList* list)
{
}*/

PWSMemory* getLast(PWSLinkedList* list)
{
	PWSMemory* data = NULL;
	
	if(list->head != NULL)
		data = list->tail->data;

	return data;
}

/*PWSMemory* getByReference(PWSLinkedList* list, PWSMemory* data)
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
}*/

void map(PWSLinkedList* list, void (*mappingFunction)(PWSMemory*))
{
	ListNode* node = list->head;

	while(node != NULL) {
		mappingFunction(node->data);
		node = node->next;
	}
}

void reduce(PWSLinkedList* list, void (*reducingFunction)(PWSMemory*, PWSMemory*), PWSMemory* acc)
{
	ListNode* node = list->head;

	while(node != NULL) {
		reducingFunction(acc, node->data);
		node = node->next;
	}	
}

/*void reverse(PWSLinkedList* list)
{
}i*/

int count(PWSLinkedList *list)
{
	return list->count;
}

bool isEmpty(PWSLinkedList *list)
{
	return list->count == 0;
}
