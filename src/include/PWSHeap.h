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

/* Functions called by the system! */

/* Prepare the PWSHeap before use. */
bool setupHeap(int autoReleasePoolSize);

/* Prepare the PWSHeap before shutdown. */
void teardownHeap();

/* Call at end of each runloop. */
void emptyAutoReleasePool();

/* Heap query methods. */
int autoReleasePoolCount();

bool spaceLeftInPool();

#endif
