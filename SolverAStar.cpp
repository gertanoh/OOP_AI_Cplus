#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <limits>
#include <utility>
#include <chrono>
#include <string>
#include "State.h"
#include "List.h"
#include "Fringe.h"
using std::ostream;
using std::cout;
using std::endl;
using std::vector;



class Solver
{
private:

	/* data */
	Fringe frontier;
	List explored;

	/* data related to display after searched solved */
	int m_search_depth;
	int m_nodes_expanded;
	int m_max_search_depth;
	std::chrono::duration<double> m_duration;
	vector<Move> m_path_to_goal;

  /*
   * only root state is supposed
   * to have level 0
   */
  void path_to_goal()
  {
  	auto loop_ptr = (explored.top()).get();
  	// cout <<"State from path_to_goal:" << *(loop_ptr) << endl;
    // explored can be empty if first state is goal
    if (loop_ptr->getLevel() != 0)
    {
      m_search_depth = loop_ptr->getLevel();
    	/* from father pointer
    	 * go backward until reach root state
    	 */
    	 do
    	 {
    		//  cout <<"in loop"<< endl;
    		 m_path_to_goal.push_back(loop_ptr->getMove());
    		 // point to father
    		 loop_ptr = loop_ptr->getParent();
    	 }
    	 while (loop_ptr->getLevel() != 0);
    }
    else
    {
      m_search_depth = 0;
    }

  }

  int numInver(vector<int> values)
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
public:

  Solver(): explored(List_Type::STACK),
  							m_search_depth(0),m_nodes_expanded(0),
                m_max_search_depth(0)
  {
  }

	// no copy constructor and
	// assignment constructor
  Solver (const Solver& ) = delete;
	Solver& operator=(const Solver& ) = delete;
	/* solve the search problem using alg */
  /*
   * Solve the search
   * the Algorithm passed
   * use of A star algorithm
   * return true if solution is found
   */
  bool solve(vector<int> values)
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
    #ifdef TEST
    int i = 0;
    while ( i++<1 && !solved )
    #else
		while ( (!frontier.empty()) && !solved )
    #endif
  	{
  			// get front of frontier
  			auto acquired = frontier.acquire();
        #ifdef TEST
        cout <<"State pop heuristic score: " <<
              acquired.get()->getHeuristic() <<endl;
        #endif
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
  				if (!tmp_ret) {
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
  /*
   * results to display are
   * path_to_goal
   * cost of path = size of path_to_goal
   * nodes expanded
   * search_depth
   * max_search_depth
   * run_time
   */
  void display_results(void)
  {
  	vector<std::string> conv_enum_string {"Up", "Down", "Left", "Right"};
  	path_to_goal();
  	m_nodes_expanded = explored.size() - 1;
  	m_max_search_depth = frontier.getMaxDepth();

  	// display
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

};
const vector<vector<int>> testsEven {{1,2,5,3,4,0,6,7,8},
													 			{6,1,8,4,0,2,7,3,5},
													 			{8,6,4,2,1,3,5,7,0},
													 			{3,1,2,0,4,5,6,7,8}};

const vector<vector<int>> testsOdd {{1,2,3,8,0,4,7,6,5},
													 			    {1,3,4,8,6,2,7,0,5},
					 			                    {2,8,1,4,6,3,0,7,5},
													 			    {5,6,7,4,0,8,3,2,1}};

const vector<vector<int>> testsOther {
                                    {8,6,7,2,5,4,3,0,1},
													 			    {6,4,7,8,5,0,3,2,1},
                                    {1,3,4,8,0,5,7,2,6},
                                    {1,3,4,8,6,2,0,7,5},
                                    {3,6,4,0,1,2,8,7,5},
                                    {7,2,4,5,0,6,8,3,1}
					 			                    };
void testCases(vector<vector<int>> values)
{
	cout <<"Tests " << endl;
  for (size_t i = 0; i < values.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver>();
		int ret = s->solve(values[i]);
		cout <<"Search has :" <<( (ret)?"Succeed":"Failed") << endl;
		// ok is 0
		if (ret)
		{
			s->display_results();
		}
  }
}
void testSimple(void)
{
  vector<int> val {1,8,2,0,4,3,7,6,5};
  auto s = std::make_shared<Solver>();
  int ret = s->solve(val);
  cout <<"Search has :" <<( (ret)?"Succeed":"Failed") << endl;
  // ok is 0
  if (ret)
  {
    s->display_results();
  }
}

int main(int argc, char const *argv[]) {

  // testSimple();
  // testCases(testsOdd);
  testCases(testsEven);
  // testCases(testsOther);
  return 0;
}
