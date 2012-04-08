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

/*PWSLinkedList* initLinkedListFromArray(PWSLinkedList* list, PWSArray* array, int size)
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

int addAtIndex(PWSLinkedList *list, PWSMemory* data, int index)
{
	ListNode* node = list->head;
	ListNode* newNode;
	int acctualIndex = 0;

	if(0 == index) {
		addFirst(list, data);
	} else if (list->count <= index) {
		addLast(list, data);
		acctualIndex = list->count - 1;
	} else {

		for (int i = 0; i < index && node != NULL; i++) {
			node = node->next;
			acctualIndex = i;
		}

		newNode = nodeWithData(data);

		newNode->next = node;
		newNode->previous = node->previous;

		node->previous->next = newNode;
		node->previous = newNode;

		list->count++;
	}

	return acctualIndex;
}

PWSMemory* getFirst(PWSLinkedList* list)
{
	PWSMemory* data = NULL;
	
	if(list->head != NULL)
		data = list->head->data;

	return data;
}

PWSLinkedList* getRest(PWSLinkedList* list)
{
	PWSLinkedList* rest = linkedList();

	if(list->head != NULL) {	
		rest->head = list->head->next;
	}
	rest->tail = list->tail;

	ListNode* node = rest->head;

	while(node != NULL) {
		retain((PWSMemory*)node);
		node = node->next;
	}

	return rest;
}

PWSMemory* getLast(PWSLinkedList* list)
{
	PWSMemory* data = NULL;
	
	if(list->head != NULL)
		data = list->tail->data;

	return data;
}

PWSMemory* getEqual(PWSLinkedList* list, PWSMemory* data, int (*compareFunction)(void*, void*))
{
	PWSMemory* result = NULL;

	ListNode* node = list->head;

	while(node != NULL && result == NULL) {

		if(compareFunction(data, node->data) == 0) {
			result = node->data;
		}
		node = node->next;
	}
	
	return result;
}

PWSMemory* getByIndex(PWSLinkedList* list, int index)
{
	PWSMemory* data = NULL;

	ListNode* node = list->head;

	for (int i = 0; i <= index && node != NULL; i++) {
		data = node->data;
		node = node->next;
	}

	return data;
}

PWSMemory* removeFirst(PWSLinkedList* list)
{
	PWSMemory* data = NULL;

	if(list->head != NULL) {
		ListNode* tmp_node = list->head;
		data = list->head->data;
		list->head = list->head->next;
		autorelease((PWSMemory*)tmp_node);
		list->count--;
	}

	return data;
}

/*PWSMemory* removeLast(PWSLinkedList* list)
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

int count(PWSLinkedList *list)
{
	return list->count;
}

bool isEmpty(PWSLinkedList *list)
{
	return list->count == 0;
}
