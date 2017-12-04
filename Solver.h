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
#include "List.h"
#include "State.h"

using std::vector;

using sharedPtrVec = vector<std::shared_ptr<State> >;

enum class Algorithm
{
	BFS,
	DFS
};
class Solver
{
private:

	/* data */

	/* vector which holds pointers to state created during search */
	sharedPtrVec pointers_vec;

	List frontier;
	List explored;


	/* data related to display after searched solved */
	int m_search_depth;
	int m_nodes_expanded;
	int m_max_search_depth;
	vector<Move> m_path_to_goal;

public:
	Solver(Algorithm alg);

	/* solve the search problem using alg */
	bool solve(vector<int> values);

	void display_results();

	/* I believe no need for destructor as
	 * sharedPtrVec will take care o functionality
	 */
};
#endif
