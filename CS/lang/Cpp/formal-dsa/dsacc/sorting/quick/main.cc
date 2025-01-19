#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using std::vector;
using std::cout;
using std::endl;
using std::swap;
using std::iter_swap;


template<typename ForwardIt>
ForwardIt partition4(ForwardIt p, ForwardIt r) {
    auto middle = p + std::distance(p, r) / 2; // Calculate the middle iterator
    std::iter_swap(middle, r - 1);   // Move the middle element to the end temporarily

    auto pivot = *(r - 1); // Use the last element (original middle) as pivot
    auto i = p; // Boundary for elements less than or equal to the pivot

    for (auto j = p; j != r - 1; ++j) { // Iterate up to the pivot position
        if (*j <= pivot) {
            std::iter_swap(j, i);
            ++i;
        }
    }
    std::iter_swap(i, r - 1); // Place the pivot in its correct position
    return i; // Return the pivot iterator
}

template <typename ForwardIt>
void qsort2(ForwardIt start, ForwardIt end) {
    if (std::distance(start, end) > 1) { // Correct base case: at least two elements
        auto pivot = partition4(start, end);
        qsort2(start, pivot); // Sort elements before the pivot
        qsort2(pivot + 1, end); // Sort elements after the pivot
    }
}


int partition3(std::vector<int>& v, int p, int r) {
    int middle = p + (r-p) / 2;

    // Determine the median of v[p], v[middle], and v[r]
    if ((v[p] > v[middle]) != (v[p] > v[r])) {
        std::swap(v[p], v[r]); // Median is at v[p]
    } else if ((v[middle] > v[p]) != (v[middle] > v[r])) {
        std::swap(v[middle], v[r]); // Median is at v[middle]
    } 
    // If v[r] is the median, no swap is needed since we want it as the pivot

    int x = v[r]; // The pivot is now the median of the three values
    int i = p - 1;

    // Standard partition logic
    for (int j = p; j < r; ++j) {
        if (v[j] <= x) {
            ++i;
            std::swap(v[j], v[i]);
        }
    }
    std::swap(v[i + 1], v[r]); // Place the pivot in its correct position
    return i + 1; // Return the pivot index
}

int partition2(std::vector<int>& v, int p, int r) {
    int middle = p + (r - p) / 2; // Calculate the middle index
    std::swap(v[middle], v[r]);   // Move the middle element to the end temporarily

    int x = v[r];                 // Use the last element (original middle) as pivot
    int i = p - 1;

    for (int j = p; j < r; ++j) {
        if (v[j] <= x) {
            ++i;
            std::swap(v[j], v[i]);
        }
    }
    std::swap(v[i + 1], v[r]);    // Place the pivot in its correct position
    return i + 1;                 // Return the pivot index
}

int partition(vector<int>& v, int p, int r) {
    int x = v[r];
    int i=p-1;

    for (int j=p; j<r; ++j) {
        if (v[j] <= x) {
            ++i;
            swap(v[j], v[i]);
        }
    }
    swap(v[i+1], v[r]);
    return i+1;
}



void qsort(vector<int>& v, int start, int end) {
    if (start < end) {
        int pivot = partition3(v, start, end);
        qsort(v, start, pivot-1);
        qsort(v, pivot+1, end);
    }
}

int main(int argc, char** argv) {
    vector<int> v{17,6,19,81,64,36,28};
    qsort2(v.begin(), v.end());

    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}


// #include <vector>
// #include <iostream>
//
// template <typename It>
// void qsort(It first, It last) {
//     if (last - first > 1) {
//         auto partition_pivot = [](It first, It last) {
//             auto x = *(last - 1);
//             auto i = first - 1;
//             for (auto j = first; *j != *last; ++j) {
//                 if (*j <= x) std::iter_swap(j, ++i);
//             }
//             return i;
//         };
//         auto cut = partition_pivot(first,last);
//         qsort(cut + 1, last);
//         qsort(first, cut);
//     }
// }
//
// int main(int argc, char **argv){
//
//     std::vector v = {67,1,23,8,76,12,18,47};
//     qsort(v.begin(), v.end());
//
//     for (const auto & i : v) {
//         std::cout << i << ' ';
//     }
//
//
//     return 0;
// }
