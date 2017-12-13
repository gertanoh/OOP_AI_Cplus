//Solver.cpp
#include <iostream>
#include <string>
#include "Solver.h"

using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::string;


/*
 * Initialized frontier with alg
 * explored is default
 * does not matter that i Initialized explroed with alg
 */

/* TODO
 * Implement a template container
 * to add a star functionality
 * and code duplication
 * Implement mah
 */

Solver::Solver(List_Type type): frontier(type),
							explored(List_Type::STACK),m_search_depth(0),
							m_nodes_expanded(0), m_max_search_depth(0)
{

}

/*
 * Solve the search
 * the Algorithm passed
 * Doable by BFS or DFS
 * return true if solution is found
 */
bool Solver::solve(vector<int> values)
{

	// start chrono
	auto start = std::chrono::system_clock::now();
	int ret = -1;
	bool solved = false;
	State goalState({0,1,2,3,4,5,6,7,8});
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
			ret = 0;
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
					for (size_t i = 0; i < children.size(); ++i)
					{
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
					for (int i = children.size()-1; i>=0; --i)
					{
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
				ret = -1;
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
void Solver::path_to_goal()
{
	auto loop_ptr = (explored.top()).get();
	// cout <<"State from path_to_goal:" << *(loop_ptr) << endl;
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

/*
 * results to display are
 * path_to_goal
 * cost of path = size of path_to_goal
 * nodes expanded
 * search_depth
 * max_search_depth
 * run_time
 */
void Solver::display_results(void)
{
	vector<string> conv_enum_string {"Up", "Down", "Left", "Right"};
	path_to_goal();
	m_nodes_expanded = explored.size() - 1;
	m_max_search_depth = frontier.getMaxDepth();

	// display
	// reverse display as we print from root
	#ifdef DEBUG
	cout <<"path_to_goal:[";
	for (int i = m_path_to_goal.size() -1; i >=0; i--)
	{
		cout <<"'"<<conv_enum_string[static_cast<int>(m_path_to_goal[i])]\
				<<"'" << ( (i == 0)?"]":",");
	}
	cout <<endl;
	#endif
	cout <<"cost_of_path:"<< m_path_to_goal.size()<< endl;
	cout <<"nodes_expanded:"<<m_nodes_expanded<<endl;
	cout <<"search_depth:"<<m_search_depth<<endl;
	cout <<"max_search_depth:"<<m_max_search_depth<<endl;
	cout <<"running_time:"<<m_duration.count()<<endl;

}
