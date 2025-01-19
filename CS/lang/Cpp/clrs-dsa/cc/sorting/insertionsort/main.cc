#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::vector;
using std::endl;
using std::swap;

void insertionsort(vector<int>& v) {
    for (int i=1; i<v.size(); ++i) {
        int key = v[i];

        int j=i-1;
        while (j >= 0 && v[j] > key) {
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = key;
    }

}

int main(int argc, char** argv) {

    vector<int> v{5,2,4,7,1,3,2,6};
    insertionsort(v);

    for(const auto& item : v) {
        cout << item << " ";
    }
    cout << '\n';

    return 0;
}
