#include "PWSHeap.h"
#include "CuTest.h"

#define AUTO_RELEASE_POOL_SIZE 30

void TestPWSHeapSetupAndTeardownAutoReleasePool(CuTest* tc)
{

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, setupAutoReleasePool(AUTO_RELEASE_POOL_SIZE));

		CuAssertTrue(tc, spaceLeftInPool());

		CuAssertTrue(tc, autoReleasePoolCount() == 0);

		teardownAutoReleasePool();	

		CuAssertTrue(tc, !spaceLeftInPool());
	}
}

void TestPWSHeapAllocAndRelease(CuTest* tc)
{

	PWSMemory* memory = alloc(sizeof(int));

	CuAssertTrue(tc, memory != NULL);
	CuAssertTrue(tc, retainCount(memory) == 1);
	CuAssertTrue(tc, memoryGuardsUntouched(memory));
}


void TestPWSHeapAllocRetainAndRelease(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}

void TestPWSHeapAllocAndAutoRelease(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}
