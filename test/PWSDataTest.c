#include <stdlib.h>

#include "PWSData.h"
#include "CuTest.h"

void TestPWSDataInitAndFree(CuTest* tc)
{
	PWSData* data = initData(0xDEADBEEF);        

	CuAssertTrue(tc, data != NULL);

	void* innerData = freeData(data);

	CuAssertTrue(tc, innerData == 0xDEADBEEF);
}
