#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

static inline void swap(int& a, int& b) { a+=b; b=a-b; a=a-b; }

void percDown(vector<int>& v, int n, int i) {
    // Assume the largest is the current node
    int largest = i;
    // Get index of both children
    int left = 2*i+1;
    int right = 2*i+2;

    // If the left child exists, and is larger, update largest
    if (left < n && v[left] > v[largest]) {
        largest = left;
    }
    // If the right child exists, and is larger, update largest
    if (right < n && v[right] > v[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(v[i], v[largest]);
        percDown(v,n,largest);
    }
}

void heapify(vector<int>& v, int n) {
    for (int i = (n-2)/2; i>=0; --i) {
        percDown(v, n, i);
    }
}

void heapSort(vector<int>& v, int n) {
    heapify(v, n);
    int last = n-1;
    while (last > 0) {
        swap(v[0], v[last--]);
        percDown(v, last, 0);
    }
}

int main(int argc, char** argv) {

    vector<int> v = {12, 78, 35, 15, 1, 9, 22};
    int n = static_cast<int>(v.size());

    heapSort(v, n);


    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << '\n' << endl;


    return 0;
}
