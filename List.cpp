//List.cpp


#include <iostream>
#include <boost/functional/hash.hpp>
#include <vector>
#include "List.h"


using std::cout;
using std::endl;
using std::ostream;
using std::deque;
using std::vector;


// custom comparator
bool StateComparator::operator() (const StatePtr &s1, const StatePtr &s2) const
{
    return (s1->getValues() == s2->getValues() );
}
std::size_t  StateHasher::operator() (const StatePtr s) const
{
    std::size_t seed = 0;
    vector<int> tmp = s->getValues_copy() ;
    for (unsigned int i = 0 ; i <tmp.size(); ++i)
    {
        boost::hash_combine(seed, tmp[i]);
    }
    return seed;
}

List::List(List_Type type): m_min_cost(0), m_max_level_reached(0),
                            m_type(type)
{
}

/*
 * check if node alredy present in list
 */
bool List::find(StatePtr s) const
{
    return (m_indexStates.find(s) != m_indexStates.end() );
}
/*
 * insert element in deque
 * depending on the type of list 
 * either front or back
 */
bool List::insert(StatePtr s)
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
        m_states.push_back(std::move(s) );
        ret = true;
    }
    else if( m_type == List_Type::QUEUE ) 
    {
        m_states.push_front(std::move(s) );
        ret = true;
    }
    else
    {
        cout <<"Error, unexpected behaviour in insert from type of list " << endl;
    }
    return ret;
        
}

bool List::empty() const
{
    return m_indexStates.empty();
};
int List::size() const
{
    return m_states.size();
}
StatePtr List::acquire()
{
    
    StatePtr s = m_states.front();
    m_indexStates.erase(s);
    m_states.pop_front();
    
    return s;
}
int List::getLevel() const
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
        out<<"State:"<< *(l.getStates()[i]);
    }
    return out;
};

#ifdef DEBUG
int main()
{
    
    return 0;
}

#endif