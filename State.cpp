//State.cpp


#include <iostream>
#include <vector>
#include <algorithm>
#include "State.h"

using std::vector;
using std::cout;
using std::endl;


/* calculate heuristic_function
 */
void State::heuristic_function()
{
    /* misplaced tiles */
    std::vector<int> goal_state{0,1,2,3,4,5,6,7,8,9};
    int result = 0;
    for (unsigned int i = 0; i < goal_state.size(); ++i)
    {
        if (goal_state[i] != m_values[i] )
        {
            result += 1;
        }
    }
    m_heuristic_score = result;
}

State::State() = default;

State::State(vector<int> values):m_values(values),
        m_level(0), m_heuristic_score(0), parentPtr(nullptr)
{
    /* default initialization of m_to_state is UP */
    m_to_state = Move::UP;
}

// constructor used to expand the tree search
State::State(vector<int> values, int level, Move m, State* ptr):
        m_values(values), m_level(level), m_to_state(m)
{
    if (ptr) 
    {
        parentPtr = ptr;
    }
    else
    {
        parentPtr = nullptr;
    }
    heuristic_function();
    m_heuristic_score += m_level;
}

// getters
const vector<int>& State::getValues() const
{
    return m_values;
}

// by value
vector<int> State::getValues_copy() const
{
    return m_values;
}

int State::getLevel() const
{
    return m_level;
}
Move State::getMove() const
{
    return m_to_state;
}
int State::getHeuristic() const 
{
    return m_heuristic_score;
}

State* State::getParent() const
{
    return parentPtr;
}
// just realised don't need to be friend
ostream& operator<< (ostream &out, const State &s)
{
    for (int i = 0 ; i <9; ++i)
    {
        out << s.m_values[i]<<",";
    }
    return out;
}
bool operator== (const State& s1, const State& s2)
{
    return (s1.getValues() == s2.getValues() );
}
bool operator!= (const State& s1, const State& s2)
{
    return !(s1 == s2);
}
bool operator> (const State& s1, const State& s2)
{
    return s1.getHeuristic() > s2.getHeuristic();
}


/* creates the vector values for children
 * used a hard coded lookup table instead of switch
 * values are return by copy but compuler would move
 * -1 is a move not allowed
 */
States_values look_up_table { {-1,-1,-1,0,1,2,3,4,5},
                              {3,4,5,6,7,8,-1,-1,-1},
                              {-1,0,1,-1,3,4,-1,6,7},
                              {1,2,-1,4,5,-1,7,8,-1} };

/* Not the best way to return error but will do  */
States_values generateChildren(const State& father, int &ret)
{
    States_values values;
    ret = -1;
    /*  find value of position 0 */
    /* no random iterator have been used and index can only be positive */
    unsigned int index = std::distance (father.getValues().begin(), \
                            std::find(father.getValues().begin(), \
                                      father.getValues().end(), 0));
    if (index >= father.getValues().size())
    {
        // log unexpected behaviour
        std::cout <<"Empty tile is not present" << std::endl; 
    }
    else 
    {
        /* there is four possible states */
        for (int i = 0; i <4; ++i)
        {
            
            if (look_up_table[i][index] != -1 )
            {
                /* get copy */
                vector<int> copy = father.getValues_copy();
                /* swap index of 0 and correspondat move from look_up_table */
                std::swap(copy[look_up_table[i][index] ], copy[index] );
                
                values.push_back(copy);
            }
        }
    }
    ret = 0;
    return values;
} 
