// StateTest.cpp
#include <iostream>
#include <vector>
#include "State.h"

using std::vector;
using std::cout;
using std::endl;

int main()
{
    vector<int> goal_state{0,1,2,3,4,5,6,7,8,9};
    vector<int> test_1{1,2,5,3,4,0,6,7,8};
    vector<int> test_4{3,1,2,0,4,5,6,7,8};
    State goal(goal_state);
    State test2(goal);
    State test(test_1);
    cout <<"Goal State :" << goal << endl;

    cout <<"Goal is equal to test_2: "<< ((goal == test2) ? "Yes": "No") << endl;
    cout <<"test_1 is equal to test_2: "<< ((test_1 == test2) ? "Yes": "No") << endl;

    cout <<"test State :" << test << endl;
    int ret = 0;
    States_values v = generateChildren(test, ret);
    if (!ret)
    {
        for (unsigned int i= 0 ; i<v.size(); ++i)
        {
            // cout <<"Vector "<< i << ": ";
            auto tmp = v[i];
            // need of static cast to integer for unscoped
            // enum
            cout <<"Move: " << static_cast<int>(tmp.first)<<", ";
            auto tmp_vec = tmp.second;
            for (int j = 0 ; j <9; ++j)
            {

                cout << tmp_vec[j]<<",";
            }
            cout << endl;
        }
    }
    else
    {
        cout <<"Error in generateChildren " << endl;
    }

    // test parent
    cout <<"test2 State :" << test2 << endl;
    State test4(test_4, 2, Move::DOWN, &test2);
    State* ptr = test4.getParent();
    cout <<"test2 State ptr :" << *ptr << endl;


    return 0;
}
