#include "PWSLinkedList.h"
#include "CuTest.h"

void TestPWSLinkedListInit(CuTest* tc)
{
        //CuString* str = CuStringNew();
        //CuAssertTrue(tc, 0 == str->length);
        CuAssertTrue(tc, 0 != 0);
        //CuAssertStrEquals(tc, "", str->buffer);
}

CuSuite* CuGetSuite(void)
{
        CuSuite* suite = CuSuiteNew();

        SUITE_ADD_TEST(suite, TestPWSLinkedListInit);

        return suite;
}
