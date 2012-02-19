/* Struct holding pointer to data and function pointer to the comparator function. */

typedef struct __PWSData PWSData;

/* Allocates a struct and assign the passed pointer to it. */
PWSData* initData(void *innerData);

/* Frees the struct and returns the pointer to the raw data for deallocation by the caller. */
void* freeData(PWSData *data);

/* Todo: set function pointers to comparator function. */
