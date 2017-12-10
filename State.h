// State.h

#ifndef STATE__H
#define STATE__H

/*
 * represents a state
 * and provides the functions required
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "utils.h"
#include <boost/functional/hash.hpp>


using std::vector;
using std::ostream;
using std::pair;



class State
{

private:

  vector<int> m_values;
  int m_level;
  Move m_to_state;
  int m_heuristic_score;
  /* Parent pointer */
  State* m_parentPtr;
  /* to calculate heuristic score of the state */
  void heuristic_function(void);


public:

  static Map man_distance;
  static Goal m_goal_to_reach;
  // default constructor
  State();
  // create a state with values and default values for all other parameters
  State(vector<int> values);
  // create a state initialized with parameter
  State(vector<int> values, int level, Move m, State* ptr);

  // No need to declare specified copy and assign constructor


  // getters
  const vector<int>& getValues() const;
  // get by value
  vector<int> getValues_copy() const;
  int getLevel() const;
  Move getMove() const;
  int getHeuristic() const;
  State* getParent() const;

  // setters
  static  void setGoal(Goal g);
  friend ostream& operator<< (ostream &out, const State &s);
};

States_values generateChildren(const State& father, int &ret);

bool operator== (const State& s1, const State& s2);
bool operator!= (const State& s1, const State& s2);
bool operator> (const State& s1, const State& s2);

struct StateComparator
{
  // custom comparator
  bool operator() (const StatePtr &s1, const StatePtr &s2) const
  {
      return (s1->getValues() == s2->getValues() );
  }
};
struct StateHasher
{
  std::size_t  operator() (const StatePtr s) const
  {
    std::size_t seed = 0;
    vector<int> tmp = s->getValues_copy() ;
    for (unsigned int i = 0 ; i <tmp.size(); ++i)
    {
        boost::hash_combine(seed, tmp[i]);
    }
    return seed;
  }
};

struct QueueCompare
{
  bool operator() (const StatePtr &s1, const StatePtr &s2) const
  {
    return (s1->getHeuristic() > s2->getHeuristic() );
  }

};


#endif
