#include <iostream>
#include <vector>
using namespace std;

void printPuzzleState(const vector<vector<int>> &state){
    for(int i =0; i <state.size(); ++i){
        for(int j = 0; j <state[i].size();++j){
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    cout << "A* Euclidean Heuristic 8-Puzzle Solver" << endl;
    vector<vector<int>> state = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};
    printPuzzleState(state);
}

