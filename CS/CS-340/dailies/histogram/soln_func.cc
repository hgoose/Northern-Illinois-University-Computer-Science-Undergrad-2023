#include <iostream>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::vector;

int histogram(int a[], int len) {

    std::map<int, int> occurences;
    std::vector<int> insertion_order;

    for(size_t i=0; i<(size_t) len; ++i) {
        if(!occurences[a[i]]) {
            insertion_order.push_back(a[i]);
        }
        occurences[a[i]]++;
    }

    for (const auto& item: insertion_order) {
        cout << item << " occurs " << occurences[item] << " time(s)." << endl;
    }

    return 1;
}
