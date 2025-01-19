/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_GRAPH_DECL_H
#define NIU_CSCI340_GRAPH_DECL_H

#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <limits>

const double INFINITY = std::numeric_limits<double>::infinity();

#include "config.h"

struct dijkstra_row {
  size_t  vertex;         // the index of the vertex for this row
  bool    visited;        // whether the vertex has been visited
  double  shortest_known; // distance of shortest known path to this vertex
  ssize_t came_from;      // the index of the vertex we came from for shortest known path, or -1 if N/A
};

struct GraphEdge {
  size_t origin;      // index of vertex the edge starts from
  size_t destination; // index of vertex the edge goes to
  double weight;      // the weight/cost associated with this edge
};

struct AdjListEdge {
  size_t vertex; // the index of the vertex on the other side of the edge
  double weight; // the weight/cost associated with this edge
};

// This will go into graph.decl.h, which must include config.h
class Graph {
  std::vector <std::string> vertices;  // labels for each vertex
  std::map<std::string, size_t> v_lut; // for label -> index look up table

  std::vector <GraphEdge>   edges;     // edge list
  
  StudentExtra student; // you can add members to this in config.h

  public:

    // These constructors are provided for you.
    Graph() : vertices(), edges() {} // empty graph constructor
    Graph(const std::vector<std::string> & vertices, const std::vector<GraphEdge> & edges) : vertices(), edges() {
      this->assign(vertices, edges); }

    // Implement the rest of these in graph.h
    size_t nvertices() const;
    size_t nedges() const; 

    std::string v_label(size_t vertex) const; 
    ssize_t v_index(const std::string &label) const;

    void assign(const std::vector<std::string> & vertices, const std::vector<GraphEdge> &edges); 

    bool edge_exists(size_t origin, size_t destination) const; 
    double edge_weight(size_t origin, size_t destination) const; 

    std::vector<AdjListEdge> undirected_adjacency_list(size_t vertex) const;
    std::vector<AdjListEdge> in_adjacency_list(size_t vertex) const;
    std::vector<AdjListEdge> out_adjacency_list(size_t vertex) const; 

    std::vector <double> weighted_adjacency_matrix() const;
    std::vector <bool> unweighted_adjacency_matrix() const;
 
    template <typename FN>
    void depth_first(size_t start, FN visitfn, bool connected_only=true);

    template <typename FN>
    void breadth_first(size_t start, FN visitfn, bool connected_only=true);

    std::vector<size_t> toposort() const; 

    std::vector<dijkstra_row> dijkstra(size_t start) const;
};


#endif /* NIU_CSCI340_GRAPH_DECL_H */
