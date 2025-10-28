#include "problem.h"

Problem::Problem() {
    initialState = "120453786";
    goalState = "123456780";
}

Problem::Problem(string initial) {
    initialState = initial;
    goalState = "123456780";
}

string Problem::getInitialState() const {
    return initialState;
}

string Problem::getGoalState() const {
    return goalState;
}

void Problem::printState(const string& state) const {
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

vector<string> Problem::getSuccessors(const string& state) const {
    vector<string> successors;
    int pos = state.find('0');
    int x = pos / 3;
    int y = pos % 3;
    for (auto [dx, dy] : moves) {
        int newX = x + dx;
        int newY = y + dy;
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            int newPos = newX * 3 + newY;
            string newState = state;
            swap(newState[pos], newState[newPos]);
            successors.push_back(newState);
        }
    }
    return successors;
}

bool Problem::isGoalState(const string& state) const {
    return state == goalState;
}