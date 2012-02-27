#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


typedef struct __PWSData PWSData;

struct __PWSData {
	void *innerData;
	int (*compareFunction)(void*, void*); 
};

PWSData* initData(void *innerData)
{
	PWSData* data = (PWSData*)malloc(sizeof (PWSData));
	memset(data, 0, (sizeof (PWSData)));
        data->innerData = innerData;
	return data;
}

void* freeData(PWSData *data)
{
	void* innerData = data->innerData;
	free(data);
	return innerData;
}

void setComparator(PWSData *data, int (*compareFunction)(void*, void*))
{
	data->compareFunction = compareFunction;
}

bool hasComparator(PWSData* data)
{
	bool result = false;
	if (data->compareFunction != NULL) {
		result = true;
	}
	return result;
}

int compare(PWSData* data1, PWSData* data2)
{

	if(data1->compareFunction == NULL
		|| data1 == NULL
		|| data2 == NULL) {
		assert(false);
	}
	return data1->compareFunction(data1->innerData, data2->innerData);
}

