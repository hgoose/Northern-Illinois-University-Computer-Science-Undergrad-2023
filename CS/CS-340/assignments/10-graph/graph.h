//***************************************************************************
//
//  graph.h 
//  CSCI 340 Assignment 10 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************
#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

#include "graph.decl.h"
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>
#include <functional>
using std::for_each;
using std::queue;
using std::stack;

/**
 * Returns the number of vertices in the graph.
 *
 * @return size_t: Number of vertices.
 */
size_t Graph::nvertices() const {
    // Return the size of the vertex vector
    return vertices.size();
}

/**
 * Returns the number of edges in the graph.
 *
 * @return size_t: Number of edges.
 */
size_t Graph::nedges() const { 
    // Return the size of the edge vector
    return edges.size();
}

/**
 * Assigns vertices and edges to the graph, clearing any previous data.
 *
 * @param vertices: Vector of vertex labels.
 * @param edges: Vector of edges connecting the vertices.
 */
void Graph::assign(const std::vector<std::string>& vertices, const std::vector<GraphEdge>& edges) {
    // Clear stuff
    this->vertices.clear();
    this->edges.clear();
    this->v_lut.clear();

    // Add vertices
    for (size_t i = 0; i < vertices.size(); ++i) {
        this->vertices.push_back(vertices[i]);
        this->v_lut[vertices[i]] = i;
    }

    // Add edges
    for (const auto& edge : edges) {
        this->edges.push_back(edge);
    }
}

/**
 * Checks if an edge exists between two vertices.
 *
 * @param origin: Index of the origin vertex.
 * @param destination: Index of the destination vertex.
 * @return bool: True if the edge exists, false otherwise.
 */
bool Graph::edge_exists(size_t origin, size_t destination) const {
    // Assume false
    bool ret = false;
    // Loop through the edge vector
    for_each(edges.begin(), edges.end(),  [&](GraphEdge e) {
        // If match is found, update ret
        if (e.origin == origin && e.destination == destination) {
            ret = true;
        }
    });
    return ret;
}

/**
 * Retrieves the weight of the edge between two vertices.
 *
 * @param origin: Index of the origin vertex.
 * @param destination: Index of the destination vertex.
 * @return double: Weight of the edge, or infinity if no edge exists.
 */
double Graph::edge_weight(size_t origin, size_t destination) const {
    // Assume infinity
    double weight = INFINITY; 
    // Loop through the edges
    for_each(edges.begin(), edges.end(),  [&](GraphEdge e) {
        // If match is found, grab weight
        if (e.origin == origin && e.destination == destination) {
            weight = e.weight;
        }
    });
    // Return weight
    return weight;
}


/**
 * Returns the undirected adjacency list for a vertex.
 *
 * @param vertex: Index of the vertex.
 * @return std::vector<AdjListEdge>: Vector of adjacent vertices with edge weights.
 */
std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
    // return vector
    std::vector<AdjListEdge> al;
    // Loop through the edges
    for_each(edges.begin(), edges.end(),  [&](GraphEdge e) {
        // IF match is found
        if (e.origin == vertex || e.destination == vertex) {
            // Make the edge, fill members
            AdjListEdge edge;
            edge.vertex = (e.origin == vertex ? e.destination : e.origin);
            edge.weight = e.weight;
            // Push into vector
            al.push_back(edge);
        }
    });
    // Return built vector
    return al;
}

/**
 * Returns the in-adjacency list for a vertex (incoming edges).
 *
 * @param vertex: Index of the vertex.
 * @return std::vector<AdjListEdge>: Vector of incoming edges with weights.
 */
std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
    // return vector
    std::vector<AdjListEdge> al;
    // Loop through the edges
    for_each(edges.begin(), edges.end(),  [&](GraphEdge e) {
        // Find match
        if (e.destination == vertex) {
            // Make edge, fill members
            AdjListEdge edge;
            edge.vertex = e.origin;
            edge.weight = e.weight;
            // Push to vector
            al.push_back(edge);
        }
    });
    return al;
}


/**
 * Returns the out-adjacency list for a vertex (outgoing edges).
 *
 * @param vertex: Index of the vertex.
 * @return std::vector<AdjListEdge>: Vector of outgoing edges with weights.
 */
std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
    // Same idea as above
    std::vector<AdjListEdge> al;
    for_each(edges.begin(), edges.end(),  [&](GraphEdge e) {
        if (e.origin == vertex) {
            AdjListEdge edge;
            edge.vertex = e.destination;
            edge.weight = e.weight;
            al.push_back(edge);
        }
    });
    return al;
}

/**
 * Generates a weighted adjacency matrix for the graph.
 *
 * @return std::vector<double>: Row-major weighted adjacency matrix.
 */
std::vector <double> Graph::weighted_adjacency_matrix() const {
    // Get number of vertices
    size_t n = nvertices(); 
    // Init row major matrix with infinity
    std::vector<double> m(n*n,INFINITY);
    // Loop through edges, overwrite entry in matrix
    for_each(edges.begin(), edges.end(), [&](GraphEdge e) {
       m[e.origin * n + e.destination] = e.weight; 
    });
    // Return matrix
    return m;
}


/**
 * Generates an unweighted adjacency matrix for the graph.
 *
 * @return std::vector<bool>: Row-major unweighted adjacency matrix.
 */
std::vector <bool> Graph::unweighted_adjacency_matrix() const {
    // Get number of vertices
    size_t n = nvertices(); 
    // init matrix
    std::vector<bool> m(n*n,0);
    // For each edge, 
    for_each(edges.begin(), edges.end(), [&](GraphEdge e) {
    // Update matrix if edge exists
       m[e.origin * n + e.destination] = 1;
    });
    // Return matrix
    return m;
}

/**
 * Returns the label of a vertex.
 *
 * @param vertex: Index of the vertex.
 * @return std::string: Label of the vertex.
 */
std::string Graph::v_label(size_t vertex) const {
    // Return vertex from vertices vector
    return vertices[vertex];
}


/**
 * Finds the index of a vertex given its label.
 *
 * @param label: Label of the vertex.
 * @return ssize_t: Index of the vertex, or -1 if not found.
 */
ssize_t Graph::v_index(const std::string &label) const {
    // Find label in vertex vector, return index
    for (int i=0; i<(int)vertices.size(); ++i) {
        if (vertices[i] == label ) {
            return (size_t) i;
        }
    }
    // Does not exist
    return -1;
}

/**
 * Performs a depth-first traversal (DFT) of the graph starting from a given vertex.
 *
 * @tparam FN: Callable function type to process each vertex.
 * @param start: Index of the starting vertex.
 * @param visitfn: A callable function applied to each visited vertex.
 * @param connected_only: If true, only traverses vertices reachable from the start.
 */
template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
    // Track visited
    std::vector<bool> visited(nvertices(), false);
    // Make queue
    queue<size_t> q;

    // Lambda function to search starting from vertex start_vertex
    auto process_vertex = [&](size_t start_vertex) {
        // Set start visited
        visited[start_vertex] = true;
        // Push start to queue
        q.push(start_vertex);

        // While q not empty
        while (!q.empty()) {
            // Get and pop front of queue
            size_t curr = q.front();
            q.pop();
            // Visit node
            visitfn(curr);
            // Get vector of Adjacent edges and vertices
            std::vector<AdjListEdge> nb = out_adjacency_list(curr);
            // Sort adjacenct
            std::sort(nb.begin(), nb.end(), [](const AdjListEdge& a, const AdjListEdge& b) {
                    return a.vertex < b.vertex;
            });

            // For each neighbor, 
            for (const auto& item : nb) {
                // IF neighbor is not visited, mark visited and push to queue
                if (!visited[item.vertex]) {
                    visited[item.vertex] = true;
                    q.push(item.vertex);
                }
            }
        }
    };

    // Start processing from requested start
    process_vertex(start);

    // If connected_only is false, process again at a vertex not visited, until all have been visited
    if (!connected_only) {
        for (size_t i = 0; i < nvertices(); ++i) {
            if (!visited[i]) {
                process_vertex(i);
            }
        }
    }
}

/**
 * Performs a topological sort of the graph if it is a Directed Acyclic Graph (DAG).
 *
 * @return std::vector<size_t>: A vector containing the indices of the vertices
 * in topologically sorted order. If a cycle is detected, returns an empty vector.
 */
template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
    // Track visited
    std::vector<bool> visited(nvertices(), false);
    // Make stack
    std::stack<size_t> s;

    // Function to do the dft
    auto process_vertex = [&](size_t start_vertex) {
        // Push start to stack
        s.push(start_vertex);

        // While stack not empty
        while (!s.empty()) {
            // Get top and pop stack
            size_t curr = s.top();
            s.pop();

            // If not visited
            if (!visited[curr]) {
                // Mark visited and visit
                visited[curr] = true;
                visitfn(curr);

                // Get adjacent
                std::vector<AdjListEdge> nb = out_adjacency_list(curr);
                // Sort Adjacent
                std::sort(nb.rbegin(), nb.rend(), [](const AdjListEdge& a, const AdjListEdge& b) {
                        return a.vertex < b.vertex;
                });

                // For each neigbor
                for (const auto& item : nb) {
                    // IF neighbor not visited, push to stack
                    if (!visited[item.vertex]) {
                        s.push(item.vertex);
                    }
                }
            }
        }
    };

    // Process at requested start
    process_vertex(start);

    // Check if we need to keep going
    if (!connected_only) {
        for (size_t i = 0; i < nvertices(); ++i) {
            if (!visited[i]) {
                process_vertex(i);
            }
        }
    }
}

std::vector<size_t> Graph::toposort() const {
    std::vector<size_t> result; // Stores the topological sort order of vertices.
    std::vector<bool> visited(nvertices(), false); // Tracks if a vertex has been visited.
    std::vector<bool> on_stack(nvertices(), false); // Tracks if a vertex is currently in the recursion stack.
    bool cycle_detected = false; // Flag to detect cycles in the graph.

    // Define a recursive DFS function to perform depth-first traversal.
    std::function<void(size_t)> dfs = [&](size_t vertex) {
        if (cycle_detected) return; // If a cycle is detected, stop further processing.

        visited[vertex] = true; // Mark the current vertex as visited.
        on_stack[vertex] = true; // Add the current vertex to the recursion stack.

        // Get the adjacency list of the current vertex.
        std::vector<AdjListEdge> nb = out_adjacency_list(vertex);

        // Sort neighbors in descending order (highest index first).
        std::sort(nb.rbegin(), nb.rend(), [](AdjListEdge e1, AdjListEdge e2) {
            return e1.vertex < e2.vertex;
        });

        // Traverse each neighbor of the current vertex.
        for (const auto& neighbor : nb) {
            if (!visited[neighbor.vertex]) {
                // If the neighbor is not visited, perform DFS on it.
                dfs(neighbor.vertex);
            } else if (on_stack[neighbor.vertex]) {
                // If the neighbor is on the stack, a cycle is detected.
                cycle_detected = true;
                return;
            }
        }

        on_stack[vertex] = false; // Remove the current vertex from the recursion stack.
        result.push_back(vertex); // Add the current vertex to the result.
    };

    // Iterate over all vertices to ensure all components are visited.
    for (size_t i = 0; i < nvertices(); ++i) {
        if (!visited[i]) {
            dfs(i); // Start DFS from unvisited vertices.
        }
        if (cycle_detected) break; // Stop if a cycle is detected.
    }

    if (cycle_detected) {
        return {}; // Return an empty result if a cycle is detected.
    }

    // Reverse the result to get the correct topological order.
    std::reverse(result.begin(), result.end());
    return result; // Return the final topological sort order.
}

/**
 * Computes the shortest paths from a start vertex to all other vertices in the graph
 * using Dijkstra's algorithm.
 *
 * @param start: Index of the starting vertex.
 * @return std::vector<dijkstra_row>: A table containing the shortest-known distances
 * and paths to each vertex. If the graph contains negative edge weights, returns an empty table.
 */
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
    // Check if the graph contains negative edge weights (not allowed in Dijkstra's algorithm).
    for (const auto& edge : edges) {
        if (edge.weight < 0) {
            std::cerr << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
            return {};
        }
    }

    // Initialize the result table for Dijkstra's algorithm.
    std::vector<dijkstra_row> table(nvertices(), {0, false, INFINITY, -1});

    // Assign vertex indices to the table.
    for (size_t i = 0; i < nvertices(); ++i) {
        table[i].vertex = i;
    }

    // Define a priority queue to process vertices by their shortest-known distance.
    using pq_entry = std::pair<double, size_t>;
    std::priority_queue<pq_entry, std::vector<pq_entry>, std::greater<pq_entry>> pq;

    table[start].shortest_known = 0; // Set the starting vertex's distance to 0.
    pq.emplace(0.0, start); // Add the starting vertex to the priority queue.

    while (!pq.empty()) {
        size_t curr = pq.top().second; // Get the vertex with the smallest distance.
        pq.pop();

        if (table[curr].visited) continue; // Skip already visited vertices.

        table[curr].visited = true; // Mark the current vertex as visited.

        // Traverse all neighbors of the current vertex.
        for (const auto& neighbor : out_adjacency_list(curr)) {
            size_t next = neighbor.vertex; // Get the neighbor's vertex index.
            double weight = neighbor.weight; // Get the weight of the edge.

            // Relaxation: Update the shortest path if a better one is found.
            if (!table[next].visited && table[curr].shortest_known + weight < table[next].shortest_known) {
                table[next].shortest_known = table[curr].shortest_known + weight;
                table[next].came_from = curr; // Update the predecessor of the neighbor.
                pq.emplace(table[next].shortest_known, next); // Add the neighbor to the priority queue.
            }
        }
    }

    return table; // Return the final shortest path table.
}

#endif /* NIU_CSCI340_GRAPH_H */

