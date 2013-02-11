/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef char Memory;

/* Allocates memory of size and returns a memory pointer with retain count 1. 
 * Takes a function that should call release on all allocated members. */
Memory* util_alloc(size_t size, void (*deallocFunction)(Memory*));

/* Retain memory that gets passed to you. Retain count increased by 1. */
Memory* util_retain(Memory *memory);

/* Release memory you don't reference. Retain count decreased by 1.
 * If the retain count reaches 0 the memory is freed after its deallocFunction is called. */
void util_release(Memory *memory);

/* Decreases the the memory's retain count by 1. If it reaches 0 it is put in the autorelease pool.
 * If the retain count is 0 when emptyAutoReleasePool() is called it is freed after its deallocFunction is called. */
Memory* util_autorelease(Memory *memory);

/* Returns the memorys retain count. */
uint32_t util_retain_count(Memory *memory);

/* Returns true if the memory guards haven't been overrun. */
bool util_memguards_ok(Memory *memory);

/* Empties the pool. All memories with retain count 0 is freed after their deallocFunction is called. Call at end of each runloop. */
void util_empty_autoreleasepool();

uint32_t util_autoreleasepool_count();

uint32_t util_total_alloc_count();

#endif
