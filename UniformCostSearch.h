#ifndef UNIFORMCOSTSEARCH_H
#define UNIFORMCOSTSEARCH_H
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "problem.h"

using namespace std;

struct Node {
    string state;
    int cost;
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
        void printPath(unordered_map<string, string>& parent, string& goal);
        void printState(const string& state) const;
};

#endif