#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <forward_list>
#include <set>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::queue;

struct types {
    template <typename T>
        using matrix = vector<vector<T>>;
};

int main (int argc, char** argv) {


     // Create a set of integers
    std::set<int> s = {10, 20, 30, 40, 50};

    int val = 25;

    // Using lower_bound() to find the first element >= 25
    auto lb = s.lower_bound(val);
    if (lb != s.end()) {
        std::cout << "Lower bound of " << val << " is " << *lb << std::endl;
    } else {
        std::cout << "No element is greater than or equal to " << val << std::endl;
    }

    // Using upper_bound() to find the first element > 25
    auto ub = s.upper_bound(val);
    if (ub != s.end()) {
        std::cout << "Upper bound of " << val << " is " << *ub << std::endl;
    } else {
        std::cout << "No element is greater than " << val << std::endl;
    }

    // Using equal_range() to get the range of elements equal to or near 30
    val = 30;
    auto range = s.equal_range(val);

    if (range.first != s.end()) {
        std::cout << "Lower bound of " << val << " is " << *range.first << std::endl;
    }
    if (range.second != s.end()) {
        std::cout << "Upper bound of " << val << " is " << *range.second << std::endl;
    }

    return 0;
}
