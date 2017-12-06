// Solver.h

#ifndef SOLVER__H
#define SOLVER__H

/*
 * Solver for 8 puwwle game
 * Uses classes List and State to do so
 * Provides two methods BFS or DFS
 */

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include "List.h"
#include "State.h"

using std::vector;


// enum class Algorithm
// {
// 	BFS,
// 	DFS
// };
class Solver
{
private:

	/* data */
	List frontier;
	List explored;

	/* data related to display after searched solved */
	int m_search_depth;
	int m_nodes_expanded;
	int m_max_search_depth;
	std::chrono::duration<double> m_duration;
	vector<Move> m_path_to_goal;

	void path_to_goal();
public:
	Solver(List_Type type);

	// no copy constructor and
	// assignment constructor
	Solver (const Solver& ) = delete;
	Solver& operator=(const Solver& ) = delete;
	/* solve the search problem using alg */
	bool solve(vector<int> values);

	void display_results(void);
	/* I believe no need for destructor as
	 * sharedPtrVec will take care o functionality
	 */
};
#endif
