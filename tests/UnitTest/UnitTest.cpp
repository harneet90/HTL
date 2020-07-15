#include "UnitTest.h"
int grand_total=0;
int total_pass=0;
int main()
{
    TestHVector();
    cout<<"Total Passed: "<<total_pass<<"/"<<grand_total<<endl;
    if(grand_total != total_pass)
        return 1;
    return 0;
}
