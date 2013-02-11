/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <limits.h>

#include "Heap.h"
#include "CuTest.h"

static int deallocCount;

void test_dealloc(Memory* memory)
{
	deallocCount++;
}

void TestHeapAllocAndRelease(CuTest* tc)
{

	int *memory;
	deallocCount = 0;
	uint32_t initialAllocCount = util_total_alloc_count();

	for (int i = 0; i < 5; i++) {

		memory = (int*)util_alloc(sizeof(int), &test_dealloc);

		*memory = INT_MAX;

		CuAssertTrue(tc, memory != NULL);
		CuAssertTrue(tc, util_retain_count((Memory*)memory) == 1);
		CuAssertTrue(tc, util_memguards_ok((Memory*)memory));

		util_release((Memory*)memory);
	}

	CuAssertTrue(tc, deallocCount == 5);
	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}


void TestHeapAllocRetainAndRelease(CuTest* tc)
{

	uint32_t initialAllocCount = util_total_alloc_count();
	int *memory = (int*)util_alloc(sizeof(int), &test_dealloc);
	deallocCount = 0;

	CuAssertTrue(tc, memory != NULL);

	*memory = INT_MAX;

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, *memory == INT_MAX);
		CuAssertTrue(tc, util_retain_count((Memory*)memory) == 1);
		CuAssertTrue(tc, util_memguards_ok((Memory*)memory));

		util_retain((Memory*)memory);

		CuAssertTrue(tc, *memory == INT_MAX);
		CuAssertTrue(tc, util_retain_count((Memory*)memory) == 2);
		CuAssertTrue(tc, util_memguards_ok((Memory*)memory));

		util_release((Memory*)memory);
	}

	util_release((Memory*)memory);

	CuAssertTrue(tc, deallocCount == 1);
	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}

void TestHeapAllocAndAutoRelease(CuTest* tc)
{
	int *memories[5];
	deallocCount = 0;
	uint32_t initialAllocCount = util_total_alloc_count();

	for (int i = 0; i < 5; i++) {

		memories[i] = (int*)util_alloc(sizeof(int), &test_dealloc);
		*memories[i]  = i;

		CuAssertTrue(tc, util_retain_count((Memory*)memories[i]) == 1);
		CuAssertTrue(tc, util_memguards_ok((Memory*)memories[i]));
	}

	CuAssertTrue(tc, util_autoreleasepool_count() == 0);

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, util_autoreleasepool_count() == i);

		util_autorelease((Memory*)memories[i]);
	}

	CuAssertTrue(tc, deallocCount == 0);

	util_empty_autoreleasepool();

	CuAssertTrue(tc, util_autoreleasepool_count() == 0);
	CuAssertTrue(tc, deallocCount == 5);

	CuAssertTrue(tc, initialAllocCount == util_total_alloc_count());
}
