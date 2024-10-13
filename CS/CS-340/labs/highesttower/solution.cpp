#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::sort;


// Made by nate warner z2004109 and ralph helm 1610706
//
// Variant of the first solution with better sorting

void sortVP(vector<pair<int,int>>& v) {
    sort(v.begin(), v.end(), [] (const pair<int,int>& a, const pair<int,int>& b) -> bool {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first > b.first;
        }
    );
}

void buildHanoiTower(const vector<pair<int, int>> &v, int & height, int & index ) {

    if (v.size() == 1) {
        height = v[0].second;
        index = 0;
        return;
    }

    vector<pair<int, int>> vcopy = v;
    sortVP(vcopy);


    height+= vcopy[v.size() -1].second;
    pair<int, int> paircopy = vcopy[v.size() - 1];
    for (int i=(int) vcopy.size()-2; i>=0; --i) {

        if (vcopy[i].first < paircopy.first && vcopy[i].second < paircopy.second) {
            height+=vcopy[i].second;
            paircopy = vcopy[i];
        } 
    }

    for (int i=0; i<(int)v.size(); ++i) {
        if (v[i] == paircopy) {
            index = i;
            break;
        }
    }
}

