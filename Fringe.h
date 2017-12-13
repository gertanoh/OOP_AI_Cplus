// Fringe .h


#ifndef FRINGE__H
#define FRINGE__H

/*
 * Container with std::priority_queue
 * Also with unordered_multiset
 * to allow duplicate states
 * and constant search time
 */

 #include <iostream>
 #include <vector>
 #include <queue>
 #include <memory>
 #include <unordered_set>
 #include "State.h"
 #include "utils.h"

 using std::priority_queue;
 using std::unordered_multiset;
 using std::ostream;


class Fringe
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
  Fringe();
  // no copy constructor and assignment constructor
  Fringe (const Fringe&) = delete;
  Fringe& operator=(const Fringe&) = delete;

  bool find(const StatePtr& s) const;
  bool insert(const StatePtr& s);
  bool empty(void) const;
  int size(void) const;
  int getMaxDepth(void);
  StatePtr acquire(void);
  int getPriority(const StatePtr& s);
};

#endif
