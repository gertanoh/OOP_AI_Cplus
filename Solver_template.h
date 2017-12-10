// Solver_template.h

#ifndef SOLVER_TEPMLATE__H
#define SOLVER_TEMPLATE__H

/*
 * Solver for 8 puzzle game
 * Uses classes List and State and Fringe to do so
 * using A star algorithm with manhattan distance
 * or BFS or DFS
 */

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include "List.h"
#include "State.h"
#include "Fringe.h"
#include "utils.h"

using std::vector;
using std::cout;
using std::endl;

template<typename T>
class Solver
{
private:

 	/* data */
	T frontier;
	List explored;

	/* data related to display after searched solved */
	int m_search_depth;
	int m_nodes_expanded;
	int m_max_search_depth;
	std::chrono::duration<double> m_duration;
  vector<Move> m_path_to_goal;

	void path_to_goal();
  int numInver(vector<int> values);
public:
  Solver(List_Type type);
  Solver();
 	// no copy constructor and
 	// assignment constructor
 	Solver<T> (const Solver& ) = delete;
 	Solver<T>& operator=(const Solver& ) = delete;
 	/* solve the search problem using alg */
 	bool solve(vector<int> values);

 	void display_results(void);
 	/* I believe no need for destructor as
 	 * sharedPtrVec will take care o functionality
 	 */
};

template<typename T>
Solver<T>::Solver():explored(List_Type::STACK),
              m_search_depth(0),m_nodes_expanded(0),
              m_max_search_depth(0)
{
}
template<typename T>
Solver<T>::Solver(List_Type type): frontier(type),
            explored(List_Type::STACK),m_search_depth(0),
            m_nodes_expanded(0), m_max_search_depth(0)
{
}

/*
 * Solve the search
 * the Algorithm passed
 * Doable by BFS or DFS or A Star
 * return true if solution is found
 */
template<>
bool Solver<Fringe>::solve(vector<int> values)
{

 auto start = std::chrono::system_clock::now();
 int ret = 0;
 vector<int> goal;
 // get inversion to know which goal state can be reached
 int inv = numInver(values);
 if (inv%2 == 0)
 {
   // set goal to reach
   State::setGoal(Goal::STANDARD_GOAL);
   goal = {0,1,2,3,4,5,6,7,8};
 }
 else
 {
   // set goal to reach
   State::setGoal(Goal::NON_STANDARD_GOAL);
   goal = {1,2,3,8,0,4,7,6,5};
 }
 bool solved = false;
 State goalState(goal);
 auto init = std::make_shared<State>(values);
 // move it to frontier
 frontier.insert(std::move(init));
 while ( (!frontier.empty()) && !solved )
 {
   // get front of frontier
   auto acquired = frontier.acquire();
   // insert into explored
   explored.insert(acquired);
   // check if goal state
   if ( (acquired.get()->getValues()) == goalState)
   {
     solved = true;
     ret = 1;
   }
   else
   {
     // expand the search
     int tmp_ret = -1;
     auto children = generateChildren(*acquired.get(), tmp_ret);
     // ok is 0
     if (!tmp_ret)
     {
       // insert state into frontier
       for (int i = 0; i<children.size(); ++i)
       {
         auto state = std::make_shared<State>(
           std::move(children[i].second), acquired->getLevel()+1,
           children[i].first, acquired.get());
           // unseen state in explored or list
         if (!frontier.find(state) && !explored.find(state) )
         {
           frontier.insert(std::move(state));
         }
         // state already in frontier but with lower score
         // allow duplicate, can not remove state with priority_queue
         else if (frontier.find(state) && !explored.find(state) )
         {
           int prev_score = frontier.getPriority(state);
           if (state->getHeuristic() < prev_score)
           {
             frontier.insert(std::move(state));
           }
         }
       }
     }
     else
     {
       cout <<"Error in generateChildren" << endl;
       solved = false;
       ret = 0;
     }
   }
 }
 // stop chrono
 auto end = std::chrono::system_clock::now();
 m_duration = end - start;
 return ret;
}

template<>
bool Solver<List>::solve(vector<int> values)
{

  auto start = std::chrono::system_clock::now();
  int ret = 0;
  vector<int> goal;
  // get inversion to know which goal state can be reached
  int inv = numInver(values);
  if (inv%2 == 0)
  {
    // set goal to reach
    State::setGoal(Goal::STANDARD_GOAL);
    goal = {0,1,2,3,4,5,6,7,8};
  }
  else
  {
    //set goal to reach
    State::setGoal(Goal::NON_STANDARD_GOAL);
    goal = {1,2,3,8,0,4,7,6,5};
  }
  bool solved = false;
  State goalState(goal);
  auto init = std::make_shared<State>(values);
  // move it to frontier
  frontier.insert(std::move(init));
  while ( (!frontier.empty()) && !solved )
  {
    // get front of frontier
    auto acquired = frontier.acquire();
    // insert into explored
    explored.insert(acquired);
    // check if goal state
    if ((acquired.get()->getValues()) == goalState)
    {
      solved = true;
      ret = 1;
    }
    else
    {
      // expand the search
      int tmp_ret = -1;
      auto children = generateChildren(*acquired.get(), tmp_ret);
      // ok is 0
      if (!tmp_ret)
      {
        // insert state into frontier
        if (frontier.getType() == List_Type::QUEUE)
        {
          for (size_t i = 0; i < children.size(); ++i) {
              auto state = std::make_shared<State>(
                std::move(children[i].second), acquired->getLevel()+1,
                children[i].first, acquired.get());
              if (!frontier.find(state) && !explored.find(state) )
              {
                frontier.insert(std::move(state));
              }
          }
        }
        else if (frontier.getType() == List_Type::STACK)
        {
          for (int i = children.size() -1; i>=0; --i) {
              auto state = std::make_shared<State>(
                std::move(children[i].second), acquired->getLevel()+1,
                children[i].first, acquired.get());
              if (!frontier.find(state) && !explored.find(state) )
              {
                frontier.insert(std::move(state));
              }
          }
        }
        else
        {
          cout <<"Undefined Type of frontier list " << endl;
          ret = -1;
          solved = false;
        }
      }
      else
      {
      cout <<"Error in generateChildren" << endl;
      solved = false;
      ret = 0;
      }
    }
  }
  // stop chrono
  auto end = std::chrono::system_clock::now();
  m_duration = end - start;
  return ret;
}
/*
 * only root state is supposed
 * to have level 0
 */
template <typename T>
void Solver<T>::path_to_goal()
{

  auto loop_ptr = (explored.top()).get();
  // cout <<"State from path_to_goal:" << *(loop_ptr) << endl;
  m_search_depth = loop_ptr->getLevel();
  /* from father pointer
  * go backward until reach root state
  */
  do
  {
  m_path_to_goal.push_back(loop_ptr->getMove());
  // point to father
  loop_ptr = loop_ptr->getParent();
  }
  while (loop_ptr->getLevel() != 0);
}


/*
 * Check if board is solvable
 * count inversions
 */
template<typename T>
int Solver<T>::numInver(vector<int> values)
{
  int inv_count = 0;
  for (int i = 0; i < 8; i++)
  {
   for (int j = i+1; j < 9; j++)
   {
     // Value 0 is used for empty space
     if (values[j] && values[i] &&  values[i] > values[j])
     {
       inv_count++;
     }
   }
  }

  return  inv_count;
}
/*
 * results to display are
 * path_to_goal
 * cost of path = size of path_to_goal
 * nodes expanded
 * search_depth
 * max_search_depth
 * run_time
 */
template<typename T>
void Solver<T>::display_results(void)
{
  vector<std::string> conv_enum_string {"Up", "Down", "Left", "Right"};
  path_to_goal();
  m_nodes_expanded = explored.size() - 1;
  m_max_search_depth = frontier.getMaxDepth();

  // reverse display as we print from root
  cout <<"path_to_goal:[";
  for (int i = m_path_to_goal.size() -1; i >=0; i--)
  {
    cout <<"'"<<conv_enum_string[static_cast<int>(m_path_to_goal[i])]\
        <<"'" << ( (i == 0)?"]":",");
  }
  cout <<endl;
  cout <<"cost_of_path:"<< m_path_to_goal.size()<< endl;
  cout <<"nodes_expanded:"<<m_nodes_expanded<<endl;
  cout <<"search_depth:"<<m_search_depth<<endl;
  cout <<"max_search_depth:"<<m_max_search_depth<<endl;
  cout <<"running_time:"<<m_duration.count()<<endl;

}
#endif
