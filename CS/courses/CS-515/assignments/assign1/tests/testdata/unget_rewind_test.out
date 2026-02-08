#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
#include <cmath>
#include <bitset>
#include <array>
#include <map>
#include <limits>
#include <tuple>
#include <unordered_set>
using std::tuple;
using std::map;
using std::array;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::bitset;

typedef long long dword;

template<typename T, typename U>
using pmap = unordered_map<T,U>;

template<typename T, typename U, typename W=std::less<T>>
using pq = priority_queue<T,U,W>;

template<typename T>
using lims = std::numeric_limits<T>;

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        pmap<int, int> umap;
        std::unordered_set<int> seen;
        for (int i=0; i<(int)nums.size(); ++i) {
            seen.clear();
            if (i+k > nums.size()) break;
            for (int j=i; j<i+k; ++j) {
                if (seen.find(nums[j]) == seen.end()) {
                    ++umap[nums[j]];
                }
                seen.insert(nums[j]);
            }
        }
        int max = lims<int>::min();
        bool ch=false;
        for (const auto& [key, value] : umap) {
            if (value == 1 && key > max)  {
                max = key;
                ch = true;

            }
        }
        return ch == false ? -1 : max;
    }
};

int main(int argc, char** argv) {

    Solution s;
    vector<int> v{0,0};
    cout << s.largestInteger(v,2);
    return 0;
}
