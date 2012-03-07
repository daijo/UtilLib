#ifndef __PWSHEAP_H__
#define __PWSHEAP_H__

#include <stddef.h>
#include <stdbool.h>

typedef char PWSMemory;

/* Get retained memory pointer. */
PWSMemory* alloc(size_t size);

/* Retain memory that gets passed to you. */
void retain(PWSMemory *memory);

/* Release memory you don't reference. */
void release(PWSMemory *memory);

/* Call in library functions before returning pointers allocated in the library. */
void autorelease(PWSMemory *memory);

/* Returns the memorys retain count. */
int retainCount(PWSMemory *memory);

/* Returns true if the memory guards haven't been overrun. */
bool memoryGuardsUntouched(PWSMemory *memory);

bool setupAutoReleasePool(int autoReleasePoolSize);

/* Empties and deallocates the pool. */
void teardownAutoReleasePool();

/* Call at end of each runloop. */
void emptyAutoReleasePool();

int autoReleasePoolCount();

bool spaceLeftInPool();

#endif
