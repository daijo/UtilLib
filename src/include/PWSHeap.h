/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __PWSHEAP_H__
#define __PWSHEAP_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef char PWSMemory;

/* Allocates memory of size and returns a memory pointer with retain count 1. 
 * Takes a function that should call release on all allocated members. */
PWSMemory* alloc(size_t size, void (*deallocFunction)(PWSMemory*));

/* Retain memory that gets passed to you. Retain count increased by 1. */
PWSMemory* retain(PWSMemory *memory);

/* Release memory you don't reference. Retain count decreased by 1.
 * If the retain count reaches 0 the memory is freed after its deallocFunction is called. */
void release(PWSMemory *memory);

/* Decreases the the memory's retain count by 1. If it reaches 0 it is put in the autorelease pool.
 * If the retain count is 0 when emptyAutoReleasePool() is called it is freed after its deallocFunction is called. */
PWSMemory* autorelease(PWSMemory *memory);

/* Returns the memorys retain count. */
uint32_t retainCount(PWSMemory *memory);

/* Returns true if the memory guards haven't been overrun. */
bool memoryGuardsUntouched(PWSMemory *memory);

/* Empties the pool. All memories with retain count 0 is freed after their deallocFunction is called. Call at end of each runloop. */
void emptyAutoReleasePool();

uint32_t autoReleasePoolCount();

uint32_t totalAllocCount();

#endif
