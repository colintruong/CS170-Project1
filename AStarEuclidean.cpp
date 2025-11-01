#include <iostream>
#include <vector>
#include <cmath>
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

int main(){
    cout << "A* Euclidean Heuristic 8-Puzzle Solver" << endl;
    vector<vector<int>> state = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};
    printPuzzleState(state);
    cout << StateToString2D(state) << endl;
    cout << goalReached(state) << endl;
    pair<int, int> position = findGoalPosition(goalState, 3);
    cout << "( " << position.first << ", " << position.second << " )" << endl;
    double heuristic = euclidean(state);
    cout << heuristic << endl;
    Node nodeTest(state, 3, heuristic);
    cout << nodeTest.cost << " " << nodeTest.heuristic << " " << nodeTest.totalCost() << endl;
    vector<vector<vector<int>>> nxt = nextStates(state);
    for(int i = 0; i<nxt.size(); ++i){
        printPuzzleState(nxt[i]);
    }
    return 0;
}

