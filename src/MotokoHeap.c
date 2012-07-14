/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "MotokoHeap.h"

#define MEMORY_GUARD 0xDEADBEAF

/* Private definitions. */

typedef struct __MotokoMemoryHeader MotokoMemoryHeader;

struct MotokoHeap
{
	MotokoMemoryHeader* autoReleasePool; 
	uint32_t poolCount;
};

struct __MotokoMemoryHeader
{
	uint32_t retainCount;
	void (*deallocFunction)(MotokoMemory*);
	size_t size;
	uint32_t *firstMemoryGuard;
	MotokoMemory *memory;
	uint32_t *secondMemoryGuard;
	MotokoMemoryHeader *nextInAutoReleasePool;
};

static void callDeallocAndFreeIfRetainCountIsZero(MotokoMemoryHeader *header);
static void addToPool(MotokoMemoryHeader *header);
static MotokoMemoryHeader* headerFromMemory(MotokoMemory *memory);

static struct MotokoHeap theHeap;
static uint32_t totalAllocCounter = 0;

/* Public method implementations. */

MotokoMemory* alloc(size_t size, void (*deallocFunction)(MotokoMemory*))
{
	MotokoMemoryHeader *header;
	MotokoMemory *ptr;

	/* Get the memory. */
	header = (MotokoMemoryHeader*)calloc(sizeof(MotokoMemoryHeader) + size + 2 * sizeof(uint32_t), 1);
	header->retainCount = 1;
	header->deallocFunction = deallocFunction;
	header->size = size;
	ptr = (MotokoMemory*)header;

	/* Get first memory guard pointer. */
	ptr += sizeof(MotokoMemoryHeader);
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

	totalAllocCounter++;

	return header->memory;
}

MotokoMemory* retain(MotokoMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	if(memory != NULL) {

		MotokoMemoryHeader *header = headerFromMemory(memory);

		header->retainCount++;
	}

	return memory;
}

void release(MotokoMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	if(memory != NULL) {

		MotokoMemoryHeader *header = headerFromMemory(memory);

		header->retainCount--;

		callDeallocAndFreeIfRetainCountIsZero(header);
	}
}

MotokoMemory* autorelease(MotokoMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	if(memory != NULL) {

		MotokoMemoryHeader *header = headerFromMemory(memory);

		header->retainCount--;
		if(header->retainCount == 0)
			addToPool(header);
	}

	return memory;
}

uint32_t retainCount(MotokoMemory *memory)
{
	assert(memoryGuardsUntouched(memory));

	uint32_t result = 0;

	if(memory != NULL) {

		MotokoMemoryHeader *header = headerFromMemory(memory);
		result = header->retainCount;
	}

	return result;
}

bool memoryGuardsUntouched(MotokoMemory *memory)
{
	bool result = true;

	if(memory != NULL) {

		MotokoMemoryHeader *header = headerFromMemory(memory);
		result = *(header->firstMemoryGuard) == MEMORY_GUARD && *(header->secondMemoryGuard) == MEMORY_GUARD;
	}

	return result;
}

void emptyAutoReleasePool()
{
	MotokoMemoryHeader* header = theHeap.autoReleasePool;
	theHeap.autoReleasePool = NULL;

	while (header != NULL) {

		MotokoMemoryHeader* next = header->nextInAutoReleasePool;
		callDeallocAndFreeIfRetainCountIsZero(header);
		header = next;
		theHeap.poolCount--;
	}

	assert((theHeap.poolCount == 0));
}

uint32_t autoReleasePoolCount()
{
	return theHeap.poolCount;
}

/* Private methods implementations. */

static void callDeallocAndFreeIfRetainCountIsZero(MotokoMemoryHeader *header)
{
	if (header->retainCount == 0) {
		header->deallocFunction(header->memory);
		free(header);
		totalAllocCounter--;
	}
}

static void addToPool(MotokoMemoryHeader *header)
{
	header->nextInAutoReleasePool = theHeap.autoReleasePool;
	theHeap.autoReleasePool = header;
	theHeap.poolCount++;
}

static MotokoMemoryHeader* headerFromMemory(MotokoMemory *memory)
{
	return (MotokoMemoryHeader*)(memory - (sizeof(MotokoMemoryHeader) + sizeof(uint32_t)));
}

uint32_t totalAllocCount()
{
	return totalAllocCounter;
}
