//List.cpp


#include <iostream>
#include <vector>
#include "List.h"


using std::cout;
using std::endl;
using std::ostream;
using std::deque;
using std::vector;





List::List(List_Type type):  m_max_level_reached(0),
                            m_type(type)
{
}


/*
 * check if node alredy present in list
 */
bool List::find(const StatePtr& s) const
{
  return (m_indexStates.find(s) != m_indexStates.end() );
}
/*
 * insert element in deque
 * depending on the type of list
 * either front or back
 */
bool List::insert(const StatePtr& s)
{
  // update depth of list
  bool ret = false;
  if (s->getLevel() > m_max_level_reached)
  {
      m_max_level_reached = s->getLevel() ;
  }
  // insert
  m_indexStates.insert(s);
  if (m_type == List_Type::STACK )
  {
      // possibility to use std::move
      m_states.push_front(s);
      ret = true;
  }
  else if( m_type == List_Type::QUEUE )
  {
      m_states.push_back(s);
      ret = true;
  }
  else
  {
      cout <<"Error, unexpected behaviour in insert from type of list " << endl;
  }
  return ret;

}
bool List::empty(void) const
{
  return m_states.empty();
};
int List::size(void) const
{
  return m_states.size();
}
List_Type List::getType(void)
{
  return m_type;
}
int List::getMaxDepth(void)
{
  return m_max_level_reached;
}
StatePtr List::acquire(void)
{
  /* It is okay as we transfer
   * Ownership and pop right after
   */
  StatePtr s = m_states.front();
  m_indexStates.erase(s);
  m_states.pop_front();

  return s;
}
StatePtr List::top(void)
{
  return m_states.front();
}
int List::getLevel(void) const
{
  return m_max_level_reached;
}
const deque<StatePtr>& List::getStates() const
{
  return m_states;
}
ostream& operator<< (ostream &out, const List &l)
{
  int size = l.size();
  out <<"List size is " << size << std::endl;
  for (int i = 0 ; i <size; ++i)
  {
      out<<"State:"<< *(l.getStates()[i]).get();
  }
  return out;
};
