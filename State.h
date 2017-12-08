// State.h

#ifndef STATE__H
#define STATE__H

/*
 * represents a state
 * and provides the functions required
 */

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>



using std::vector;
using std::ostream;
using std::pair;
using Map = std::map<std::string, int> ;

// differents moves available
enum class Move
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class State
{


private:

    vector<int> m_values;
    int m_level;
    Move m_to_state;
    int m_heuristic_score;
    /* Parent pointer */
    State* parentPtr;
    /* to calculate heuristic score of the state */
    void heuristic_function(void);


public:

    static Map man_distance;
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

    friend ostream& operator<< (ostream &out, const State &s);
};

//
using States_values = vector< pair<Move, vector<int>> >;
States_values generateChildren(const State& father, int &ret);

bool operator== (const State& s1, const State& s2);
bool operator!= (const State& s1, const State& s2);
bool operator> (const State& s1, const State& s2);




#endif
