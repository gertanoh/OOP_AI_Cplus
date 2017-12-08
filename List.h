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
 * After considerations,
 * I decided to change poitners to std::shared_ptr
 * This List will take of delete himself
 * But this comes at the cost of non behaviour
 * for stack-allocated object
 */

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <memory>
#include <queue>
#include "State.h"

using std::vector;
using std::deque;
using std::unordered_set;
using std::ostream;



using StatePtr = std::shared_ptr<State>;
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

class List
{
private:

    // store pointers to objects
    /* Object should be create on heap */
    deque<StatePtr > m_states;
    // container for constant time functions
    unordered_set<StatePtr, StateHasher, StateComparator > m_indexStates;

    int m_max_level_reached;
    List_Type m_type;


public:

    // default and empty constructor
    List(List_Type type);

    // no copy constructor and assignment constructor
    List (const List&) = delete;
    List& operator=(const List&) = delete;

    // ~List();
    bool find(const StatePtr& s) const;
    bool insert(const StatePtr& s);
    bool empty(void) const;
    int size(void) const;
    List_Type getType(void);
    int getMaxDepth(void);
    /*
     * get access front value
     * value is removed from list
     */
    StatePtr acquire(void);
    /* return just a copy
     * of top
     */
    StatePtr top(void);
    int getLevel(void) const;
    // for debug
    const deque<StatePtr>& getStates() const;
    friend ostream& operator<< (ostream &out, const List &l);
};


#endif
