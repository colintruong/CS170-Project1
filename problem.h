#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Problem {
    public:
        Problem();
        Problem(string initial, string goal);
        string getInitialState() const;
        string getGoalState() const;
        vector<string> getSuccessors(const string& state) const;
        bool isGoalState(const string& state) const;
    private:
        string initialState;
        string goalState;
        const vector<pair<int, int>> moves = {
            {-1, 0}, // up
            {1, 0},  // down
            {0, -1}, // left
            {0, 1}   // right
        };
        
};

#endif