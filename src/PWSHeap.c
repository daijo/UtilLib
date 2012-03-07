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
	uint32_t freePoolIndex;
	uint32_t autoReleasePoolSize;
};

struct __PWSMemoryHeader
{
	uint32_t retainCount;
	size_t size;
	uint32_t *firstMemoryGuard;
	PWSMemory *memory;
	uint32_t *secondMemoryGuard;
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
	header = (PWSMemoryHeader*)calloc(sizeof(PWSMemoryHeader) + size + 2 * sizeof(uint32_t), 1);
	header->retainCount = 1;
	ptr = (PWSMemory*)header;

	/* Get first memory guard pointer. */
	ptr += sizeof(PWSMemoryHeader);
	header->firstMemoryGuard = (uint32_t*)ptr;
	*(header->firstMemoryGuard) = MEMORY_GUARD;

	/* Get user memory pointer. */
	ptr += sizeof(uint32_t);
	header->memory = ptr;
	
	/* Get second memory guard pointer. */
	ptr += size;	
	header->secondMemoryGuard = (uint32_t*)ptr;
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

uint32_t retainCount(PWSMemory *memory)
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

bool setupAutoReleasePool(uint32_t autoReleasePoolSize)
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

uint32_t autoReleasePoolCount()
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
	return (PWSMemoryHeader*)(memory - (sizeof(PWSMemoryHeader) + sizeof(uint32_t)));
}
