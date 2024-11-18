#include <iostream>
#include <vector>

void generatePermutations(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
    // Base case: if the starting index is at the end, we've formed a permutation
    if (start == nums.size()) {
        result.push_back(nums);
        return;
    }

    // Loop through the array to swap the current index with all subsequent indices
    for (int i = start; i < nums.size(); ++i) {
        // Swap the current element with the one at index `i`
        std::swap(nums[start], nums[i]);

        // Recur to generate permutations for the next index
        generatePermutations(nums, start + 1, result);

        // Backtrack: restore the original order
        std::swap(nums[start], nums[i]);
    }
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    std::vector<std::vector<int>> result;

    // Generate permutations
    generatePermutations(nums, 0, result);

    // Output all permutations
    for (const auto& perm : result) {
        for (int num : perm) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

