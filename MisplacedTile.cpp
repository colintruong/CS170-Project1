#include <MisplacedTile.h>
#include <queue>
#include <vector>
#include <string>

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
    const string goalState = "123456780";
    string startState = problem.getInitialState();

    struct SearchNode {
        int f;            // f = g + h
        string state;     // encoded board
        bool operator>(const SearchNode& o) const { return f > o.f; }
    };

    // Min-heap by f
    priority_queue<SearchNode, vector<SearchNode>, greater<SearchNode>> open;

    unordered_map<string, string> parent;  // child -> parent
    unordered_set<string> closed;          // expanded states

    // push start
    open.push({ h(startState) /* f = 0 + h */, startState });

    while (!open.empty()) {
        SearchNode cur = open.top();
        open.pop();

        if (closed.count(cur.state)) continue;  // skip stale
        closed.insert(cur.state);

        // Goal check
        if (cur.state == goalState) {
            // Reconstruct path
            vector<string> path;
            string s = cur.state;
            while (true) {
                path.push_back(s);
                auto it = parent.find(s);
                if (it == parent.end()) break;
                s = it->second;
            }
            reverse(path.begin(), path.end());

            // Print result
            cout << "Solution in " << (int)path.size() - 1 << " moves:\n";
            for (const auto& st : path) {
                printNodeState(st);
                cout << "-----\n";
            }
            return true;
        }

        // Expand neighbors
        for (const string& nb : legalStates(cur.state)) {
            if (closed.count(nb)) continue;

            // tentative g = depth(parent-walk of current) + 1
            int tentative_g = g(cur.state, startState, parent) + 1;
            int nb_old_g = g(nb, startState, parent);

            // Set/Improve parent if this path is better
            if (parent.find(nb) == parent.end() || tentative_g < nb_old_g) {
                parent[nb] = cur.state;
            }

            int f = tentative_g + h(nb);
            open.push({ f, nb });
        }
    }

    cout << "No solution found.\n";
    return false;
}


