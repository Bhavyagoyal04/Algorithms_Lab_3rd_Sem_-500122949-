#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 100

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

// Function for Dynamic Programming approach
int knapSackDP(int W, struct Item items[], int n) {
    int dp[n + 1][W + 1];
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i-1].weight <= w)
                dp[i][w] = (items[i-1].value + dp[i-1][w - items[i-1].weight] > dp[i-1][w]) ? 
                            items[i-1].value + dp[i-1][w - items[i-1].weight] : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][W];
}

// Backtracking approach
int knapSackBacktracking(struct Item items[], int n, int W, int currentWeight, int currentValue) {
    if (n == 0 || currentWeight >= W) {
        return currentValue;
    }
    
    // Include the current item
    int include = 0;
    if (currentWeight + items[n-1].weight <= W) {
        include = knapSackBacktracking(items, n-1, W, currentWeight + items[n-1].weight, currentValue + items[n-1].value);
    }

    // Exclude the current item
    int exclude = knapSackBacktracking(items, n-1, W, currentWeight, currentValue);
    
    return (include > exclude) ? include : exclude;
}

// Branch and Bound approach
struct Node {
    int level, profit, weight;
    float bound;
};

float bound(struct Node u, int n, int W, struct Item items[]) {
    if (u.weight >= W)
        return 0;
    
    int j = u.level + 1;
    float result = u.profit;
    int totalWeight = u.weight;
    
    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        result += items[j].value;
        j++;
    }
    
    if (j < n)
        result += (W - totalWeight) * (float) items[j].value / items[j].weight;
    
    return result;
}

int knapSackBranchBound(struct Item items[], int n, int W) {
    struct Node u, v;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, W, items);
    
    int maxProfit = 0;
    int Q[n];
    int front = 0, rear = 0;
    
    Q[rear++] = 0;
    
    while (front < rear) {
        u.level = Q[front++];
        
        if (u.level == n) continue;
        
        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        
        if (v.weight <= W && v.profit > maxProfit) {
            maxProfit = v.profit;
        }
        
        v.bound = bound(v, n, W, items);
        
        if (v.bound > maxProfit) {
            Q[rear++] = v.level;
        }
    }
    
    return maxProfit;
}

// Time the approaches
void compareKnapsackApproaches(struct Item items[], int n, int W) {
    clock_t start, end;
    double time_spent;
    
    // Time Dynamic Programming
    start = clock();
    printf("Max value using DP: %d\n", knapSackDP(W, items, n));
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for DP: %f seconds\n", time_spent);

    // Time Backtracking
    start = clock();
    printf("Max value using Backtracking: %d\n", knapSackBacktracking(items, n, W, 0, 0));
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for Backtracking: %f seconds\n", time_spent);
    
    // Time Branch and Bound
    start = clock();
    printf("Max value using Branch and Bound: %d\n", knapSackBranchBound(items, n, W));
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for Branch and Bound: %f seconds\n", time_spent);
}

int main() {
    struct Item items[] = {{3, 4}, {2, 3}, {4, 5}, {5, 7}};
    int n = sizeof(items) / sizeof(items[0]);
    int W = 7;
    
    compareKnapsackApproaches(items, n, W);
    
    return 0;
}