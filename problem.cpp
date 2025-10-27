#include "problem.h"

Problem::Problem() {}

Problem::Problem(string initial, string goal) : initialState(initial), goalState(goal) {}

string Problem::getInitialState() const {
    return initialState;
}

string Problem::getGoalState() const {
    return goalState;
}

