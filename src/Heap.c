/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Heap.h"

#define MEMORY_GUARD 0xDEADBEAF

/* Private definitions. */

typedef struct __MemoryHeader MemoryHeader;

struct Heap
{
	MemoryHeader* autoReleasePool; 
	uint32_t poolCount;
};

struct __MemoryHeader
{
	uint32_t retainCount;
	void (*deallocFunction)(Memory*);
	size_t size;
	uint32_t *firstMemoryGuard;
	Memory *memory;
	uint32_t *secondMemoryGuard;
	MemoryHeader *nextInAutoReleasePool;
};

static void callDeallocAndFreeIfRetainCountIsZero(MemoryHeader *header);
static void addToPool(MemoryHeader *header);
static MemoryHeader* headerFromMemory(Memory *memory);

static struct Heap theHeap;
static uint32_t totalAllocCounter = 0;

/* Public method implementations. */

Memory* util_alloc(size_t size, void (*deallocFunction)(Memory*))
{
	MemoryHeader *header;
	Memory *ptr;

	/* Get the memory. */
	header = (MemoryHeader*)calloc(sizeof(MemoryHeader) + size + 2 * sizeof(uint32_t), 1);
	header->retainCount = 1;
	header->deallocFunction = deallocFunction;
	header->size = size;
	ptr = (Memory*)header;

	/* Get first memory guard pointer. */
	ptr += sizeof(MemoryHeader);
	header->firstMemoryGuard = (uint32_t*)ptr;
	*(header->firstMemoryGuard) = MEMORY_GUARD;

	/* Get user memory pointer. */
	ptr += sizeof(uint32_t);
	header->memory = ptr;
	
	/* Get second memory guard pointer. */
	ptr += size;	
	header->secondMemoryGuard = (uint32_t*)ptr;
	*(header->secondMemoryGuard) = MEMORY_GUARD;

	assert(util_memguards_ok(header->memory));

	totalAllocCounter++;

	return header->memory;
}

Memory* util_retain(Memory *memory)
{
	assert(util_memguards_ok(memory));

	if(memory != NULL) {

		MemoryHeader *header = headerFromMemory(memory);

		header->retainCount++;
	}

	return memory;
}

void util_release(Memory *memory)
{
	assert(util_memguards_ok(memory));

	if(memory != NULL) {

		MemoryHeader *header = headerFromMemory(memory);

		header->retainCount--;

		callDeallocAndFreeIfRetainCountIsZero(header);
	}
}

Memory* util_autorelease(Memory *memory)
{
	assert(util_memguards_ok(memory));

	if(memory != NULL) {

		MemoryHeader *header = headerFromMemory(memory);

		header->retainCount--;
		if(header->retainCount == 0)
			addToPool(header);
	}

	return memory;
}

uint32_t util_retain_count(Memory *memory)
{
	assert(util_memguards_ok(memory));

	uint32_t result = 0;

	if(memory != NULL) {

		MemoryHeader *header = headerFromMemory(memory);
		result = header->retainCount;
	}

	return result;
}

bool util_memguards_ok(Memory *memory)
{
	bool result = true;

	if(memory != NULL) {

		MemoryHeader *header = headerFromMemory(memory);
		result = *(header->firstMemoryGuard) == MEMORY_GUARD && *(header->secondMemoryGuard) == MEMORY_GUARD;
	}

	return result;
}

void util_empty_autoreleasepool()
{
	MemoryHeader* header = theHeap.autoReleasePool;
	theHeap.autoReleasePool = NULL;

	while (header != NULL) {

		MemoryHeader* next = header->nextInAutoReleasePool;
		callDeallocAndFreeIfRetainCountIsZero(header);
		header = next;
		theHeap.poolCount--;
	}

	assert((theHeap.poolCount == 0));
}

uint32_t util_autoreleasepool_count()
{
	return theHeap.poolCount;
}

/* Private methods implementations. */

static void callDeallocAndFreeIfRetainCountIsZero(MemoryHeader *header)
{
	if (header->retainCount == 0) {
		header->deallocFunction(header->memory);
		free(header);
		totalAllocCounter--;
	}
}

static void addToPool(MemoryHeader *header)
{
	header->nextInAutoReleasePool = theHeap.autoReleasePool;
	theHeap.autoReleasePool = header;
	theHeap.poolCount++;
}

static MemoryHeader* headerFromMemory(Memory *memory)
{
	return (MemoryHeader*)(memory - (sizeof(MemoryHeader) + sizeof(uint32_t)));
}

uint32_t util_total_alloc_count()
{
	return totalAllocCounter;
}
