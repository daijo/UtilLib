#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "PWSHeap.h"

#define MEMORY_GUARD 0xDEADBEAF

/* Private definitions. */

typedef struct __PWSMemoryHeader PWSMemoryHeader;

struct PWSHeap
{
	PWSMemoryHeader* autoReleasePool;
	int freePoolIndex;
	int autoReleasePoolSize;
};

struct __PWSMemoryHeader
{
	unsigned int retainCount;
	size_t size;
	int *firstMemoryGuard;
	PWSMemory *memory;
	int *secondMemoryGuard;
};

//static void addToPool(PWSMemory *memory);
static PWSMemoryHeader* headerFromMemory(PWSMemory *memory);

static struct PWSHeap theHeap;

/* Public method implementations. */

PWSMemory* alloc(size_t size)
{
	PWSMemoryHeader *header;
	PWSMemory *ptr;

	/* Get the memory. */
	header = (PWSMemoryHeader*)calloc(sizeof(PWSMemoryHeader) + size + 2 * sizeof(int), 1);
	header->retainCount = 1;
	ptr = (PWSMemory*)header;

	/* Get first memory guard pointer. */
	ptr += sizeof(PWSMemoryHeader);
	header->firstMemoryGuard = (int*)ptr;
	*(header->firstMemoryGuard) = MEMORY_GUARD;

	/* Get user memory pointer. */
	ptr += sizeof(int);
	header->memory = ptr;
	
	/* Get second memory guard pointer. */
	ptr += size;	
	header->secondMemoryGuard = (int*)ptr;
	*(header->secondMemoryGuard) = MEMORY_GUARD;

	assert(memoryGuardsUntouched(header->memory));

	return header->memory;
}

void retain(PWSMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	PWSMemoryHeader *header = headerFromMemory(memory);

	header->retainCount++;
}

void release(PWSMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	PWSMemoryHeader *header = headerFromMemory(memory);

	header->retainCount--;

	if (header->retainCount == 0) {
		free(header);
	}
}

void autorelease(PWSMemory *memory)
{
	assert(memoryGuardsUntouched(memory));


}

int retainCount(PWSMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	PWSMemoryHeader *header = headerFromMemory(memory);

	return header->retainCount;
}

bool memoryGuardsUntouched(PWSMemory *memory)
{
	PWSMemoryHeader *header = headerFromMemory(memory);

	return *(header->firstMemoryGuard) == MEMORY_GUARD && *(header->secondMemoryGuard) == MEMORY_GUARD;
}

bool setupAutoReleasePool(int autoReleasePoolSize)
{
	theHeap.autoReleasePool = (PWSMemoryHeader*)calloc(sizeof(PWSMemoryHeader*), autoReleasePoolSize);
	theHeap.freePoolIndex = 0;
	theHeap.autoReleasePoolSize = autoReleasePoolSize;
	return theHeap.autoReleasePool != NULL;
}

void teardownAutoReleasePool()
{
	emptyAutoReleasePool();
	free(theHeap.autoReleasePool);
	theHeap.autoReleasePool = 0;
	theHeap.autoReleasePoolSize = 0;
}

void emptyAutoReleasePool()
{

}

int autoReleasePoolCount()
{
	return theHeap.freePoolIndex;
}

bool spaceLeftInPool()
{
	return theHeap.freePoolIndex < theHeap.autoReleasePoolSize;
}

/* Private methods implementations. */

/*static void addToPool(PWSMemory *memory)
{

}*/

static PWSMemoryHeader* headerFromMemory(PWSMemory *memory)
{
	return (PWSMemoryHeader*)(memory - (sizeof(PWSMemoryHeader) + sizeof(int)));
}
