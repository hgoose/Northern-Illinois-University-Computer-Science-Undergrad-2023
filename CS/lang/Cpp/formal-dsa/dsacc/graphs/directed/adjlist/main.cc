#include <iostream>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <vector>
using std::cout;
using std::vector;
using std::endl;
using std::unordered_map;
using std::unordered_set;
using std::stack;

struct graph {
    unordered_map<int, vector<int>> list;

    void addEdge(int v, int u) {
        list[v].push_back(u);
    }

    void topologicalSort() {
        unordered_set<int> visited; // Set to keep track of visited nodes
        stack<int> s;               // Stack to store the topological order

        // Visit each node that hasn't been visited yet
        for (const auto& [node, _] : list) {
            if (visited.find(node) == visited.end()) {
                dfs(node, visited, s);
            }
        }

        // Print the nodes in topological order
        cout << "Topological Sort: ";
        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    }

    // Helper function for DFS
    void dfs(int node, unordered_set<int>& visited, stack<int>& s) {
        visited.insert(node); // Mark the current node as visited

        // Visit all the neighbors
        for (int neighbor : list[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, visited, s);
            }
        }

        // Push the current node onto the stack after visiting all its neighbors
        s.push(node);
    }
    void display() {
        for (const auto& [key, value] : list) {
            cout << key << ": ";
            for (const auto& item : value) {
                cout << item << " ";
            }
            cout << endl;
        }
    }

};

int main(int argc, char** argv) {

    graph g;
    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(2,3);

    g.topologicalSort();

    return 0;
}
