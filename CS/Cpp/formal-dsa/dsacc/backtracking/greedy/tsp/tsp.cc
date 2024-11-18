#include <iostream>
#include <float.h>
#include <vector>
using std::min;
using std::vector;
using std::cout;
using std::endl;

double tspGreedyBacktracking(vector<vector<double>>& distances, vector<bool>& visited, int currentCity, int citiesVisited, double currentCost, double& bestCost) {
    if (citiesVisited == visited.size()) {
        // Add the cost to return to the starting city
        return currentCost + distances[currentCity][0];
    }

    for (int nextCity = 0; nextCity < distances.size(); ++nextCity) {
        if (!visited[nextCity]) {
            visited[nextCity] = true;

            // Calculate the cost for this path
            double nextCost = currentCost + distances[currentCity][nextCity];
            if (nextCost < bestCost) { // Only proceed if this path is promising
                bestCost = min(bestCost, tspGreedyBacktracking(distances, visited, nextCity, citiesVisited + 1, nextCost, bestCost));
            }

            visited[nextCity] = false; // Backtrack
        }
    }
    return bestCost;
}

int main() {
    vector<vector<double>> distances = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    vector<bool> visited(distances.size(), false);
    visited[0] = true;

    double bestCost = DBL_MAX;
    tspGreedyBacktracking(distances, visited, 0, 1, 0, bestCost);

    cout << "Minimum cost: " << bestCost << endl;
    return 0;
}

