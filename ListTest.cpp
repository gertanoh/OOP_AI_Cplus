// ListTest.cpp

#include <iostream>
#include "List.h"

using std::cout;
using std::endl;


void testCreation();
void testInsert();
void testFind();
void testAcquire();
int main()
{
    
    testCreation();
    testInsert();
    testFind();
    testAcquire();
    return 0;
}

void testCreation()
{
    List l(List_Type::STACK);
    cout <<"List :" << l << endl;
}

void testInsert()
{
    cout <<"Test creation " << endl;
    List l(List_Type::STACK);
    vector<int> test_1{1,2,5,3,4,0,6,7,8};
    State test(test_1);
    bool ret = l.insert(&test);
    if (ret)
    {
        cout <<"ok " << endl;
        cout <<"List: "<< l <<endl;
    }
    else
    {
        cout <<"Fail" << endl;
    }
}
void testFind()
{
    cout <<"Test Find " << endl;
    List l(List_Type::STACK);
    vector<int> test_1{1,2,5,3,4,0,6,7,8};
    vector<int> test_2{3,1,2,0,4,5,6,7,8};
    State test1(test_1);
    State test2(test_2);
    bool ret = l.insert(&test2);
    if (ret)
    {
        cout << "Test insertion:" <<( (l.find(&test2) )? "Ok": "Fail" )<< endl;
        cout << "Test non nsertion:" <<( (l.find(&test1) )? "Ok": "Fail") << endl;
    }
    else
    {
        cout <<"Fail due to failure in test insertion" << endl;
    }
}

void testAcquire()
{   
    cout <<"Test Acquire " << endl;
    List l(List_Type::STACK);
    vector<int> test_1{1,2,5,3,4,0,6,7,8};
    State test1(test_1);
    bool ret = l.insert(&test1);
    if (ret)
    {
        StatePtr s = l.acquire();
        cout << "testAcquire:" <<( (*s == test1)? "Ok": "Fail" ) << endl;
    }
    else
    {
        cout <<"Fail due to failure in test insertion" << endl;
    }
}
    