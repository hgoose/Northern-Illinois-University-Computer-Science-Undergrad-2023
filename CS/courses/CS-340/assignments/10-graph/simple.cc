/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include "graph.decl.h"
#include "graph.h"

std::vector <std::string> vertices;
std::vector <GraphEdge>   edges;

const std::vector <std::string> v_atod {"A", "B", "C", "D"};
const std::vector <GraphEdge> no_edges{};
const std::vector <GraphEdge> e_atod_complete{ {0,1, 1}, {0,2, 2}, {0,3, 3},
                                               {1,0, 4}, {1,2, 5}, {1,3, 6},
                                               {2,0, 7}, {2,1, 8}, {2,3, 9},
                                               {3,0,10}, {3,1,11}, {3,2,12} };

void simple_test_graph(const std::vector <std::string> & vertices,
                       const std::vector <GraphEdge> & edges,
                       const char * label) {
  using std::cout;
  const char * indent = "  ";
  std::cout << "Simple tests: " << label << "\n";
  Graph g(vertices, edges);
  size_t N = g.nvertices();
  std::cout << indent << "vertices: " << N << ", ";
  std::cout << "edges: " << g.nedges() << "\n";

  cout << indent << "lookup vertex name by index: ";
  for(size_t i=0; i<N; ++i) {
    cout << g.v_label(i) << "(" << i << ") "; }
  cout << "\n";
  
  cout << indent << "lookup vertex index by name: ";
  for(size_t i=0; i<N; ++i) {
    std::string name = vertices[i];
    cout << name << "(" << g.v_index(name) << ") ";
  }
  cout << "\n";

  for(size_t i=0; i<N; ++i) {
    for(size_t j=0; j<N; ++j) {
      cout << indent;
      cout << g.v_label(i) << "(" << i << ")->";
      cout << g.v_label(j) << "(" << j << ") ";
      bool isadj = g.edge_exists(i,j);
      cout << "edge? " << isadj;
      cout << " weight? " << g.edge_weight(i, j);
      cout << "\n";
    }
  }
}

int main() {
  std::cout << "********************************************************************************\n";
  std::cout << "* 01-simple - Tests your Graph methods on known graphs.\n";
  std::cout << "********************************************************************************\n";
  simple_test_graph(v_atod, no_edges, "graph with no edges"); 
  simple_test_graph(v_atod, e_atod_complete, "complete graph"); 
}
