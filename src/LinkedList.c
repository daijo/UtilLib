/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "LinkedList.h"
#include "Heap.h"

typedef struct __ListNode ListNode;
struct __ListNode {
	Memory *data;
	ListNode *previous;
	ListNode *next;
};

struct __LinkedList {
	ListNode *head;
        ListNode *tail;
        int count;
	bool reversed;
};

static void deallocNode(Memory* memory)
{
	ListNode* node = (ListNode*)memory;

	util_release(node->data), node->data = NULL;
	/* Other list nodes are intentionally not released. */
}

static void deallocList(Memory* memory)
{
	LinkedList* list = (LinkedList*)memory;

	ListNode* node = list->head;
	while(node != NULL) {
		ListNode* tmp_node = node;
		node = node->next;
		util_release((Memory*)tmp_node);
	}
}

static ListNode* nodeWithData(Memory *data)
{
	ListNode* node = (ListNode*)util_alloc(sizeof(ListNode), &deallocNode);
	node->data = data;
	return node;
}

LinkedList* util_linkedList()
{
	return (LinkedList*)util_alloc(sizeof(LinkedList), &deallocList);
}

/*LinkedList* initLinkedListFromArray(LinkedList* list, Array* array, int size)
{

}*/

int util_list_add_last(LinkedList *list, Memory* data)
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

void util_list_add_first(LinkedList *list, Memory* data)
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

int util_list_add_at_index(LinkedList *list, Memory* data, int index)
{
	ListNode* node = list->head;
	ListNode* newNode;
	int acctualIndex = 0;

	if(0 == index) {
		util_list_add_first(list, data);
	} else if (list->count <= index) {
		util_list_add_last(list, data);
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

Memory* util_list_first(LinkedList* list)
{
	Memory* data = NULL;
	
	if(list->head != NULL)
		data = list->head->data;

	return data;
}

LinkedList* util_list_rest(LinkedList* list)
{
	LinkedList* rest = util_linkedList();

	if(list->head != NULL) {	
		rest->head = list->head->next;
	}
	rest->tail = list->tail;

	ListNode* node = rest->head;

	while(node != NULL) {
		util_retain((Memory*)node);
		node = node->next;
	}

	return rest;
}

Memory* util_list_last(LinkedList* list)
{
	Memory* data = NULL;
	
	if(list->head != NULL)
		data = list->tail->data;

	return data;
}

Memory* util_list_equal(LinkedList* list, Memory* data,
		int (*compareFunction)(void*, void*))
{
	Memory* result = NULL;

	ListNode* node = list->head;

	while(node != NULL && result == NULL) {

		if(compareFunction(data, node->data) == 0) {
			result = node->data;
		}
		node = node->next;
	}
	
	return result;
}

Memory* util_list_index(LinkedList* list, int index)
{
	Memory* data = NULL;

	ListNode* node = list->head;

	for (int i = 0; i <= index && node != NULL; i++) {
		data = node->data;
		node = node->next;
	}

	return data;
}

Memory* util_list_remove_first(LinkedList* list)
{
	Memory* data = NULL;

	if(list->head != NULL) {
		ListNode* nodeToRemove = list->head;
		data = list->head->data;
		list->head = list->head->next;
		util_autorelease((Memory*)nodeToRemove);
		list->count--;
	}

	return data;
}

Memory* util_list_remove_last(LinkedList* list)
{
	Memory* data = NULL;

	if(list->tail != NULL) {
		ListNode* nodeToRemove = list->tail;
		data = list->tail->data;
		list->tail = list->tail->previous;
		util_autorelease((Memory*)nodeToRemove);
		list->count--;
	}

	return data;
}

/*Memory* removeByReference(LinkedList* list, Memory* data)
{
}

Memory* removeByValue(LinkedList* list, Memory* data)
{
}

Memory* removeByIndex(LinkedList* list, int index)
{
}*/

void util_list_map(LinkedList* list, void (*mappingFunction)(Memory*))
{
	ListNode* node = list->head;

	while(node != NULL) {
		mappingFunction(node->data);
		node = node->next;
	}
}

void util_list_reduce(LinkedList* list, void (*reducingFunction)(Memory*, Memory*), Memory* acc)
{
	ListNode* node = list->head;

	while(node != NULL) {
		reducingFunction(acc, node->data);
		node = node->next;
	}	
}

int util_list_count(LinkedList *list)
{
	return list->count;
}

bool util_list_is_empty(LinkedList *list)
{
	return list->count == 0;
}
