#include <iostream>
#include <numeric>
#include <algorithm>
#include <deque>
#include <vector>
using std::endl;
using std::cout;

int findSmallestIndex(std::vector<std::vector<int>> v) {

    int smallest = std::accumulate(v[0].begin(), v[0].end(), 0);
    int sum, count=1, idx=0;
    for (auto rowit = v.begin()+1; rowit!=v.end(); ++rowit, ++count) {
        sum = std::accumulate(rowit->begin(), rowit->end(), 0);
        if (sum < smallest) {
            smallest = sum;
            idx = count;
        }
    }
    return idx;
}

std::vector<int> accumulateRows(std::vector<std::vector<int>> v) {
    std::vector<int> accumulatedRows;

    for (auto rowit = v.begin(); rowit!=v.end(); ++rowit) {
        accumulatedRows.push_back(std::accumulate(rowit->begin(), rowit->end(), 0));
    }

    return accumulatedRows;
}

int bricklayers(int b, int a[], int len) {

    if (!b || len < 1) return -1;

    if ( !(std::all_of(a, a+len, [] (int x) { return x>0; }))) return -1;

    if (b == 1) {
        return std::accumulate(a, a+len, 0);
    }

    if (b >= len) {
        return *std::max_element(a,a+len);
    }

    std::vector<std::vector<int>> splits(b, std::vector<int>(len));
    std::deque<int> waiting(a, a+len); std::sort(waiting.begin(), waiting.end(), std::greater<>());


    std::vector<int> tmp;
    for (int i=0; i<b; ++i) {   
        tmp.clear();
        tmp.push_back(waiting[0]);
        waiting.pop_front();
        splits[i] = (tmp);
    }


    int count{0}, numLeft = waiting.size();  
    while (count < numLeft) {
        int smallestIdx = findSmallestIndex(splits);
        splits[smallestIdx].push_back(waiting.front()); 
        waiting.pop_front();
        ++count;
    }

    std::vector<int> maxtimes = accumulateRows(splits);

    return *std::max_element(maxtimes.begin(), maxtimes.end());
}
