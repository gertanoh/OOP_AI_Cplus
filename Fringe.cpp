// Fringe.cpp

#include <iostream>
#include "Fringe.h"



Fringe::Fringe():m_max_level_reached(0)
{
}
/*
 * check if node alredy present in list
 */
bool Fringe::find(const StatePtr& s) const
{
  return (m_indexStates.find(s) != m_indexStates.end() );
}
bool Fringe::insert(const StatePtr& s)
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
bool Fringe::empty(void) const
{
  return m_indexStates.empty();
};
int Fringe::size(void) const
{
  return m_states.size();
}
int Fringe::getMaxDepth(void)
{
  return m_max_level_reached;
}

StatePtr Fringe::acquire(void)
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
int Fringe::getPriority(const StatePtr& s)
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

#ifdef TESTS_UNITS
int main()
{
  return 0;
}
#endif
