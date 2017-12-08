#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <memory>
#include <queue>
#include <limits>
#include <utility>
#include <chrono>
#include <string>
#include "../State.h"
#include "../List.h"

using std::priority_queue;
using std::unordered_multiset;
using std::ostream;
using std::cout;
using std::endl;


struct QueueCompare
{
  bool operator() (const StatePtr &s1, const StatePtr &s2) const
  {
    return (s1->getHeuristic() > s2->getHeuristic() );
  }
};

class FringeA
{
private:

    // store pointers to objects
    /* Object should be create on heap */
    priority_queue<StatePtr, std::vector<StatePtr>,
          QueueCompare> m_states;
    unordered_multiset<StatePtr, StateHasher,
        StateComparator > m_indexStates;

    int m_max_level_reached;

public:

    // default and empty constructor
    FringeA(): m_max_level_reached(0)
    {
    };

    // no copy constructor and assignment constructor
    FringeA (const List&) = delete;
    FringeA& operator=(const List&) = delete;

    // ~List();
    /*
     * check if node alredy present in list
     */
    bool find(const StatePtr& s) const
    {
        return (m_indexStates.find(s) != m_indexStates.end() );
    }
    bool insert(const StatePtr& s)
    {
        // update depth of list
        bool ret = false;
        if (s->getLevel() > m_max_level_reached)
        {
            m_max_level_reached = s->getLevel() ;
        }
        // insert
        m_indexStates.insert(s);
        m_states.push(s);
        return ret;

    }
    bool empty(void) const
    {
        return m_indexStates.empty();
    };
    int size(void) const
    {
        return m_states.size();
    }
    int getMaxDepth(void)
    {
      return m_max_level_reached;
    }

    StatePtr acquire(void)
    {
        /* It is okay as we transfer
         * Ownership and pop right after
         * TODO std::move
         */
        StatePtr s = m_states.top();
        m_indexStates.erase(s);
        m_states.pop();

        return s;
    }
    int getPriority(const StatePtr& s)
    {
        auto iterators = m_indexStates.equal_range(s);
        int min = std::numeric_limits<int>::max();
        for (auto iter = iterators.first; iter != iterators.second; ++iter)
        {
            if (min < (*iter).get()->getHeuristic() )
            {
              min = (*iter).get()->getHeuristic();
            }
        }
        return min;
    }
};



class Solver
{
private:

	/* data */
	FringeA frontier;
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
    if (!loop_ptr)
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
    		//  cout <<"Before while " << endl;
    	 }
    	 while (loop_ptr->getLevel() != 0);
    }
    else
    {
      m_search_depth = 0;
    }

  }
  /*
   * Check if board is solvable
   * count inversions
   */
  int numInver(vector<int> values)
  {
      int inv_count = 0;
      for (int i = 0; i < 9 - 1; i++)
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

    // check if board is solvable
    // bool solvable = isSolvable(values);
    // if (!solvable)
    // {
    //   cout <<"Board is not solvable"<<endl;
    //   return false;
    // }
  	// start chrono
  	auto start = std::chrono::system_clock::now();
  	int ret = 0;
    vector<int> goal;
    // get inversion to know which goal state can be reached
    int inv = numInver(values);
    cout <<"Inv counts:"<<inv << std::endl;
    if (inv%2 == 0)
    {
      cout <<"Goal even state "<<endl;
      goal = {0,1,2,3,4,5,6,7,8};
    }
    else
    {
      cout <<"Goal odd state "<<endl;
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
const vector<vector<int>> tests {{1,2,5,3,4,0,6,7,8},
													 			{6,1,8,4,0,2,7,3,5},
													 			{8,6,4,2,1,3,5,7,0},
													 			{3,1,2,0,4,5,6,7,8}};

const vector<vector<int>> testsNot {{1,2,3,8,0,4,7,6,5},
													 			    {1,3,4,8,6,2,7,0,5},
					 			                    {2,8,1,4,6,3,0,7,5},
													 			    {5,6,7,4,0,8,3,2,1}};

void testCases(void)
{
	cout <<"Tests " << endl;
  for (size_t i = 0; i < testsNot.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver>();
		int ret = s->solve(testsNot[i]);
		cout <<"Search has :" <<( (ret)?"Succeed":"Failed") << endl;
		// ok is 0
		if (ret)
		{
			s->display_results();
		}
  }
}
void test(void)
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
  /* code */
  testCases();
  return 0;
}
