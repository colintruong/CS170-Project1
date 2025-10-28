#include "UniformCostSearch.h"
#include <queue>
#include <iostream>

UniformCostSearch::UniformCostSearch(const Problem& p)
    : problem(p), expandedCount(0), maxQueueSize(0), goalDepth(0) {}

void UniformCostSearch::printNodeState(const string& state) const {
    for (int i = 0; i < 9; i++) {
        if (state[i] == '0')
            cout << "b ";
        else
            cout << state[i] << " ";
        if (i % 3 == 2)
            cout << endl;
    }
}

bool UniformCostSearch::solve() {
    auto cmp = [](const Node& a, const Node& b) { return a.cost > b.cost; };
    priority_queue<Node, vector<Node>, decltype(cmp)> frontier(cmp);

    unordered_set<string> visited;
    unordered_map<string, string> parent; // for reconstructing path

    frontier.push({problem.getInitialState(), 0, 0});
    visited.insert(problem.getInitialState());

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        cout << "The best state to expand with g(n) = " << current.cost << endl;
        printNodeState(current.state);
        cout << "Expanding this node..." << endl << endl;

        expandedCount++;

        if (current.state == problem.getGoalState()) {
            goalDepth = current.depth;
            cout << "Goal!!!" << endl;
            cout << "To solve this problem the search algorithm expanded a total of "
                 << expandedCount << " nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time: "
                 << maxQueueSize << "." << endl;
            cout << "The depth of the goal node was " << goalDepth << "." << endl;
            return true;
        }

        vector<string> successors = problem.getSuccessors(current.state);

        for (const string& next : successors) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                frontier.push({next, current.cost + 1, current.depth + 1});
            }
        }

        if (frontier.size() > (size_t)maxQueueSize)
            maxQueueSize = frontier.size();
    }

    cout << "No solution found." << endl;
    return false;
}
