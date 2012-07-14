/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>

#include "MotokoLinkedList.h"
#include "CuTest.h"

void dummyDealloc(MotokoMemory* memory)
{
}

void doubleIntFunction(MotokoMemory* data)
{
	*data= *data * 2;
}

void addIntFunction(MotokoMemory* acc, MotokoMemory* data)
{
	*acc= *acc + *data;
}

int comparePointer(void* pt1, void* pt2)
{
	int result = -1;
	if (pt1 > pt2) {
		result = 1;
	} else if (pt1 == pt2) {
		result = 0;
	}
	return result;
}

void TestMotokoLinkedListCreate(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	
	CuAssertTrue(tc, isEmpty(list));
	CuAssertTrue(tc, count(list) == 0);

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListAddFirst(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();

	for (int i = 1; i < 5; i++) {	

		addFirst(list, alloc(sizeof(int), &dummyDealloc));

		CuAssertTrue(tc, !isEmpty(list));
		CuAssertTrue(tc, count(list) == i);
	}

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListAddLast(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();

	for (int i = 1; i < 5; i++) {	

		addLast(list, alloc(200, &dummyDealloc));

		CuAssertTrue(tc, !isEmpty(list));
		CuAssertTrue(tc, count(list) == i);
	}

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokolinkedListAddAtIndex(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	data = alloc(sizeof(int), &dummyDealloc);

	*data = 42;

	addAtIndex(list, data, 2);

	CuAssertTrue(tc, count(list) == 5);

	data = getByIndex(list, 2);

	CuAssertTrue(tc, 42 == *data);

	data = getByIndex(list, 3);

	CuAssertTrue(tc, 3 == *data);

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());	
}

void TestMotokoLinkedListGetFirst(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	data = getFirst(list);

	CuAssertTrue(tc, 1 == *data);

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListGetLast(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addFirst(list, data);
	}

	data = getLast(list);

	CuAssertTrue(tc, 1 == *data);

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListGetEqual(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	data = getEqual(list, data, &comparePointer);

	CuAssertTrue(tc, 4 == *data);

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListGetByIndex(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	data = getByIndex(list, 2);

	CuAssertTrue(tc, 3 == *data);

	release((MotokoMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListRemoveFirst(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 0; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	CuAssertTrue(tc, count(list) == 5);

	for (int i = 0; i < 5; i++) {	

		CuAssertTrue(tc, count(list) == 5 - i);

		data = removeFirst(list);

		CuAssertTrue(tc, *data == i);
	}

	release((MotokoMemory*)list);
	emptyAutoReleasePool();

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoLinkedListMap(CuTest* tc)
{
	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 0; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	map(list, &doubleIntFunction);

	data = getFirst(list);
	
	CuAssertTrue(tc, 0 == *data);

	data = getLast(list);
	
	CuAssertTrue(tc, 8 == *data);

	release((MotokoMemory*)list);
}

void TestMotokoLinkedListReduce(CuTest* tc)
{
	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 0; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	MotokoMemory* acc = alloc(sizeof(int), &dummyDealloc);
	*acc = 0;
	
	reduce(list, &addIntFunction, acc);

	/* 0 + 0 + 1 + 2 + 3 + 4 = 10 */
	CuAssertTrue(tc, 10 == *acc);

	release((MotokoMemory*)list);
	release(acc);
}

void MotokoLinkedListGetRest(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	MotokoLinkedList* list = linkedList();
	MotokoMemory* data;

	for (int i = 0; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	MotokoLinkedList* rest = getRest(list);

	MotokoMemory* first = getFirst(rest);
	MotokoMemory* last = getLast(rest);

	CuAssertTrue(tc, 1 == *first);
	CuAssertTrue(tc, 4 == *last);

	release((MotokoMemory*)rest);
	release((MotokoMemory*)list); 

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}
