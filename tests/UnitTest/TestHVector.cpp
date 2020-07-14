#include "HVector.h"
#include "UnitTest.h"

void TestHVector_cons()
{
    BEGIN_TEST_CASE("HVector_cons");
    HVector<int> x;
    CHECK_RESULT(x.size()!=0);
    CHECK_RESULT(x.capacity()!=0);
    HVector<int> y(3);
    CHECK_RESULT(x.size()!=0);
    CHECK_RESULT(x.capacity()!=0);
    END_TEST_CASE();
}

void TestHVector()
{
    BEGIN_TEST("HVector");
    TestHVector_cons();
    //TestHVector_push_back();
    //TestHVector_pop_back();
    END_TEST();
}
