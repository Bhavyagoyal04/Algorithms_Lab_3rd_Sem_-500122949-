#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

struct Item {
    int value, weight;
};

bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

int greedyKnapsack(std::vector<Item>& items, int W) {
    std::sort(items.begin(), items.end(), compare);
    int currentWeight = 0;
    int finalValue = 0;

    for (auto& item : items) {
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            finalValue += item.value;
        }
    }
    return finalValue;
}

int knapsackDP(std::vector<int>& values, std::vector<int>& weights, int W, int n) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = std::max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}
int main() {
    std::vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    int W = 50;

    auto start = std::chrono::high_resolution_clock::now();
    int greedyResult = greedyKnapsack(items, W);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> greedyTime = end - start;
    std::cout << "Greedy Result: " << greedyResult << ", Time: " << greedyTime.count() << " seconds" << std::endl;

    std::vector<int> values = {60, 100, 120};
    std::vector<int> weights = {10, 20, 30};
    start = std::chrono::high_resolution_clock::now();
    int dpResult = knapsackDP(values, weights, W, values.size());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dpTime = end - start;
    std::cout << "DP Result: " << dpResult << ", Time: " << dpTime.count() << " seconds" << std::endl;

    return 0;
}