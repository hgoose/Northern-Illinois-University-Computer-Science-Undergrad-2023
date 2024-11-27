#include <iostream>
#include <vector>
#include <queue>
using std::cout;
using std::vector;
using std::endl;
using std::queue;

struct graph {
    vector<vector<int>> matrix;
    int numVertices{0};

    graph(int n) : numVertices(n) {
        matrix.resize(n, vector<int>(n,0));
    }

    void addEdge(int v1, int v2) {
        if (v1 >=0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
            matrix[v1][v2] = 1;
            matrix[v2][v1] = 1;
        } 
    }
    void removeEdge(int v1, int v2) {
        if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
            matrix[v1][v2] = 0; 
            matrix[v2][v1] = 0;
        } 
    }

    vector<int> getNeighbors(int v) {
        vector<int> ret{};
        int row = v; 
        for (int j=0; j<numVertices; ++j) {
            if (matrix[row][j]) ret.push_back(j);
        }
        return ret;
    }

    bool hasEdge(int v1, int v2) {
        if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
            return matrix[v1][v2] == 1;
        } 
        return false;
    }

    // Display the adjacency matrix
    void display() {
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void bft(int start) {
        if (start < 0 || start >= numVertices) {
            cout << "Starting point does not exist" << endl;
            return;
        }
        vector<bool> visited(numVertices,0);
        queue<int> q;
        q.push(start);
        visited[start] = 1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            int i = curr;
            for (int j=0; j<numVertices; ++j) {
                if (matrix[i][j] && !visited[j]) {
                    q.push(j);
                    visited[j] = 1;
                }
            }
        }
    }

    void r_dft(int v, vector<bool>& visited) {
        cout << v << " ";

        int i=v;
        for (int j=0; j<numVertices; ++j) {
            if (matrix[i][j] && !visited[j]) {
                visited[j] = 1;
                r_dft(j, visited);
            }
        }
    }

    void dft(int start) {
        if (start < 0 || start >= numVertices) {
            return;
        }
        vector<bool> visited(numVertices,0);
        visited[start] = 1;
        r_dft(start, visited);
    }
};

int main(int argc, char** argv) {

    graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(0,4);
    g.bft(0);

    // vector<int> v = g.getNeighbors(0);
    // for (const auto& item : v) {
    //     cout << item << " ";
    // }
    // cout << endl;



    return 0;
}
