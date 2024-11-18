#include <iostream>
#include <vector>

void generateCombinations(const std::vector<int>& nums, int k, int start, std::vector<int>& current, std::vector<std::vector<int>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }

    for (int i=start; i<nums.size(); ++i) {
        current.push_back(nums[i]);
        generateCombinations(nums, k, i+1, current, result);
        current.pop_back();
    }
}

int main() {
    // Input: array of numbers and size of combinations
    std::vector<int> nums = {1, 2, 3, 4};
    int k = 2;

    // To store the result combinations
    std::vector<std::vector<int>> result;

    // Temporary vector to store current combination
    std::vector<int> current;

    // Generate all combinations
    generateCombinations(nums, k, 0, current, result);

    // Output the combinations
    std::cout << "Combinations of size " << k << ":\n";
    for (const auto& combination : result) {
        for (int num : combination) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

