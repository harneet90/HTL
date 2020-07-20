#include "HVector.h"
#include "UnitTest.h"

void TestHVector_cons()
{
    BEGIN_TEST_CASE("HVector_cons");
    /* Default Constructor */
    HVector<int> x;
    CHECK_RESULT(x.size() != 0);
    CHECK_RESULT(x.capacity() != 0);
    /* Size Construcotr */
    HVector<Test> y(3);
    CHECK_RESULT(y.size() != 3);
    CHECK_RESULT(y.capacity() != 3);
    CHECK_RESULT(cons_call != 3);
    /* Fill Constructor */
    HVector<int> z(4,4);
    CHECK_RESULT(z.size() != 4);
    for(int i=0;i<4;i++)
        CHECK_RESULT(z[i] != 4);
    /* Initializer List Construcotr */
    HVector<int> w{1,2,3,4,5};
    CHECK_RESULT(w.size() != 5);
    CHECK_RESULT(w.capacity() != 5);
    for(int i=1;i<=5;i++)
        CHECK_RESULT(w[i-1] != i);
    END_TEST_CASE();
}

void TestHVector_push_pop()
{
    BEGIN_TEST_CASE("HVector_push_pop");
    HVector<int> x;
    x.push_back(5);
    CHECK_RESULT(x.size() != 1);
    CHECK_RESULT(x.capacity() != 1);
    x.push_back(6);
    CHECK_RESULT(x.size() != 2);
    CHECK_RESULT(x.capacity() != 2);
    x.push_back(7);
    CHECK_RESULT(x.size() != 3);
    CHECK_RESULT(x.capacity() != 4);
    for(int i=0;i<3;i++)
        CHECK_RESULT(x[i]!= 5+i);
    HVector<Test> y;
    Test t;
    y.push_back(t);
    y.push_back(Test());
    CHECK_RESULT(cons_call != 2);
    cout<<"\nCalls"<<copy_cons_call<<" "<<move_cons_call<<" "<<des_call<<"\n";
    CHECK_RESULT(copy_cons_call != 2);
    CHECK_RESULT(move_cons_call != 0);
    y.pop_back();
    CHECK_RESULT(des_call != 2);
    CHECK_RESULT(y.size() != 1);
    CHECK_RESULT(y.capacity() != 2);
    END_TEST_CASE();
}

void TestHVector_begin_end()
{
    BEGIN_TEST_CASE("HVector_begin_end");
    HVector<int> x;
    x.push_back(5);
    CHECK_RESULT(*(x.begin()) != 5);
    CHECK_RESULT(x.begin() != x.end());
    x.push_back(6);
    CHECK_RESULT(*(x.end()) != 6);
    CHECK_RESULT(x.begin() + 1 != x.end());
    int i=0;
    for(auto itr = x.begin();itr != x.end();itr++,i++)
        CHECK_RESULT(*itr != 5 + i);
    END_TEST_CASE();
}

void TestHVector()
{
    BEGIN_TEST("HVector");
    TestHVector_cons();
    TestHVector_push_pop();
    TestHVector_begin_end();
    END_TEST();
}
