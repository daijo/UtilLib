/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>

#include "PWSLinkedList.h"
#include "CuTest.h"

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



}

void TestPWSLinkedListAddLast(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}

void TestPWSLinkedListGetFirst(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}

void TestPWSLinkedListGetLast(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}
