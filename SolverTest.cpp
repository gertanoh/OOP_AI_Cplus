// SolverTest.cpp
#include <iostream>
#include "Solver.h"


using std::cout;
using std::endl;
using std::vector;

void testBFS(void);
void testDFS(void);
void testBadEntryState(void);
void testPressure(void);

const vector<vector<int>> tests {{1,2,5,3,4,0,6,7,8},
													 			{6,1,8,4,0,2,7,3,5},
													 			{8,6,4,2,1,3,5,7,0},
													 			{3,1,2,0,4,5,6,7,8}};
const int NUMBER_TEST = 100;
int main(int argc, char const *argv[]) {
	/* code */
	// testBFS();
	// testDFS();
	testPressure();
	return 0;
}
void testBFS(void)
{
	cout <<"Test pressure BFS " << endl;
  for (size_t i = 0; i < tests.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver>(List_Type::QUEUE);
		int ret = s->solve(tests[i]);
		cout <<"Search has :" <<( (ret)?"Failed":"Succeed") << endl;
		// ok is 0
		if (!ret)
		{
			s->display_results();
		}
  }

}
void testDFS(void)
{
	cout <<"Test pressure DFS " << endl;
	for (size_t i = 0; i < tests.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver>(List_Type::STACK);
		int ret = s->solve(tests[i]);
		cout <<"Search has :" <<( (ret)?"Failed":"Succeed") << endl;
		if (!ret)
		{
			s->display_results();
		}
  }
}
void testBadEntryState(void)
{
	// vector<int> v{};
}

void testPressure(void)
{
	for (size_t i = 0; i < NUMBER_TEST; i++)
	{
		testDFS();
		testBFS();
	}
}
