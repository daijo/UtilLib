/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __MotokoHEAP_H__
#define __MotokoHEAP_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef char MotokoMemory;

/* Allocates memory of size and returns a memory pointer with retain count 1. 
 * Takes a function that should call release on all allocated members. */
MotokoMemory* alloc(size_t size, void (*deallocFunction)(MotokoMemory*));

/* Retain memory that gets passed to you. Retain count increased by 1. */
MotokoMemory* retain(MotokoMemory *memory);

/* Release memory you don't reference. Retain count decreased by 1.
 * If the retain count reaches 0 the memory is freed after its deallocFunction is called. */
void release(MotokoMemory *memory);

/* Decreases the the memory's retain count by 1. If it reaches 0 it is put in the autorelease pool.
 * If the retain count is 0 when emptyAutoReleasePool() is called it is freed after its deallocFunction is called. */
MotokoMemory* autorelease(MotokoMemory *memory);

/* Returns the memorys retain count. */
uint32_t retainCount(MotokoMemory *memory);

/* Returns true if the memory guards haven't been overrun. */
bool memoryGuardsUntouched(MotokoMemory *memory);

/* Empties the pool. All memories with retain count 0 is freed after their deallocFunction is called. Call at end of each runloop. */
void emptyAutoReleasePool();

uint32_t autoReleasePoolCount();

uint32_t totalAllocCount();

#endif
