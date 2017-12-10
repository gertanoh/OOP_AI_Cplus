// ListTest.cpp

#include <iostream>
#include <memory>
#include "List.h"
#include "utils.h"

using std::cout;
using std::endl;


void testCreation();
void testInsert();
void testFind();
void testAcquire();
int main()
{

  testCreation();
  testFind();
  testInsert();
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
  auto test = std::make_shared<State>(test_1);
  bool ret = l.insert(test);
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
  auto test1 = std::make_shared<State>(test_1);
  auto test2 = std::make_shared<State>(test_2);
  bool ret = l.insert(test2);
  if (ret)
  {
    cout << "Test insertion:" <<( (l.find(test2) )? "Ok": "Fail" )<< endl;
    cout << "Test non insertion:" <<( (l.find(test1) )? "Ok": "Fail") << endl;
    cout <<"Ownership Test: "<< test2.use_count() << endl;
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
  auto test1 = std::make_shared<State>(test_1);
  bool ret = l.insert(test1);
  if (ret)
  {
    StatePtr s = l.acquire();
    cout << "element just pop out: " << *s.get() << endl;
    cout << "testAcquire:" <<( (*s.get() == *test1.get())? "Ok": "Fail" ) << endl;
  }
  else
  {
    cout <<"Fail due to failure in test insertion" << endl;
  }
}
