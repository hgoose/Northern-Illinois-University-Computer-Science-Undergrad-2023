#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

const int INF = numeric_limits<int>::max(); // Define infinity

// Dijkstra's algorithm function
void dijkstra(int source, const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size(); // Number of nodes in the graph
    vector<int> dist(n, INF); // Distance array initialized to infinity
    vector<bool> visited(n, false); // Visited array

    // Min-heap to store (distance, node) pairs
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Initialize the source node
    dist[source] = 0;
    pq.push({0, source}); // Push the source with distance 0

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (visited[currentNode]) continue; // Skip already visited nodes
        visited[currentNode] = true;

        // Explore all neighbors
        for (const auto& [neighbor, weight] : graph[currentNode]) {
            int newDist = currentDist + weight;

            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist; // Update distance
                pq.push({newDist, neighbor}); // Push neighbor into the heap
            }
        }
    }

    // Print the shortest distances
    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << "Node " << i << ": Unreachable\n";
        } else {
            cout << "Node " << i << ": " << dist[i] << "\n";
        }
    }
}

// Main function
int main() {
    // Hardcoded graph
    int n = 5; // Number of nodes
    vector<vector<pair<int, int>>> graph(n); // Adjacency list (node, weight)

    // Add edges (u -> v with weight w)
    graph[0].emplace_back(1, 1); // Edge 0 -> 1 with weight 1
    graph[0].emplace_back(2, 4); // Edge 0 -> 2 with weight 4
    graph[1].emplace_back(2, 2); // Edge 1 -> 2 with weight 2
    graph[1].emplace_back(3, 6); // Edge 1 -> 3 with weight 6
    graph[2].emplace_back(3, 3); // Edge 2 -> 3 with weight 3
    graph[3].emplace_back(4, 1); // Edge 3 -> 4 with weight 1

    int source = 0; // Hardcoded source node

    // Run Dijkstra's algorithm
    dijkstra(source, graph);

    return 0;
}
