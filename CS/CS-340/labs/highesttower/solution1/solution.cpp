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

void sortVP(vector<pair<int,int>>& v) {
    
    std::sort(v.begin(), v.end(), [] (pair<int, int>& a, pair<int,int>& b) {
            return a.first > b.first;
        });

    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i=0; i<(int)v.size()-1; ++i) {
            if (v[i].first > v[i+1].first) {
                pair<int,int> tmp = v[i];
                v[i] = v[i+1];
                v[i+1] = tmp;
                swapped = true;
            }
        }
    }
}


void buildHanoiTower(const vector<pair<int, int>> &v, int & height, int & index ) {

    unsigned long vsize = v.size();

    if (vsize == 1) {
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
            vcopy.pop_back();
        } else if (vcopy[i].second > paircopy.second) {
            height-=paircopy.second;
            vcopy.pop_back();
            paircopy = vcopy[i];
            height+=paircopy.second;
        }
    }

    for (int i=0; i<(int)v.size(); ++i) {
        if (v[i] == paircopy) {
            index = i;
        }
    }
}

