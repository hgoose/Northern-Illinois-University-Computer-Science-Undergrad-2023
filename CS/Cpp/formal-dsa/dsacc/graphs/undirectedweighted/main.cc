#include <iostream>
#include <sys/types.h>
#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
using std::cout;
using std::vector;
using std::endl;
using std::unordered_map;
using std::priority_queue;
using std::queue;

const int INF = std::numeric_limits<int>::max();

struct graph {
    int n = 0;
    vector<vector<int>> matrix;

    graph() = default;
    graph(int n) : n(n) {
        matrix = vector<vector<int>>(n, vector<int>(n,0));
    }

    void addEdge(int v, int u, int weight) {
        if (v >=0 && v < n && u >= 0 && u < n) {
            matrix[v][u] = weight;
            matrix[u][v] = weight;
        }
    }

    void removeEdge(int v, int u) {
        if (v >=0 && v < n && u >= 0 && u < n) {
            matrix[v][u] = 0;
            matrix[u][v] = 0;
        }
    }

    void dijkstra(int start) {
        priority_queue<std::pair<int,int>, vector<std::pair<int,int>>, std::greater<>> pq;
        vector<int> dist(n, INF);
        vector<int> parent(n,-1);
        dist[start] = 0;
         
        pq.emplace(0,start);

        while (!pq.empty()) {
            auto [d,u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (int v = 0; v<n; ++v) {
                if (matrix[u][v] > 0) {
                    int weight = matrix[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.emplace(dist[v], v);
                        parent[v] = u;
                    }
                }
            }
        }
        for (int i=0; i<n; ++i) {
            if (dist[i] == INF) {
                cout << "Distance " << start << " -> " << i << ": " << "not reachable" << endl;
            } else {
                cout << "Distance " << start << " -> " << i << ": " << dist[i] << endl;
                cout << "Path: ";
                vector<int> path;
                for (int v = i; v != -1; v = parent[v]) {
                    path.push_back(v);
                }
                std::reverse(path.begin(), path.end());

                for (const auto& item : path) {
                    cout << item << " -> ";
                }
                cout << endl << endl;
            }
        }
    }

    void display() {
        for (const auto& row : matrix) {
            for (const auto& entry : row) {
                cout << entry << " ";
            }
            cout << endl;
        }
    }
};


int main(int argc, char** argv) {

    graph  g(6);
    g.addEdge(0,1,2);
    g.addEdge(1,2,1);
    g.addEdge(2,3,3);
    g.addEdge(3,4,2);
    g.addEdge(0,4,9);
    g.addEdge(4,5,1);
    g.addEdge(5,1,2);

    g.display();
    cout << endl << endl;

    g.dijkstra(0);



   return 0;
}
