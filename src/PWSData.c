#include <stdlib.h>

typedef struct __PWSData PWSData;

struct __PWSData {
	void *innerData;
};


PWSData* initData(void *innerData)
{
	PWSData* data = malloc(sizeof (PWSData));
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
