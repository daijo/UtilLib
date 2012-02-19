#include "PWSLinkedList.h"

typedef struct __Node Node;
struct __Node {
void *data;
Node *previous;
Node *next;
};

struct __PWSLinkedList {
Node *root;
};

void addLast(void* data, PWSLinkedList* list)
{

}

void addFirst(void* data, PWSLinkedList* list)
{

}


