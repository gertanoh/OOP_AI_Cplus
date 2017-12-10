//State.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "State.h"

using std::vector;
using std::cout;
using std::endl;


Map manhattan_distance()
{
  Map m;
  int index1 = -1;
  int n0 = 3;
  for (int i = 0; i <n0; ++i)
  {
    for (int j = 0; j <n0; ++j)
    {
      index1 += 1;
      int index2 = -1;
      for (int k = 0; k <n0; ++k)
      {
        for (int l = 0; l <n0; ++l)
        {
          index2 += 1;
          std::string str = std::to_string(index1)
          +std::to_string(index2);
          m.insert(std::make_pair(str, abs(i-k)+abs(j-l)) );
        }
      }
    }
  }

  return m;
}


// by default, we try to reach standard goal
Goal State::m_goal_to_reach = Goal::STANDARD_GOAL;
void State::setGoal(Goal g)
{
  m_goal_to_reach = g;
}
Map State::man_distance = manhattan_distance();

/* calculate heuristic_function
 * return void
 */
void State::heuristic_function(void)
{
  // manhattan distance heuristic
  int dist = 0;
  if (State::m_goal_to_reach == Goal::STANDARD_GOAL)
  {
    // std::cout << "here" << '\n';
    // don't count 0
    for (int i = 0; i <9; ++i)
    {
      if (m_values[i] != 0)
      {
        std::string str = std::to_string(i)+
            std::to_string(m_values[i]);
        dist += man_distance[str];
      }
    }
  }
  else if(State::m_goal_to_reach == Goal::NON_STANDARD_GOAL )
  {
    // std::cout << "here" << '\n';
    // find indexes of digits from 1 to 8
    // in state and in goal
    vector<int> goal_indexes {0,1,2,5,8,7,6,3};
    for (int i = 1; i <9; ++i)
    {
      int index = std::distance(m_values.begin(),
        find(m_values.begin(), m_values.end(), i) );
      dist += abs( (index%3) - (goal_indexes[i-1]%3))
      + abs((index/3) - (goal_indexes[i-1]/3));
    }
  }
  else
  {
    // unknown type
  }


  m_heuristic_score = dist;
}

State::State() = default;

State::State(vector<int> values):m_values(values),
        m_level(0), m_heuristic_score(0), m_parentPtr(nullptr)
{
    // default initialization of m_to_state is UP
  m_to_state = Move::UP;
  m_heuristic_score = 0;
  heuristic_function();
}

// constructor used to expand the tree search
State::State(vector<int> values, int level, Move m, State* ptr):
        m_values(values), m_level(level), m_to_state(m)
{
  // no need to check pointer here
  m_parentPtr = ptr;
  m_heuristic_score = 0;
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
  return m_parentPtr;
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
 * order is up, down, left , right
 * -1 is a move not allowed
 */
vector<vector<int>> look_up_table { {-1,-1,-1,0,1,2,3,4,5},
                              {3,4,5,6,7,8,-1,-1,-1},
                              {-1,0,1,-1,3,4,-1,6,7},
                              {1,2,-1,4,5,-1,7,8,-1} };

// Not the best way to return error but will do
States_values generateChildren(const State& father, int &ret)
{
  States_values values;
  vector<Move> moves{Move::UP, Move::DOWN, Move::LEFT, Move::RIGHT};
  ret = -1;
  //  find value of position 0
  // no random iterator have been used and index can only be positive
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
    // there is four possible states
    for (int i = 0; i <4; ++i)
    {
      if (look_up_table[i][index] != -1 )
      {
          // get copy
          vector<int> copy = father.getValues_copy();
          // swap index of 0 and correspondat move from look_up_table
          std::swap(copy[look_up_table[i][index] ], copy[index] );
          auto tmp = std::make_pair(moves[i], std::move(copy));
          values.push_back(std::move(tmp));
      }
    }
  }
  ret = 0;
  return values;
}
