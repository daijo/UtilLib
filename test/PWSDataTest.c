/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>

#include "PWSData.h"
#include "CuTest.h"

static int testData = 0xDEADBEEF;

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

void TestPWSDataInitAndFree(CuTest* tc)
{

	PWSData* data = initData(&testData);

	CuAssertTrue(tc, data != NULL);

	void* innerData = freeData(data);

	CuAssertTrue(tc, innerData == &testData);
}

void TestPWSDataSetComparatorHasComparator(CuTest* tc)
{

/*	PWSData* data = initData(&testData);

	CuAssertTrue(tc, !hasComparator(data));

	setComparator(data, &comparePointer);

	CuAssertTrue(tc, hasComparator(data));

	freeData(data);*/
}

void TestPWSDataCompare(CuTest* tc)
{
/*	PWSData* data1 = initData((void*)1);
	PWSData* data2 = initData((void*)1);

	setComparator(data1, &comparePointer);

	CuAssertTrue(tc, compare(data1, data2) == 0);

	freeData(data2);
	data2 = initData((void*)2);

	CuAssertTrue(tc, compare(data1, data2) == -1);

	freeData(data1);
        freeData(data2);*/
}
