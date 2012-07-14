/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "MotokoLinkedList.h"
#include "MotokoHeap.h"

typedef struct __ListNode ListNode;
struct __ListNode {
	MotokoMemory *data;
	ListNode *previous;
	ListNode *next;
};

struct __MotokoLinkedList {
	ListNode *head;
        ListNode *tail;
        int count;
	bool reversed;
};

static void deallocNode(MotokoMemory* memory)
{
	ListNode* node = (ListNode*)memory;

	release(node->data), node->data = NULL;
	/* Other list nodes are intentionally not released. */
}

static void deallocList(MotokoMemory* memory)
{
	MotokoLinkedList* list = (MotokoLinkedList*)memory;

	ListNode* node = list->head;
	while(node != NULL) {
		ListNode* tmp_node = node;
		node = node->next;
		release((MotokoMemory*)tmp_node);
	}
}

static ListNode* nodeWithData(MotokoMemory *data)
{
	ListNode* node = (ListNode*)alloc(sizeof(ListNode), &deallocNode);
	node->data = data;
	return node;
}

MotokoLinkedList* linkedList()
{
	return (MotokoLinkedList*)alloc(sizeof(MotokoLinkedList), &deallocList);
}

/*MotokoLinkedList* initLinkedListFromArray(MotokoLinkedList* list, MotokoArray* array, int size)
{

}*/

int addLast(MotokoLinkedList *list, MotokoMemory* data)
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

void addFirst(MotokoLinkedList *list, MotokoMemory* data)
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

int addAtIndex(MotokoLinkedList *list, MotokoMemory* data, int index)
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

MotokoMemory* getFirst(MotokoLinkedList* list)
{
	MotokoMemory* data = NULL;
	
	if(list->head != NULL)
		data = list->head->data;

	return data;
}

MotokoLinkedList* getRest(MotokoLinkedList* list)
{
	MotokoLinkedList* rest = linkedList();

	if(list->head != NULL) {	
		rest->head = list->head->next;
	}
	rest->tail = list->tail;

	ListNode* node = rest->head;

	while(node != NULL) {
		retain((MotokoMemory*)node);
		node = node->next;
	}

	return rest;
}

MotokoMemory* getLast(MotokoLinkedList* list)
{
	MotokoMemory* data = NULL;
	
	if(list->head != NULL)
		data = list->tail->data;

	return data;
}

MotokoMemory* getEqual(MotokoLinkedList* list, MotokoMemory* data, int (*compareFunction)(void*, void*))
{
	MotokoMemory* result = NULL;

	ListNode* node = list->head;

	while(node != NULL && result == NULL) {

		if(compareFunction(data, node->data) == 0) {
			result = node->data;
		}
		node = node->next;
	}
	
	return result;
}

MotokoMemory* getByIndex(MotokoLinkedList* list, int index)
{
	MotokoMemory* data = NULL;

	ListNode* node = list->head;

	for (int i = 0; i <= index && node != NULL; i++) {
		data = node->data;
		node = node->next;
	}

	return data;
}

MotokoMemory* removeFirst(MotokoLinkedList* list)
{
	MotokoMemory* data = NULL;

	if(list->head != NULL) {
		ListNode* nodeToRemove = list->head;
		data = list->head->data;
		list->head = list->head->next;
		autorelease((MotokoMemory*)nodeToRemove);
		list->count--;
	}

	return data;
}

/*MotokoMemory* removeLast(MotokoLinkedList* list)
{
}

MotokoMemory* removeByReference(MotokoLinkedList* list, MotokoMemory* data)
{
}

MotokoMemory* removeByValue(MotokoLinkedList* list, MotokoMemory* data)
{
}

MotokoMemory* removeByIndex(MotokoLinkedList* list, int index)
{
}*/

void map(MotokoLinkedList* list, void (*mappingFunction)(MotokoMemory*))
{
	ListNode* node = list->head;

	while(node != NULL) {
		mappingFunction(node->data);
		node = node->next;
	}
}

void reduce(MotokoLinkedList* list, void (*reducingFunction)(MotokoMemory*, MotokoMemory*), MotokoMemory* acc)
{
	ListNode* node = list->head;

	while(node != NULL) {
		reducingFunction(acc, node->data);
		node = node->next;
	}	
}

int count(MotokoLinkedList *list)
{
	return list->count;
}

bool isEmpty(MotokoLinkedList *list)
{
	return list->count == 0;
}
