/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <map>

#include <signal.h>

#include "graph.decl.h"
#include "graph.h"

// format to store graphs in
// line records - tab delimited
// comment lines start with #
// vertex lines start with V
// V\tNUMBER\tLABEL
// edge lines start with E
// E\tORIGIN\tDESTINATION\tWEIGHT

template <typename CONTAINER>
void print_matrix(const CONTAINER &c, size_t N, size_t colw) {
  if(c.size() != N*N) { 
    std::cout << "ERROR: Matrix is in the wrong sized container. Expected " << N << "x" << N << "=" << N*N << ", got " << c.size() << "\n";
  }
  for(size_t i = 0; i < N; ++i) {
    std::cout << "  ";
    for(size_t j = 0; j < N; ++j) {
      std::cout << std::setw(colw) << c[i*N + j] << " ";
    }
    std::cout << "\n";
  }
}

template <typename CONTAINER>
void handle_edge_line(const std::string &str, CONTAINER &c) {
  //std::cout << "found edge\n";
  auto first = std::find(str.begin(), str.end(), '\t'); 
  if(first == str.end()) {
    std::cout << "Error in file: Edge missing origin.\n";
    return;
  }
  auto second = std::find(first+1, str.end(), '\t'); 
  if(second == str.end()) {
    std::cout << "Error in file: Edge missing destination.\n";
    return;
  }
  std::string origin_str(first+1, second); 
  std::string dest_str;
  std::string weight_str;
  auto third = std::find(second+1, str.end(), '\t'); 
  if(third == str.end()) {
    // no weight 
    weight_str = "1"; // assume 1 as the weight if not supplied
    dest_str.assign(second+1, str.end()); 
  }
  else {
    weight_str.assign(third+1, str.end()); 
    dest_str.assign(second+1, third); 
  }
  size_t origin, dest;
  double weight;
  errno = 0;
  origin = strtol(origin_str.c_str(), nullptr, 10);
  if(errno) {
    std::cout << "Error converting origin vertex index \"" << origin_str << "\" to integer.\n";
    return; }

  errno = 0;
  dest = strtol(dest_str.c_str(), nullptr, 10);
  if(errno) {
    std::cout << "Error converting destination vertex index \"" << dest_str << "\" to integer.\n";
    return; }

  errno = 0;
  weight = strtod(weight_str.c_str(), nullptr);
  if(errno) {
    std::cout << "Error converting weight \"" << weight_str << "\" to double.\n";
    return;
  }
  //std::cout << "Edge found - origin=\"" << origin_str << "\", dest=\"" << dest_str << "\", weight=\"" << weight_str << "\" (" << weight << ")\n";

  GraphEdge ge;
  ge.origin = origin;
  ge.destination = dest;
  ge.weight = weight;
  c.push_back(ge); 
}

template <typename CONTAINER>
void handle_vertex_line(const std::string &str, CONTAINER &c) {
  auto first = std::find(str.begin(), str.end(), '\t'); 
  if(first == str.end()) {
    std::cout << "Error in file: Vertex missing index.\n";
    return;
  }
  auto second = std::find(first+1, str.end(), '\t'); 
  if(second == str.end()) {
    std::cout << "Error in file: Vertex missing label.\n";
    return;
  }

  // got both index and label
  std::string index_str(first+1, second); 
  size_t index = atoi(index_str.c_str()); 
  std::string label_str(second+1, str.end());

  //std::cout << "VERTEX: index as string: \"" << index_str << "\" - as integer -> " << atoi(index_str.c_str()) << ", label: \"" << label_str << "\"\n";

  if( std::find_if(c.begin(), c.end(), [index] (auto pair) { return pair.first == index; } ) != c.end() )  {
    std::cout << "Error in file: Duplicate index (" << index << ") found. Ignoring the more recent one.\n"; 
  }
  c.push_back(std::make_pair(index, label_str)); 
}

void load_graph_file(std::istream &file, Graph & g) {
  std::vector <std::pair <size_t, std::string> > vertices;
  std::vector <GraphEdge> edges;

  std::string line;
  int lineno = 1;
  while(std::getline(file, line)) {
    //std::cout << std::setw(3) << lineno << "| " << line << "\n";
    if(line[0] == 'V' || line[0] == 'v') {
      handle_vertex_line(line, vertices); }
    else if(line[0] == 'E' || line[0] == 'e') {
      handle_edge_line(line, edges); }
    else if(line[0] == '#') {
      //std::cout << "This line is a comment.\n";
    }
    else {
      std::cout << "Line " << lineno << " is invalid. Ignoring.\n"; }
    lineno++;
  }
 
  // sort vertices in order of index
  std::sort(vertices.begin(), vertices.end(), [] (auto a, auto b) { return a.first < b.first; });

  // done reading -- display for debug purposes
  std::cout << "Found " << vertices.size() << " vertices:\n";
  for(auto x : vertices) {
    std::cout << "  vertex index=" << x.first << ", label=" << x.second << "\n";
  }
  std::cout << "\n";

  for(size_t i=0; i<vertices.size(); ++i) {
    if(vertices[i].first != i) {
      std::cout << "Error in file: Vertices must have indices numbered starting from 0 and no gaps are allowed.\n";
      return; } }

  std::cout << "Found " << edges.size() << " edges:\n";
  for(auto x : edges) {
    std::cout << "  edge origin=" << vertices[x.origin].second << "(" << x.origin << "), "
                       << "dest=" << vertices[x.destination].second << "(" << x.destination << "), "
                       << "weight=" << x.weight << "\n";
  }
  std::cout << "\n";

  // check for duplicate edges
  for(size_t i=0; i<edges.size(); ++i) {
    for(size_t j=0; j<edges.size(); ++j) {
      if(i!=j && (edges[i].origin == edges[j].origin) && (edges[i].destination == edges[j].destination)) {
        // error -- two edges share same origin and destination -- always ambiguous
        std::cout << "Error in file: There are two different edges from the same origin to the same destination. Not allowed.\n";
        return;
      }
    }
  }
  std::vector <std::string> v_for_g(vertices.size());
  for(size_t i=0; i<vertices.size(); ++i) {
    v_for_g[i] = vertices[i].second;
  }


  g.assign(v_for_g, edges); 
}

const char * default_filename = "input/gtest1.graph";

int main(int argc, char *argv[]) {
  using std::cout;

  const char * filename;

  if(argc > 1) {
    filename = argv[1];
  }
  else {
    filename = default_filename;
  }
  std::fstream file(filename); 

  if(!file.is_open()) {
    std::cout << "Error opening file \"" << filename << "\"\n";
    exit(1);
  }
  
  cout << "Loading graph from file \"" << filename << "\"\n";
  Graph g;
  load_graph_file(file, g);

  cout << "  g.nvertices() = " << g.nvertices() << "\n";
  cout << "  g.nedges() = " << g.nedges() << "\n";

  cout << "  Printing undirected adjacency list:\n";
  for(size_t i = 0; i < g.nvertices(); ++i) {
    std::string label = g.v_label(i);
    ssize_t index = g.v_index(label);

    cout << "    " << i << ", label=" << label << ", index=" << index << ": "; 
    auto list = g.undirected_adjacency_list(i); 
    for(auto x : list) {
      cout << "[" << g.v_label(x.vertex) << "(" << x.vertex << ")" << ":" << x.weight << "] "; }
    cout << "\n"; }
  cout << "\n";
  
  cout << "  Printing out-adjacency list:\n";
  for(size_t i = 0; i < g.nvertices(); ++i) {
    std::string label = g.v_label(i);
    ssize_t index = g.v_index(label);

    cout << "    " << i << ", label=" << label << ", index=" << index << ": "; 
    auto list = g.out_adjacency_list(i); 
    for(auto x : list) {
      cout << "[" << g.v_label(x.vertex) << "(" << x.vertex << ")" << ":" << x.weight << "] "; }
    cout << "\n"; }
  cout << "\n";
  
  cout << "  Printing in-adjacency list:\n";
  for(size_t i = 0; i < g.nvertices(); ++i) {
    std::string label = g.v_label(i);
    ssize_t index = g.v_index(label);

    cout << "    " << i << ", label=" << label << ", index=" << index << ": "; 
    auto list = g.in_adjacency_list(i); 
    for(auto x : list) {
      cout << "[" << g.v_label(x.vertex) << "(" << x.vertex << ")" << ":" << x.weight << "] "; }
    cout << "\n"; }
  cout << "\n";

  cout << "  Unweighted Adjacency Matrix\n";
  print_matrix(g.unweighted_adjacency_matrix(),g.nvertices(),1);
  cout << "\n";

  cout << "  Weighted Adjacency Matrix\n";
  print_matrix(g.weighted_adjacency_matrix(),g.nvertices(),5);
  cout << "\n";

  auto print = [&g] (auto x) { cout << "[" << g.v_label(x) << "(" << x << ")] "; };

  cout << "  Depth first (connected only): ";
  g.depth_first(0, print, true);
  cout << "\n";
  
  cout << "  Depth first traversal (all):  ";
  g.depth_first(0, print, false);
  cout << "\n";
  cout << "\n";
  
  cout << "  Breadth first (connected only): ";
  g.breadth_first(0, print, true);
  cout << "\n";
  cout << "  Breadth first traversal (all):  ";
  g.breadth_first(0, print, false);
  cout << "\n";

  cout << "\n";
  cout << "  Topological sort: "; 
  auto topo = g.toposort();
  if(topo.size() != g.nvertices()) cout << "(ends early b/c of cycle) ";
  for(auto x : topo) { print(x); }
  cout << "\n"; cout << "\n";


  auto test_dijkstra = [g] (size_t source) {
  std::cout << "Dijkstra's Shortest Path from source " << g.v_label(source) << "(" << source << ")\n";
    auto d = g.dijkstra(source);

    if(d.empty()) {
      cout << "  Dijkstra's returned no results. This could have been caused by a graph with no vertices, or by negative edge weights.\n"; 
    }

    for(auto x : d) {
      cout << "  "
	   << "node=" << g.v_label(x.vertex) << "(" << x.vertex << "), "
	   //<< "visited=" << x.visited << ", "
	   << "distance =" << std::setw(2) << x.shortest_known;
      if(x.came_from != -1) {
	cout << ", from vertex " << g.v_label(x.came_from) << "(" << x.came_from << ")\n"; }
      else {
	cout << "\n"; }
    }
    cout << "\n";
  };

  for(size_t i=0;i<g.nvertices();++i) test_dijkstra(i);
}
