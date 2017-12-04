// List.h

#ifndef LIST__H
#define LIST__H

/*
 * Creation of a new container
 * This container provides in average constant time
 * for find,
 * for insert and delete in average O(1) but worst case in 0(n)
 * The need for this container is because
 * for every node we check if present in two containers
 * We use deque and unordered_set to provide
 * this functionality
 * The list contains pointers
 * to State objects and is not supposed
 * to be copied and assign
 */

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>

#include "State.h"

using std::vector;
using std::deque;
using std::unordered_set;
using std::ostream;


using StatePtr = State*;
struct StateComparator
{
   bool operator()
        (const StatePtr &s1, const StatePtr &s2) const;
};
struct StateHasher
{
    std::size_t operator() (const StatePtr s) const;
};


enum class List_Type
{
    STACK,
    QUEUE
};

// TODO change StatePtr to std:.shared_ptr
class List
{
private:

    // store pointers to objects
    deque<StatePtr > m_states;
    // container for constant time functions
    unordered_set<StatePtr, StateHasher, StateComparator> m_indexStates;

    int m_min_cost;
    int m_max_level_reached;
    List_Type m_type;


public:

    // default and empty constructor
    List(List_Type type);

    // no copy constructor and assignment constructor
    List (const List& ) = delete;
    List& operator=(const List& ) = delete;

    bool find(StatePtr s) const;
    bool insert(StatePtr s);
    bool empty() const;
    int size() const;
    /*
     * get access front value
     */
    StatePtr acquire();
    int getLevel() const;
    // for debug
    const deque<StatePtr>& getStates() const;
    friend ostream& operator<< (ostream &out, const List &l);
};

#endif
