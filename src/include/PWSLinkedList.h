typedef struct __PWSLinkedList PWSLinkedList;

PWSLinkedList* initLinkedList();
void releaseLinkedList(PWSLinkedList list);
void addLast(void* data, PWSLinkedList* list);
void addFirst(void* data, PWSLinkedList* list);
void* getFirst(PWSLinkedList* list);
void* getLast(PWSLinkedList* list);
void* remove(PWSLinkedList* list, void* data); 
