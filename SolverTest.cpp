// SolverTest.cpp
#include <iostream>
#include "Solver_template.h"
#include "List.h"
#include "Fringe.h"


using std::cout;
using std::endl;
using std::vector;



const vector<vector<int>> tests
	{{1,2,5,3,4,0,6,7,8},
	{6,1,8,4,0,2,7,3,5},
	{8,6,4,2,1,3,5,7,0},
	{3,1,2,0,4,5,6,7,8}};
const vector<vector<int>> testsEven
	{{1,2,5,3,4,0,6,7,8},
	{6,1,8,4,0,2,7,3,5},
	{8,6,4,2,1,3,5,7,0},
	{3,1,2,0,4,5,6,7,8}};

const vector<vector<int>> testsOdd
	{{1,2,3,8,0,4,7,6,5},
  {1,3,4,8,6,2,7,0,5},
  {2,8,1,4,6,3,0,7,5},
  {5,6,7,4,0,8,3,2,1}};

const vector<vector<int>> testsOther
	{{8,6,7,2,5,4,3,0,1},
  {6,4,7,8,5,0,3,2,1},
	{1,3,4,8,0,5,7,2,6},
	{1,3,4,8,6,2,0,7,5},
  {3,6,4,0,1,2,8,7,5},
  {7,2,4,5,0,6,8,3,1}};


void testBFS(void);
void testDFS(void);
void testBadEntryState(void);
void testPressure(void);
void testSimple(void);
void testCases(vector<vector<int>> values);


int main(int argc, char const *argv[]) {
	/* code */
	// testBFS();
	// testDFS();
	// testSimple();
	// testCases(testsOdd);
	// testCases(testsEven);
	testCases(testsOther);
	return 0;
}
void testBFS(void)
{
	cout <<"Test BFS " << endl;
  for (size_t i = 0; i < tests.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver<List>>(List_Type::QUEUE);
		int ret = s->solve(tests[i]);
		cout <<"Search has :" <<( (ret)?"Succeed":"Failed") << endl;
		if (ret)
		{
			s->display_results();
		}
  }

}
void testDFS(void)
{
	cout <<"Test  DFS " << endl;
	for (size_t i = 0; i < tests.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver<List>>(List_Type::STACK);
		int ret = s->solve(tests[i]);
		cout <<"Search has :" <<( (ret)?"Succeed":"Failed") << endl;
		if (ret)
		{
			s->display_results();
		}
  }
}
void testCases(vector<vector<int>> values)
{
	cout <<"Tests " << endl;
  for (size_t i = 0; i < values.size(); i++)
	{
  	/* code */
		auto s = std::make_shared<Solver<Fringe>>();
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
  auto s = std::make_shared<Solver<Fringe>>();
  int ret = s->solve(val);
  cout <<"Search has :" <<( (ret)?"Succeed":"Failed") << endl;
  if (ret)
  {
    s->display_results();
  }
}
