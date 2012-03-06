#include "PWSHeap.h"
#include "CuTest.h"

#define AUTO_RELEASE_POOL_SIZE 30

void TestPWSHeapSetupAndTeardown(CuTest* tc)
{

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, setupHeap(AUTO_RELEASE_POOL_SIZE));

		CuAssertTrue(tc, spaceLeftInPool());

		CuAssertTrue(tc, autoReleasePoolCount() == 0);

		teardownHeap();	

		CuAssertTrue(tc, !spaceLeftInPool());
	}
}

void TestPWSHeapAllocAndRelease(CuTest* tc)
{
	setupHeap(AUTO_RELEASE_POOL_SIZE);

	PWSMemory* memory = alloc(sizeof(int));

	CuAssertTrue(tc, memory != NULL);
	CuAssertTrue(tc, retainCount(memory) == 1);
	CuAssertTrue(tc, memoryGuardsUntouched(memory));
	
	teardownHeap();	
}


void TestPWSHeapAllocRetainAndRelease(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}

void TestPWSHeapAllocAndAutoRelease(CuTest* tc)
{
        CuFail(tc, "Incomplete test case.");
}
