#include "UniformCostSearch.h"

UniformCostSearch::UniformCostSearch(const Problem& problem) : problem(problem) {}

bool UniformCostSearch::solve() {
    string initialState = problem.getInitialState();
    string goalState = problem.getGoalState();
    priority_queue<Node, vector<Node>, greater<int>> frontier;
    unordered_set<string> visited;
    unordered_map<string, string> parent;
    frontier.push({initialState, 0});

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();
        if (visited.count(current.state)) {
            continue;
        }
        visited.insert(current.state);
        if (problem.isGoalState(current.state)) {
            cout << "Reached goal state with cost " << current.cost << endl;
            printPath(parent, current.state);
            return true;
        }

        for (auto& next : problem.getSuccessors(current.state)) {
            if (!visited.count(next)) {
                parent[next] = current.state;
                frontier.push({next, current.cost + 1});
            }
        }
    }
    cout << "No solution found." << endl;
    return false;
}

void UniformCostSearch::printPath(unordered_map<string, string>& parent, string& goal) {
    vector<string> path;
    string currState = goal;
    while (parent.find(currState) != parent.end()) {
        path.push_back(currState);
        currState = parent[currState];
    }

    reverse(path.begin(), path.end());

    for (const string& state : path) {
        printState(state);
        cout << "--------" << endl;
    }
}

void UniformCostSearch::printState(const string& state) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i * 3 + j] == '0') {
                cout << "b ";
            } else {
                cout << state[i * 3 + j] << " ";
            }
        }
        cout << endl;
    }
}