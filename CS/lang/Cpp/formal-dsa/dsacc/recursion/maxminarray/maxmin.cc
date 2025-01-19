#include <iostream>
#include <functional>
#include <utility>
using std::cout;
using std::endl;
using std::pair;
using std::function;

[[nodiscard]] pair<int,int> maxMin(int arr[], int n) {
    // Note: Can be expressed as a tree, calls follow preorder trav


    // Recurse and get largest
    function<int(int a[], int start, int end)> getMax = [&] (int a[], int start, int end) -> int {

        if (start == end) return a[start];

        int mid = (start + end) / 2;
        int leftmax = getMax(a, start, mid);
        int rightmax = getMax(a, mid+1, end);

        return (leftmax > rightmax) ? leftmax : rightmax;
    };

    // Recurse and get smallest
    function<int(int a[], int start, int end)> getMin = [&] (int a[], int start, int end) -> int {

        // If subarray size 1, return that single element
        if (start == end) return a[start];

        int mid = (start + end) / 2;
        // Recurse all the way to the left
        int leftmin = getMin(a, start, mid);

        // Recurse all the way to the right
        int rightmin = getMin(a, mid+1, end);

        // Once at a leaf node, return max of left and right
        return (leftmin < rightmin) ? leftmin : rightmin;
    };

    return std::pair<int,int>(getMax(arr, 0, n-1), getMin(arr, 0, n-1));
}



int main(int argc, char** argv) {
    
    int arr[5] = {1,2,3,5,4};
    int n = 5;

    std::pair<int,int> p = maxMin(arr, n);

    cout << "Maximum: " << p.first << endl << "Minimum: " << p.second << endl;
    


    return 0;
}
