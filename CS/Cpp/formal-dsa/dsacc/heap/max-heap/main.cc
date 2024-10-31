#include <iostream>
using std::cout;
using std::endl;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}


void build_heap(int arr[], int n) {
    for (int i=n-1/2; i>=0; --i) {
        heapify(arr, n, i);
    }
}

int main(int argc, char** argv) {

    int arr[] = {48,59,12,7,65, 37};
    int n = 6;

    build_heap(arr, n);

    for (int i=0; i<n; ++i) {
        cout << arr[i] << endl;
    }

    return 0;
}
