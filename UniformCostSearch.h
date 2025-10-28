#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H

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

class UniformCostSearch {
    public:
        UniformCostSearch(const Problem& problem);
        bool solve();

    private:
        const Problem& problem;
        int expandedCount;
        int maxQueueSize;
        int goalDepth;

        void printNodeState(const string& state) const;
};

#endif
