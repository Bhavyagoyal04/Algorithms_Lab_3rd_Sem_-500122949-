#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item {
    int weight;
    int value;
};

// Function to compare items by their value-to-weight ratio
int compare(const void *a, const void *b) {
    struct Item* item1 = (struct Item*)a;
    struct Item* item2 = (struct Item*)b;
    double r1 = (double)item1->value / item1->weight;
    double r2 = (double)item2->value / item2->weight;
    return (r2 > r1) - (r2 < r1);
}

// Greedy approach for 0/1 knapsack
int knapsackGreedy(struct Item items[], int n, int W) {
    qsort(items, n, sizeof(struct Item), compare);
    int totalValue = 0, totalWeight = 0;
    for (int i = 0; i < n; i++) {
        if (totalWeight + items[i].weight <= W) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }
    return totalValue;
}

// Dynamic Programming approach for 0/1 knapsack
int knapsackDP(int weights[], int values[], int n, int W) {
    int dp[n + 1][W + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) ? 
                            (values[i - 1] + dp[i - 1][w - weights[i - 1]]) : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

int main() {
    struct Item items[] = {{2, 10}, {3, 14}, {4, 16}, {5, 18}};
    int weights[] = {2, 3, 4, 5};
    int values[] = {10, 14, 16, 18};
    int W = 7;
    int n = sizeof(items) / sizeof(items[0]);

    clock_t start, end;
    double time_spent;

    // Greedy approach
    start = clock();
    int resultGreedy = knapsackGreedy(items, n, W);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Greedy Approach Total Value: %d\n", resultGreedy);
    printf("Greedy Approach Time: %f seconds\n", time_spent);

    // Dynamic Programming approach
    start = clock();
    int resultDP = knapsackDP(weights, values, n, W);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Dynamic Programming Approach Total Value: %d\n", resultDP);
    printf("Dynamic Programming Approach Time: %f seconds\n", time_spent);

    return 0;
}