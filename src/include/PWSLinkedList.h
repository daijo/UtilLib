#ifndef __PWSLINKEDLIST_H__
#define __PWSLINKEDLIST_H__

#include <stdbool.h>

#include "PWSData.h"

typedef struct __PWSLinkedList PWSLinkedList;

PWSLinkedList* initLinkedList();
void freeLinkedList(PWSLinkedList *list); /* free remaining data? */

int addLast(PWSLinkedList *list, PWSData* data);
void addFirst(PWSLinkedList *list, PWSData* data);
int addAtIndex(PWSLinkedList *list, PWSData* data, int index);

PWSData* getFirst(PWSLinkedList* list);
PWSLinkedList* getRest(PWSLinkedList* list);
PWSData* getLast(PWSLinkedList* list);
PWSData* getByReference(PWSLinkedList* list, PWSData* data);
PWSData* getByValue(PWSLinkedList* list, PWSData* data);
PWSData* getByIndex(PWSLinkedList* list, int index);

PWSData* removeFirst(PWSLinkedList* list);
PWSData* removeLast(PWSLinkedList* list);
PWSData* removeByReference(PWSLinkedList* list, PWSData* data);
PWSData* removeByValue(PWSLinkedList* list, PWSData* data);
PWSData* removeByIndex(PWSLinkedList* list, int index);

int count(PWSLinkedList *list);
bool isEmpty(PWSLinkedList *list);

#endif
