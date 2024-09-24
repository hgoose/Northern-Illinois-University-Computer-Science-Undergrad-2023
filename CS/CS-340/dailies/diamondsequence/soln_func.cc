#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

vector<int> diamondsequence(vector<vector<int>> &m) {

    vector<int> seq;
    int n = m.size();

    // Make sure N is odd
    if ((int) n % 2 == 0) return seq;

    // Make sure m is square
    for (const auto& item : m) {
        if ((int) item.size() != n) {
            return seq;
        }
    }

    // Go down and right
    int i=0, j=n/2;
    for (; j<n; ++j, ++i) {
        seq.push_back(m[i][j]);
    }
    --i, --j; // Undo last increment

    // Go down and left
    ++i, --j; // Get the the next start position
    for (; i<n; ++i, --j) {
        seq.push_back(m[i][j]);
    }
    --i, ++j; // Undo last increment

    // Go up and left
    --i, --j; // Get the the next start position
    for (; j>=0; --i, --j) {
        seq.push_back(m[i][j]);
    }
    ++i, ++j; // Undo last increment

    // Go up and right
    --i, ++j; // Get the the next start position
    for (; i>0; --i, ++j) {
        seq.push_back(m[i][j]);
    }

    // Done
    return seq;
}
