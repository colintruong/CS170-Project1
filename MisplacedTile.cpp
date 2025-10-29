#include <MisplacedTile.h>

using namespace std;

MisplacedTileSearch::MisplacedTileSearch(const Problem& p)
    : problem(p), expandedCount(0), maxQueueSize(0), goalDepth(0) {}

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

