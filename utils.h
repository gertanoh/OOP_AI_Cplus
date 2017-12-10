// utils.h

#ifndef UTILS__H
#define UTILS__H

/*
 * contains all enum class
 * aliases
 * custom hashers and comparators
 */


// forward declaration for pointer 
class State;

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <utility>


using std::vector;
using std::pair;


// differents moves available
enum class Move
{
 UP,
 DOWN,
 LEFT,
 RIGHT
};

// two goals available
enum class Goal
{
 STANDARD_GOAL = 0,
 NON_STANDARD_GOAL,
};

enum class List_Type
{
  STACK,
  QUEUE
};


using Map = std::map<std::string, int> ;
using States_values = vector< pair<Move, vector<int>> >;
using StatePtr = std::shared_ptr<State>;



#endif
