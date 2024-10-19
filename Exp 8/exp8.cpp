#include <iostream>
#include <vector>

void sumOfSubsets(std::vector<int>& set, std::vector<int>& subset, int sum, int targetSum, int index) {
    if (sum == targetSum) {
        std::cout << "{ ";
        for (int i : subset) {
            std::cout << i << " ";
        }
        std::cout << "}" << std::endl;
        return;
    }

    if (sum > targetSum || index == set.size()) {
        return;
    }

    subset.push_back(set[index]);
    sumOfSubsets(set, subset, sum + set[index], targetSum, index + 1);

    subset.pop_back();
    sumOfSubsets(set, subset, sum, targetSum, index + 1);
}

int main() {
    std::vector<int> set = {10, 7, 5, 18, 12, 20, 15};
    int targetSum = 35;

    std::cout << "Subsets of the set that sum up to " << targetSum << " are: " << std::endl;
    std::vector<int> subset;
    sumOfSubsets(set, subset, 0, targetSum, 0);

    return 0;
}