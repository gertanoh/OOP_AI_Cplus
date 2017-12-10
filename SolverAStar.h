// SolverAStar.hh

#ifndef SOLVER_A_START__H
#define SOLVER_A_START__H


/*
 * Solver for 8 puzzle game
 * Uses classes List and State and Fringe to do so
 * using A star algorithm with manhattan distance
 */

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <queue>
#include "List.h"
#include "State.h"
#include "Fringe.h"
#include "utils.h"


using std::priority_queue;
using std::unordered_multiset;
