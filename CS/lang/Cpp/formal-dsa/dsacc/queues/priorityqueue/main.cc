#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

struct priority_queue {
private:
    vector<int> heap;

    void percDown(int n, int i) {
        int smallest = i;    // Initialize smallest as root
        int left = 2 * i + 1;   // Left child index
        int right = 2 * i + 2;  // Right child index

        // If left child is smaller than the root
        if (left < n && heap[left] < heap[smallest])
            smallest = left;

        // If right child is smaller than the smallest so far
        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        // If the smallest is not the root
        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);

            // Recursively heapify the affected subtree
            percDown(n, smallest);
        }
    }

    void percUp(int i) {
        int parent = (i-1)/2;

        while (i>0 && heap[i] < heap[parent]) {
            std::swap(heap[i], heap[parent]);
            i=parent;
        }
    }

public:   

    void insert(int element) {
        heap.push_back(element);
        int index = heap.size() - 1;
        percUp(index);
    }

    int pop() {
        if (heap.empty()) return -1;

        int ret = heap[0];
        std::swap(heap[0], heap[heap.size()-1]);
        heap.pop_back();
        percDown((int)heap.size(), 0);
        return ret;
    }

    int top() {
        return heap[0];
    }

    size_t size() {
        return (size_t)heap.size();
    }

    bool empty() {
        return heap.empty();
    }

    void print() {
        for (const auto& item : heap) {
            cout << item << " ";
        }
    }
};




int main(int argc, char** argv) {
    priority_queue p;
    p.insert(10);
    p.insert(40);
    p.insert(5);
    p.insert(15);
    p.insert(9);
    p.insert(90);

    p.print();
    cout << endl;

    int top =  p.pop();
    cout << "Top: " << top << endl << endl;
    p.print();
    cout << endl;
}

