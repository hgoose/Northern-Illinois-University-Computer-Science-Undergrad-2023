#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::pair;

typedef pair<int,int> Vpair;

struct graph {
    int V, E;
    vector<pair<int,Vpair>> edges;

    graph(int v, int e) : V(v), E(e) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u,v}});
    }
};

int main(int argc, char** argv) {

    return 0;
}
