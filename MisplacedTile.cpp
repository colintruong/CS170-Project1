#include <MisplacedTile.h>

using namespace std;

MisplacedTileSearch::MisplacedTileSearch(const Problem& p)
    : problem(p) {}

void MisplacedTileSearch::printNodeState(const string& state) const {
    for (int i = 0; i < 9; i++) {
        if (state[i] == '0')
            cout << "b ";
        else
            cout << state[i] << " ";
        if (i % 3 == 2)
            cout << endl;
    }
}

int MisplacedTileSearch::h(const string& state) {
    string goalState = "123456780";
    int count = 0;
    for (int i = 0; i < state.size(); i ++) {
        if (state[i] != goalState[i]) {
            count++;
        }
    }
    return count;
}

int g(const string& state, const string& start, const unordered_map<string, string>& parent) {
    int cost = 0;
    string s = state;
    while (s != start) {
        auto i = parent.find(s);
        if (i == parent.end()) break; //no parent, ie; start state
        s = i->second;
        cost++;
    }
    return cost;
}

vector<string> MisplacedTileSearch::legalStates(const string& state) {
    vector<string> returnStates;
    int a = state.find('0');
    if (a == 0) {
        string t = state;
        t[0] = state[1];
        t[1] = '0';
        returnStates.push_back(t);

        t = state;
        t[0] = state[3];
        t[3] = '0';
        returnStates.push_back(t);
    }

    if (a == 1) {
        string t = state;
        t[1] = state[0];
        t[0] = '0';
        returnStates.push_back(t);

        t = state;
        t[1] = state[2];
        t[2] = '0';
        returnStates.push_back(t);

        t = state;
        t[1] = state[4];
        t[4] = '0';
        returnStates.push_back(t);
    }

    if (a == 2) {
        string t = state;
        t[2] = state[1];
        t[1] = '0';
        returnStates.push_back(t);

        t = state;
        t[2] = state[5];
        t[5] = '0';
        returnStates.push_back(t);
    }

    if (a == 3) {
        string t = state;
        t[3] = state[0];
        t[0] = '0';
        returnStates.push_back(t);

        t = state;
        t[3] = state[4];
        t[4] = '0';
        returnStates.push_back(t);

        t = state;
        t[3] = state[6];
        t[6] = '0';
        returnStates.push_back(t);
    }

    if (a == 4) {
        string t = state;
        t[4] = state[1];
        t[1] = '0';
        returnStates.push_back(t);

        t = state;
        t[4] = state[3];
        t[3] = '0';
        returnStates.push_back(t);

        t = state;
        t[4] = state[5];
        t[5] = '0';
        returnStates.push_back(t);

        t = state;
        t[4] = state[7];
        t[7] = '0';
        returnStates.push_back(t);
    }

    if (a == 5) {
        string t = state;
        t[5] = state[2];
        t[2] = '0';
        returnStates.push_back(t);

        t = state;
        t[5] = state[4];
        t[4] = '0';
        returnStates.push_back(t);

        t = state;
        t[5] = state[8];
        t[8] = '0';
        returnStates.push_back(t);
    }

    if (a == 6) {
        string t = state;
        t[6] = state[3];
        t[3] = '0';
        returnStates.push_back(t);

        t = state;
        t[6] = state[7];
        t[7] = '0';
        returnStates.push_back(t);
    }

    if (a == 7) {
        string t = state;
        t[7] = state[4];
        t[4] = '0';
        returnStates.push_back(t);

        t = state;
        t[7] = state[6];
        t[6] = '0';
        returnStates.push_back(t);

        t = state;
        t[7] = state[8];
        t[8] = '0';
        returnStates.push_back(t);
    }

    if (a == 8) {
        string t = state;
        t[8] = state[5];
        t[5] = '0';
        returnStates.push_back(t);

        t = state;
        t[8] = state[7];
        t[7] = '0';
        returnStates.push_back(t);
    }

    return returnStates;
}

bool MisplacedTileSearch::solve() {

}

