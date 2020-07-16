#include "HVector.h"
#include "UnitTest.h"

void TestHVector_cons()
{
    BEGIN_TEST_CASE("HVector_cons");
    HVector<int> x;
    CHECK_RESULT(x.size()!=0);
    CHECK_RESULT(x.capacity()!=0);
    HVector<Test> y(3);
    CHECK_RESULT(y.size()!=3);
    CHECK_RESULT(y.capacity()!=3);
    CHECK_RESULT(cons_called != 3);
    END_TEST_CASE();
}

void TestHVector_push_back()
{
    BEGIN_TEST_CASE("HVector_push_back");
    HVector<int> x;
    x.push_back(5);
    CHECK_RESULT(x.size()!=1);
    CHECK_RESULT(x.capacity()!=1);
    x.push_back(6);
    CHECK_RESULT(x.size()!=2);
    CHECK_RESULT(x.capacity()!=2);
    x.push_back(7);
    CHECK_RESULT(x.size()!=3);
    CHECK_RESULT(x.capacity()!=4);
    for(int i=0;i<3;i++)
        CHECK_RESULT(x[i]!= 5+i);
    HVector<Test> y;
    y.push_back(Test());
    CHECK_RESULT(cons_call!=1);
    CHECK_RESULT(copy_cons_call!=1);
    END_TEST_CASE();
}

void TestHVector()
{
    BEGIN_TEST("HVector");
    TestHVector_cons();
    TestHVector_push_back();
    //TestHVector_pop_back();
    END_TEST();
}
