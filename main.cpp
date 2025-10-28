#include <iostream>
#include "problem.h"
#include "UniformCostSearch.h"

using namespace std;

int main() {
    cout << "Welcome to 8-Puzzle Solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    int choice;
    cin >> choice;
    string initialState;
    if (choice == 1) {
        initialState = "123480765";
    } else {
        vector<vector<int>> userInput(3, vector<int>(3));
        cout << "Enter your puzzle, use a zero to represent the blank space." << endl;
        cout << "Enter the first row, use space or tabs between numbers: ";
        for (int i = 0; i < 3; i++) {
            cin >> userInput[0][i];
        }
        cout << "Enter the second row, use space or tabs between numbers: ";
        for (int i = 0; i < 3; i++) {
            cin >> userInput[1][i];
        }
        cout << "Enter the third row, use space or tabs between numbers: ";
        for (int i = 0; i < 3; i++) {
            cin >> userInput[2][i];
        }
        for (const auto& row : userInput) {
            for (const auto& num : row) {
                initialState += to_string(num);
            }
        }
    }
    Problem problem(initialState);

    cout << "Expanding state" << endl;
    problem.printState(problem.getInitialState());
    cout << endl;

    UniformCostSearch UCS(problem);
    UCS.solve();
    return 0;
}