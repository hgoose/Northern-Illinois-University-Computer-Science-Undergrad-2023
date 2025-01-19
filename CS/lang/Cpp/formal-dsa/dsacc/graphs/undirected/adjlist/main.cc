#include <ios>
#include <iostream> // For input/output tasks
#include <type_traits>
#include <iomanip> // For input/output manipulators
#include <fstream>
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, EXIT_FAILURE, and malloc
#include <cstdint> // For fixed width data types
#include <numeric>
#include <unistd.h> // Posix API
#include <typeinfo> // typeid(n).name()
#include <cctype> // For character functions
#include <algorithm> // Defined algorithms
#include <iterator> // Iterator functions and types
#include <string> // String class
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstring>
#include <functional>
#include <queue>
#include <cctype>
#include <set>
#include <sstream>
#include <regex>
#include <tuple>
#include <cctype>
#include <cmath>
#include <numeric>
#include <list>
#include <limits.h>
#include <float.h>


#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
#include <iterator>
using std::cout;
using std::vector;
using std::endl;
using std::unordered_map;
using std::queue;

struct graph {
   unordered_map<int, vector<int>> adjlist;  

   void addEdge(int v1, int v2) {
       if (std::find(adjlist[v1].begin(), adjlist[v1].end(), v2) == adjlist[v1].end()) {
           adjlist[v1].push_back(v2);
       }
       if (std::find(adjlist[v2].begin(), adjlist[v2].end(), v1) == adjlist[v2].end()) {
           adjlist[v2].push_back(v1);
       }
   }
   void addNode(int v) {
        if (adjlist.find(v) == adjlist.end()) {
            adjlist[v] = {};
        }
   }
   vector<int> getNeighbors(int v) {
       vector<int> ret{};
       for (const auto& item : adjlist[v]) {
           ret.push_back(item);
       }
       return ret;
   }

   bool hasEdge(int v1, int v2) {
       if (adjlist.find(v1) != adjlist.end() && std::find(adjlist[v1].begin(), adjlist[v1].end(), v2) != adjlist[v1].end()) {
           return true;
       } return false;
   }
   void display() {
       for (const auto& node : adjlist) {
           cout << node.first << " -> ";
           for (const int& neighbor : node.second) {
               cout << neighbor << " ";
           }
           cout << endl;
       }
   }

   size_t size() {
       return adjlist.size(); 
   }

   void bft(int start) {
        bool visited[size()]; 
        std::fill(visited, visited + size(), 0);
        queue<int> q;

        if (adjlist.find(start) == adjlist.end()) {
            cout << "Starting point does not exist" << endl;
            return;
        }
        q.push(start);
        visited[start] = 1;

        while (!q.empty()) {
            int curr = q.front();
            cout << curr << " ";
            q.pop();

            for (const auto& item : adjlist[curr]) {
                if (!visited[item]) {
                    q.push(item);
                    visited[item] = 1;
                }
            }
        }
   }

   void bfs(int start, int end) {
        vector<bool> visited(size(), 0);
        unordered_map<int,int> parent;
        queue<int> q;

        q.push(start);
        visited[start] = 1;
        parent[start] = -1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            if (curr == end) {
                vector<int> path;

                for (int v = end; v != -1; v = parent[v]) {
                    path.push_back(v);
                }
                std::reverse(path.begin(), path.end());

                for (const auto& item : path) {
                    cout << item << " -> ";
                }
                cout << endl;
                return;
            }


            for (const auto& item : adjlist[curr]) {
                if (!visited[item]) {
                    q.push(item);
                    visited[item] = 1;
                    parent[item] = curr;
                }
            }
        }
   }

   void r_dft(int v, vector<bool>& visited) {
       cout << v << " ";

       for (const auto& item : adjlist[v]) {
           if (!visited[item]) {
               visited[item] =  1;
               r_dft(item, visited);
           }
       }
   }

   void dft(int start) {
       if (adjlist.find(start) == adjlist.end()) {
           cout << "Starting point does not exist" << endl;
           return;
       }
       vector<bool> visited(size(), 0);
       visited[start] = 1;
       r_dft(start, visited);
   }



};

int main(int argc, char** argv) {

    graph g;
    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(0,4);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(0,4);

    // g.display();

    g.dft(0);

    // g.bft(0);
    // g.bfs(0,2);
    // cout << endl;


    // vector<int> v = g.getNeighbors(0);
    // for (const auto& item : v) {
    //     cout << item << " ";
    // }
    // cout << endl;

    // cout << std::boolalpha << g.hasEdge(0,4);
    // cout << std::boolalpha << g.hasEdge(0,5);

    // g.display();

    return 0;
}
