#include <limits.h>

#include "PWSHeap.h"
#include "CuTest.h"

#define AUTO_RELEASE_POOL_SIZE 5 

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

	int *memory;

	for (int i = 0; i < 5; i++) {

		memory = (int*)alloc(sizeof(int));

		*memory = INT_MAX;

		CuAssertTrue(tc, memory != NULL);
		CuAssertTrue(tc, retainCount((PWSMemory*)memory) == 1);
		CuAssertTrue(tc, memoryGuardsUntouched((PWSMemory*)memory));

		release((PWSMemory*)memory);
	}
}


void TestPWSHeapAllocRetainAndRelease(CuTest* tc)
{

	int *memory = (int*)alloc(sizeof(int));

	CuAssertTrue(tc, memory != NULL);

	*memory = INT_MAX;

	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, *memory == INT_MAX);
		CuAssertTrue(tc, retainCount((PWSMemory*)memory) == 1);
		CuAssertTrue(tc, memoryGuardsUntouched((PWSMemory*)memory));

		retain((PWSMemory*)memory);

		CuAssertTrue(tc, *memory == INT_MAX);
		CuAssertTrue(tc, retainCount((PWSMemory*)memory) == 2);
		CuAssertTrue(tc, memoryGuardsUntouched((PWSMemory*)memory));

		release((PWSMemory*)memory);
	}

	release((PWSMemory*)memory);
}

void TestPWSHeapAllocAndAutoRelease(CuTest* tc)
{
	int *memories[5];

	for (int i = 0; i < 5; i++) {

		memories[i] = (int*)alloc(sizeof(int));
		*memories[i]  = i;

		CuAssertTrue(tc, retainCount((PWSMemory*)memories[i]) == 1);
		CuAssertTrue(tc, memoryGuardsUntouched((PWSMemory*)memories[i]));
	}

	CuAssertTrue(tc, setupAutoReleasePool(AUTO_RELEASE_POOL_SIZE));
	CuAssertTrue(tc, spaceLeftInPool());
	CuAssertTrue(tc, autoReleasePoolCount() == 0);


	for (int i = 0; i < 5; i++) {

		CuAssertTrue(tc, spaceLeftInPool() == (i < 5));
		CuAssertTrue(tc, autoReleasePoolCount() == (5 - i));

		autorelease((PWSMemory*)memories[i]);
	}

	CuAssertTrue(tc, !spaceLeftInPool());

	emptyAutoReleasePool();

	CuAssertTrue(tc, spaceLeftInPool());
	CuAssertTrue(tc, autoReleasePoolCount() == 0);

	teardownAutoReleasePool();
}
