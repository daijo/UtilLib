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
