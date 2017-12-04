//Solver.cpp
#include <iostream>
#include "Solver.h"

using std::cout;
using std::endl;
using std::ostream;
using std::vector;



/*
 * Initialized frontier with alg
 * explored is default
 * does not matter that i Initialized explroed with alg
 */

Solver::Solver(Algorithm alg): frontier(alg), explored(alg), m_search_depth(0),
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

	State goalState({0,1,2,3,4,5,6,7,8,9});

	auto init = std::make_shared<State>(values);

	// move it to sharedPtrVec
	sharedPtrVec.push_back(std::move(init));

}
