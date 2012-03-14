/* 0x50 0x57 0x53 
 * Copyright 2012 Patchwork Solutions AB. All rights reserved.
 * Author: Daniel Hjort
 */

#ifndef __PWSDATA_H__
#define __PWSDATA_H__

/*#include <stdbool.h>*/

typedef struct __PWSData PWSData;

/* Allocates a PWSData and assigns the passed pointer to it. */
PWSData* initData(void *innerData);

/* Frees the PWSData and returns the pointer to the raw data for deallocation by the caller. */
void* freeData(PWSData *data);

/* Sets function pointer to comparator function. */
/*void setComparator(PWSData *data, int (*compareFunction)(void*, void*));*/

/* Checks if the PWSData has a associated comparator function. */
/*bool hasComparator(PWSData* data);*/

/* Compares two PWSData. */
/*int compare(PWSData* data1, PWSData* data2);*/

#endif
