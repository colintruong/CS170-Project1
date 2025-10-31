#ifndef MISPLACED_TILE_H
#define MISPLACED_TILE_H

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "problem.h"

using namespace std;

struct Node {
    string state;
    int cost;
    int depth;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

class MisplacedTileSearch {
    public:
        MisplacedTileSearch(const Problem& problem);
        bool solve();
        int g(const string& state, const string& start, const unordered_map<string, string>& parent);
        int h(const string& state);
        vector<string> legalStates(const string& state);
        vector<string> aStar(const string& state);

    private:
        const Problem& problem;

        void printNodeState(const string& state) const;
};

#endif