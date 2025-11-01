#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

// Some of the helper functions needed to do the AStar search

void printPuzzleState(const vector<vector<int>> &state){
    for(int i =0; i <state.size(); ++i){
        for(int j = 0; j <state[i].size();++j){
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string StateToString2D(const vector<vector<int>> &state){
    string s = "";
    for(int i = 0; i<state.size(); ++i){
        for(int j = 0; j<state[i].size(); j++){
            s = s + to_string(state[i][j]);
        }
    }
    return s;
}

vector<vector<int>> goalState = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};

bool goalReached(const vector<vector<int>> &state){
    return state == goalState;
}

pair<int, int> findGoalPosition(const vector<vector<int>> &state, int val){
    for(int i =0; i < 3; ++i){
        for(int j = 0; j <3; ++j){
            if(state[i][j] == val){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}

double euclidean(const vector<vector<int>> &state){
    double total = 0.0;
    for(int i = 0; i<3; ++i){
        for(int j = 0; j <3; ++j){
            int val = state[i][j];
            if(val != 0){
                pair<int, int> goalPosition = findGoalPosition(goalState, val);
                int row = goalPosition.first;
                int column = goalPosition.second;
                double x2 = i;
                double x1 = row;
                double y2 = j;
                double y1 = column;
                double distance = sqrt(((x2-x1)*(x2-x1)) + ((y2-y1) *(y2-y1)));
                total += distance;
            }
        }
    }
    return total;
}

struct Node{
    vector<vector<int>> state;
    int cost = 0;
    double heuristic = 0.0;
    Node* parent;

    Node(vector<vector<int>> s, int startCost, double heurCost, Node* parent = nullptr) : state(s), cost(startCost), heuristic(heurCost), parent(parent) {}

    double totalCost() const{
        return cost + heuristic;
    }
};

struct Compare{
    bool operator()(const Node* a, const Node* b){
        return (a->totalCost() > b->totalCost());
    }
};

vector<vector<vector<int>>> nextStates(const vector<vector<int>> &state){
    vector<vector<vector<int>>> next;
    int x;
    int y;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(state[i][j] == 0){
                x = i;
                y = j;
            }
        }
    }
    int xDirection[4] = {-1,1,0,0};
    int yDirection[4] = {0,0,-1,1};
    for(int k = 0; k<4; ++k){
        int nextX = x + xDirection[k];
        int nextY = y + yDirection[k];

        if(nextX >= 0 && nextX <3){
            if(nextY>=0 && nextY <3){
                vector<vector<int>> nextState = state;
                swap(nextState[x][y], nextState[nextX][nextY]);
                next.push_back(nextState);
            }
        }
    }
    return next;
}

void aStar(vector<vector<int>> init){
    priority_queue<Node*, vector<Node*>, Compare> q;
    unordered_set<string> exploredSoFar;
    Node* startNode = new Node(init, 0, euclidean(init));
    q.push(startNode);
    int visitedNodes = 0;
    int maxNodesInQueue = 1;
    while(!q.empty()){
        Node* curr = q.top();
        q.pop();
        string s = StateToString2D(curr->state);
        if(exploredSoFar.count(s)){
            continue;
        }
        exploredSoFar.insert(s);
        ++visitedNodes;
        cout << "Start cost g(n) = " << curr->cost << ", Heuristic h(n) = " << curr->heuristic << endl;
        printPuzzleState(curr->state);
        if(goalReached(curr->state)){
            cout << "We have reached the goal. Visited Nodes: " << visitedNodes << " maximum size of queue: " << maxNodesInQueue << ", and the goal's depth is: " << curr->cost << endl;
            return;
        }
        vector<vector<vector<int>>> nxt = nextStates(curr->state);
        for(int i = 0; i < nxt.size(); ++i){
            vector<vector<int>> next = nxt[i];
            string nextString =  StateToString2D(next);
            if(!exploredSoFar.count(nextString)){
                Node* child = new Node(next, curr->cost + 1, euclidean(next), curr);
                q.push(child);
            }
        }
        maxNodesInQueue = max(maxNodesInQueue, (int)q.size());
    }
    cout << "There is no solution :(" << endl;
}

int main(){
    cout << "A* Euclidean Heuristic 8-Puzzle Solver" << endl;
    vector<vector<int>> state = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};
    cout << "Test 1: " << endl;
    aStar(state);
    cout << endl;
    vector<vector<int>> state2 = {{1,2,3},
                                {4,5,6},
                                {7,0,8}
    };
    cout << "Test 2: " << endl;
    aStar(state2);
    cout << endl;
    vector<vector<int>> state3 = {{1,2,3},
                                {4,5,6},
                                {0,7,8}
    }; 
    cout << "Test 3: " << endl;
    aStar(state3);
    cout << endl;
    vector<vector<int>> state4 = {{1,3,6},
                                {5,0,7},
                                {4,8,2}
    };
    cout << "Test 4: " << endl;
    aStar(state4);
    cout << endl;
    vector<vector<int>> state5 = {{8,6,7},
                                {2,5,4},
                                {3,0,1}
    };
    cout << "Test 5: " << endl;
    aStar(state5);
    cout << endl;
    vector<vector<int>> state6 = {{1,2,3},
                                {4,5,6},
                                {8,7,0}
    };
    cout << "Test 6: " << endl;
    aStar(state6);
    cout << endl;
    
    // Test Cases for helper functions:
    // cout << "Test 1: " << endl;
    // vector<vector<int>> state = {{1,2,3},
    //                              {4,5,6},
    //                              {7,8,0}};
    // printPuzzleState(state);
    // cout << StateToString2D(state) << endl;
    // cout << goalReached(state) << endl;
    // pair<int, int> position = findGoalPosition(goalState, 3);
    // cout << "( " << position.first << ", " << position.second << " )" << endl;
    // double heuristic = euclidean(state);
    // cout << heuristic << endl;
    // Node nodeTest(state, 3, heuristic);
    // cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    // vector<vector<vector<int>>> nxt = nextStates(state);
    // for(int i = 0; i<nxt.size(); ++i){
    //     printPuzzleState(nxt[i]);
    // }

    // cout << "Test 2: " << endl;
    // vector<vector<int>> state2 = {{1,2,3},
    //                             {4,5,6},
    //                             {7,0,8}
    // };
    // printPuzzleState(state2);
    // cout << StateToString2D(state2) << endl;
    // cout << goalReached(state2) << endl;
    // position = findGoalPosition(goalState, 3);
    // cout << "( " << position.first << ", " << position.second << " )" << endl;
    // heuristic = euclidean(state2);
    // cout << heuristic << endl;
    // Node nodeTest2(state2, 3, heuristic);
    // cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    // nxt = nextStates(state2);
    // for(int i = 0; i<nxt.size(); ++i){
    //     printPuzzleState(nxt[i]);
    // }

    // cout << "Test 3: " << endl;
    // vector<vector<int>> state3 = {{1,2,3},
    //                             {4,5,6},
    //                             {0,7,8}
    // };
    // printPuzzleState(state3);
    // cout << StateToString2D(state3) << endl;
    // cout << goalReached(state3) << endl;
    // position = findGoalPosition(goalState, 3);
    // cout << "( " << position.first << ", " << position.second << " )" << endl;
    // heuristic = euclidean(state3);
    // cout << heuristic << endl;
    // Node nodeTest3(state3, 3, heuristic);
    // cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    // nxt = nextStates(state3);
    // for(int i = 0; i<nxt.size(); ++i){
    //     printPuzzleState(nxt[i]);
    // }

    // cout << "Test 4: " << endl;
    // vector<vector<int>> state4 = {{1,3,6},
    //                             {5,0,7},
    //                             {4,8,2}
    // };
    // printPuzzleState(state4);
    // cout << StateToString2D(state4) << endl;
    // cout << goalReached(state4) << endl;
    // position = findGoalPosition(goalState, 3);
    // cout << "( " << position.first << ", " << position.second << " )" << endl;
    // heuristic = euclidean(state4);
    // cout << heuristic << endl;
    // Node nodeTest4(state4, 3, heuristic);
    // cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    // nxt = nextStates(state4);
    // for(int i = 0; i<nxt.size(); ++i){
    //     printPuzzleState(nxt[i]);
    // }

    // cout << "Test 5: " << endl;
    // vector<vector<int>> state5 = {{8,6,7},
    //                             {2,5,4},
    //                             {3,0,1}
    // };
    // printPuzzleState(state5);
    // cout << StateToString2D(state5) << endl;
    // cout << goalReached(state5) << endl;
    // position = findGoalPosition(goalState, 3);
    // cout << "( " << position.first << ", " << position.second << " )" << endl;
    // heuristic = euclidean(state5);
    // cout << heuristic << endl;
    // Node nodeTest5(state5, 3, heuristic);
    // cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    // nxt = nextStates(state5);
    // for(int i = 0; i<nxt.size(); ++i){
    //     printPuzzleState(nxt[i]);
    // }

    // cout << "Test 6: " << endl;
    // vector<vector<int>> state6 = {{1,2,3},
    //                             {4,5,6},
    //                             {8,7,0}
    // };
    // printPuzzleState(state6);
    // cout << StateToString2D(state6) << endl;
    // cout << goalReached(state6) << endl;
    // position = findGoalPosition(goalState, 3);
    // cout << "( " << position.first << ", " << position.second << " )" << endl;
    // heuristic = euclidean(state6);
    // cout << heuristic << endl;
    // Node nodeTest6(state6, 3, heuristic);
    // cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    // nxt = nextStates(state6);
    // for(int i = 0; i<nxt.size(); ++i){
    //     printPuzzleState(nxt[i]);
    // }

    return 0;
}