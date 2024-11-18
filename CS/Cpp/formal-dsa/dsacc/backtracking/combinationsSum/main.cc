#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

void generateCombinations(const std::vector<int>& nums, int k, int start, std::vector<int>& current, std::vector<std::vector<int>>& result, const int& sum, int& currentSum) {
    if (current.size() == k) {
        if (currentSum == sum)  {
            result.push_back(current);
        }
        return;
    }

    for (int i=start; i<nums.size(); ++i) {
        current.push_back(nums[i]);
        currentSum += nums[i];

        generateCombinations(nums, k, i+1, current, result, sum, currentSum);

        currentSum-=nums[i];
        current.pop_back();
    }
}

int main() {
    // Input: array of numbers and size of combinations
    std::vector<int> nums = {1, 2, 3, 4,5,6};
    int k = 2, sum = 6;

    // To store the result combinations
    std::vector<std::vector<int>> result;

    // Temporary vector to store current combination
    std::vector<int> current;

    // Generate all combinations
    int currentsum = 0;
    generateCombinations(nums, k, 0, current, result, sum, currentsum);

    // Output the combinations
    std::cout << "Combinations of size " << k << " that sum to " << sum << ":\n";
    for (const auto& combination : result) {
        for (int num : combination) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    return 0;
}


