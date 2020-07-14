#pragma once

static int pass = 0;
static int total = 0;
int grand_total;
int total_pass;
#define CHECK_RESULT(cond) { \
                            total++; \
                            if(!(cond)) pass++; \
                            else \
                            { \
                                cout<<"Test "<<__function__<<" failed on line "<<__LINE__<<"\n"; \
                            } \
                           }
                           
static int cons_call = 0;  
static int des_call = 0;
static int copy_cons_call = 0;

static class Test
{
    public:
    Test(){cons_call++;}
    ~Test(){des_call++;}
    Test(const Test &t){copy_cons_call++;}
};

#define BEGIN_TEST(name) {cout<<"Testing "<<name<<endl;}
#define END_TEST() {cout<<"\tPassed:"<<pass<<"/"<<total<<endl<<endl; grand_total += total; total_pass += pass;}
#define BEGIN_TESTCASE(name) cout<<"\t"<<name<<"..."; int initial_pass = pass;
#define END_TESTCASE() {if(initial_pass == pass) \
                            cout<<"PASS\n"; \
                        else \
                            cout<<"FAIL\n"; }

void TestHVector();
