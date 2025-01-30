#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::string;
using std::vector;
using std::endl;

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.resize(n);
        for (int i=0; i<n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            return find(parent[x]);
        } else return x;
    }

    void cup(int x, int y) {
        int rx = find(x), ry = find(y);

        if (rx != ry) {
            parent[ry] = rx;
        }

    }
};

int main(int argc, char** argv) {

    return 0;
}
