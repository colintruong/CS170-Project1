#include <MisplacedTile.h>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


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

int MisplacedTileSearch::g(const string& state, const string& start, const unordered_map<string, string>& parent) {
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
    const string goal = "123456780";
    string start = problem.getInitialState();

    struct Node {
        int f, g, h;
        string state;
        bool operator>(const Node& other) const { return f > other.f; }
    };

    priority_queue<Node, vector<Node>, greater<Node>> open;
    unordered_set<string> closed;
    unordered_map<string, string> parent;

    int expandedCount = 0;
    int maxQueueSize = 0;
    int goalDepth = 0;

    // initial node
    int hStart = h(start);
    open.push({hStart, 0, hStart, start});

    cout << "Expanding state" << endl;
    printNodeState(start);
    cout << endl;

    while (!open.empty()) {
        Node cur = open.top();
        open.pop();

        if (closed.count(cur.state)) continue;
        closed.insert(cur.state);

        if (cur.state == goal) {
            cout << "Goal!!!" << endl;
            cout << "To solve this problem the search algorithm expanded a total of "
                 << expandedCount << " nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time: "
                 << maxQueueSize << "." << endl;
            cout << "The depth of the goal node was " << cur.g << "." << endl;
            return true;
        }

        expandedCount++;

        vector<string> children = legalStates(cur.state);
        for (const string& child : children) {
            if (closed.count(child)) continue;

            parent[child] = cur.state;
            int gCost = cur.g + 1;
            int hCost = h(child);
            int fCost = gCost + hCost;

            open.push({fCost, gCost, hCost, child});

            if ((int)open.size() > maxQueueSize)
                maxQueueSize = open.size();
        }

        if (!open.empty()) {
            Node next = open.top();
            cout << "The best state to expand with g(n) = " << next.g
                 << " and h(n) = " << next.h << " is..." << endl;
            printNodeState(next.state);
            cout << "Expanding this node..." << endl;
        }
    }

    cout << "No solution found." << endl;
    return false;
}


