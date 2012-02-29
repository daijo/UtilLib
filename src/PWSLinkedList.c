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
	memset(list, 0, sizeof(PWSLinkedList));
        return list;
}

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

int count(PWSLinkedList *list)
{
}

bool isEmpty(PWSLinkedList *list)
{
}*/
