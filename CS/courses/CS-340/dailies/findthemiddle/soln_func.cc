#include <iostream>
#include <vector>
using std::vector;

template <typename T>
using matrix = vector<vector<int>>;

void sortMatrix(matrix<int>& vecs) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i=0; i<(int) vecs.size() - 1; ++i) {
            if (vecs[i] > vecs[i+1]) {
                vecs[i].swap(vecs[i+1]);
                swapped = true;
            }
        }
    }
}

int findmiddle(vector<vector<int>> &vecs, int &p) {

    int size = 0;

    // Get the sum of the sizes
    for (const auto& item : vecs) {
        size += (int) item.size();
    }

    // If the size is even, return 0
    if (size % 2 == 0) 
        return 0;

    // Sort
    sortMatrix(vecs);

    // Else, find which which vector and which element has the middle value
    int vidx = 0, count=0, mid=size/2;
    for (int i=0; i<=mid; ++i, ++count) {
        while (vidx < (int)vecs.size() && vecs[vidx].empty()) {
            ++vidx;
        }

        if (count >= (int) (vecs[vidx].size())) {
            ++vidx;
            count=0;
        }
    }
    --count;

    // Get the middle value we found
    p = vecs[vidx][count];

    // Return success
    return 1;
}
