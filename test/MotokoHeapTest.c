/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <limits.h>

#include "MotokoHeap.h"
#include "CuTest.h"

static int deallocCount;

void test_dealloc(MotokoMemory* memory)
{
	deallocCount++;
}

void TestMotokoHeapAllocAndRelease(CuTest* tc)
{

	int *memory;
	deallocCount = 0;
	uint32_t initialAllocCount = totalAllocCount();

	for (int i = 0; i < 5; i++) {

		memory = (int*)alloc(sizeof(int), &test_dealloc);

		*memory = INT_MAX;

		CuAssertTrue(tc, memory != NULL);
		CuAssertTrue(tc, retainCount((MotokoMemory*)memory) == 1);
		CuAssertTrue(tc, memoryGuardsUntouched((MotokoMemory*)memory));

		release((MotokoMemory*)memory);
	}

	CuAssertTrue(tc, deallocCount == 5);
	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}


void TestMotokoHeapAllocRetainAndRelease(CuTest* tc)
{

	uint32_t initialAllocCount = totalAllocCount();
	int *memory = (int*)alloc(sizeof(int), &test_dealloc);
	deallocCount = 0;

	CuAssertTrue(tc, memory != NULL);

	*memory = INT_MAX;

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, *memory == INT_MAX);
		CuAssertTrue(tc, retainCount((MotokoMemory*)memory) == 1);
		CuAssertTrue(tc, memoryGuardsUntouched((MotokoMemory*)memory));

		retain((MotokoMemory*)memory);

		CuAssertTrue(tc, *memory == INT_MAX);
		CuAssertTrue(tc, retainCount((MotokoMemory*)memory) == 2);
		CuAssertTrue(tc, memoryGuardsUntouched((MotokoMemory*)memory));

		release((MotokoMemory*)memory);
	}

	release((MotokoMemory*)memory);

	CuAssertTrue(tc, deallocCount == 1);
	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}

void TestMotokoHeapAllocAndAutoRelease(CuTest* tc)
{
	int *memories[5];
	deallocCount = 0;
	uint32_t initialAllocCount = totalAllocCount();

	for (int i = 0; i < 5; i++) {

		memories[i] = (int*)alloc(sizeof(int), &test_dealloc);
		*memories[i]  = i;

		CuAssertTrue(tc, retainCount((MotokoMemory*)memories[i]) == 1);
		CuAssertTrue(tc, memoryGuardsUntouched((MotokoMemory*)memories[i]));
	}

	CuAssertTrue(tc, autoReleasePoolCount() == 0);

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, autoReleasePoolCount() == i);

		autorelease((MotokoMemory*)memories[i]);
	}

	CuAssertTrue(tc, deallocCount == 0);

	emptyAutoReleasePool();

	CuAssertTrue(tc, autoReleasePoolCount() == 0);
	CuAssertTrue(tc, deallocCount == 5);

	CuAssertTrue(tc, initialAllocCount == totalAllocCount());
}
