/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>

#include "PWSLinkedList.h"
#include "CuTest.h"

void dummyDealloc(PWSMemory* memory)
{
}

void doubleIntFunction(PWSMemory* data)
{
	*data= *data * 2;
}

void addIntFunction(PWSMemory* acc, PWSMemory* data)
{
	*acc= *acc + *data;
}

void TestPWSLinkedListCreate(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	PWSLinkedList* list = linkedList();
	
	CuAssertTrue(tc, isEmpty(list));
	CuAssertTrue(tc, count(list) == 0);

	release((PWSMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestPWSLinkedListAddFirst(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	PWSLinkedList* list = linkedList();

	for (int i = 1; i < 5; i++) {	

		addFirst(list, alloc(sizeof(int), &dummyDealloc));

		CuAssertTrue(tc, !isEmpty(list));
		CuAssertTrue(tc, count(list) == i);
	}

	release((PWSMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestPWSLinkedListAddLast(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	PWSLinkedList* list = linkedList();

	for (int i = 1; i < 5; i++) {	

		addLast(list, alloc(200, &dummyDealloc));

		CuAssertTrue(tc, !isEmpty(list));
		CuAssertTrue(tc, count(list) == i);
	}

	release((PWSMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestPWSLinkedListGetFirst(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	PWSLinkedList* list = linkedList();
	PWSMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	data = getFirst(list);

	CuAssertTrue(tc, 1 == *data);

	release((PWSMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestPWSLinkedListGetLast(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	PWSLinkedList* list = linkedList();
	PWSMemory* data;

	for (int i = 1; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addFirst(list, data);
	}

	data = getLast(list);

	CuAssertTrue(tc, 1 == *data);

	release((PWSMemory*)list);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestPWSLinkedListMap(CuTest* tc)
{
	PWSLinkedList* list = linkedList();
	PWSMemory* data;

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

	release((PWSMemory*)list);
}

void TestPWSLinkedListReduce(CuTest* tc)
{
	PWSLinkedList* list = linkedList();
	PWSMemory* data;

	for (int i = 0; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	PWSMemory* acc = alloc(sizeof(int), &dummyDealloc);
	*acc = 0;
	
	reduce(list, &addIntFunction, acc);

	/* 0 + 0 + 1 + 2 + 3 + 4 = 10 */
	CuAssertTrue(tc, 10 == *acc);

	release((PWSMemory*)list);
	release(acc);
}

void PWSLinkedListGetRest(CuTest* tc)
{
	uint32_t initialAllocCount = totalAllocCount();

	PWSLinkedList* list = linkedList();
	PWSMemory* data;

	for (int i = 0; i < 5; i++) {	

		data = alloc(sizeof(int), &dummyDealloc);

		*data = i;

		addLast(list, data);
	}

	PWSLinkedList* rest = getRest(list);

	PWSMemory* first = getFirst(rest);
	PWSMemory* last = getLast(rest);

	CuAssertTrue(tc, 1 == *first);
	CuAssertTrue(tc, 4 == *last);

	release((PWSMemory*)rest);
	release((PWSMemory*)list); 

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}
