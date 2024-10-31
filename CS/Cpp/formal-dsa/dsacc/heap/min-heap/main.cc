#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void min_heapify(vector<int>& arr, int n, int i) {
    int smallest = i;    // Initialize smallest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If left child is smaller than the root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than the smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If the smallest is not the root
    if (smallest != i) {
        std::swap(arr[i], arr[smallest]);

        // Recursively heapify the affected subtree
        min_heapify(arr, n, smallest);
    }
}

void build_heap(vector<int>& v, int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = (n - 1) / 2; i >= 0; --i) {
        min_heapify(v, n, i);
    }
}

void percUp(vector<int>& v, int i) {
    int parent = (i-1)/2;

    while (i>0 && v[i] < v[parent]) {
        std::swap(v[i], v[parent]);

        parent = i-1/2;
    }
}

void heapInsert(vector<int>& v, int element) {
    v.push_back(element);
    int index = v.size() - 1;
    percUp(v, index);
}

void removeRoot(vector<int>& v) {
    std::swap(v[0], v[v.size()-1]);
    v.pop_back();
    min_heapify(v,v.size(), 0);
}

void erase(vector<int>& v, int element) {
    bool found = false;
    while (!found) {
        found = false;
        int i=0;
        for (;i<(int)v.size(); ++i) {
            if (v[i] == element) {
                found = true;
                std::swap(v[i], v[v.size()-1]);
                v.pop_back();

                if (v[i] > v[(i-1)/2]) {
                    min_heapify(v, v.size(), i);
                } else {
                    percUp(v, i);
                }
            }
        }
        if (i == v.size()) break;
    }
}

int main(int argc, char** argv) {

    vector<int> v = {10, 40, 28, 35, 8, 2};
    int n = v.size();

    build_heap(v, n);

    for (const auto& item : v) {
        cout << item << endl;
    }
    cout << endl;

    heapInsert(v, 7);

    for (const auto& item : v) {
        cout << item << endl;
    }
    cout << endl;

    removeRoot(v);
    for (const auto& item : v) {
        cout << item << endl;
    }
    cout << endl;

    erase(v, 40);
    for (const auto& item : v) {
        cout << item << endl;
    }
    cout << endl;

    
    erase(v, 40);
    for (const auto& item : v) {
        cout << item << endl;
    }
    cout << endl;

    return 0;
}
