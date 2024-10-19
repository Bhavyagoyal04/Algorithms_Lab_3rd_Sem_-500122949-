#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int knapsack_backtracking(vector<int>& wt, vector<int>& val, int W, int n, int curr_val = 0, int curr_wt = 0, int idx = 0) {
    if (idx == n || curr_wt > W) {
        return curr_wt <= W ? curr_val : 0;
    }

    int include = knapsack_backtracking(wt, val, W, n, curr_val + val[idx], curr_wt + wt[idx], idx + 1);

    int exclude = knapsack_backtracking(wt, val, W, n, curr_val, curr_wt, idx + 1);

    return max(include, exclude);
}

struct Item {
    int weight, value, index;
    double ratio;
    Item(int w, int v, int i) : weight(w), value(v), index(i), ratio(double(v) / w) {}
};

struct Node {
    int level, profit, weight;
    double bound;
    Node(int l, int p, int w, double b) : level(l), profit(p), weight(w), bound(b) {}
    bool operator<(const Node& other) const { return bound < other.bound; }
};

double bound(Node u, int n, int W, vector<Item>& items) {
    if (u.weight >= W) return 0;
    double profit_bound = u.profit;
    int j = u.level + 1;
    int tot_weight = u.weight;

    while (j < n && tot_weight + items[j].weight <= W) {
        tot_weight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    if (j < n) profit_bound += (W - tot_weight) * items[j].ratio;
    return profit_bound;
}

int knapsack_branch_and_bound(int W, vector<int>& wt, vector<int>& val) {
    int n = wt.size();
    vector<Item> items;
    for (int i = 0; i < n; i++) {
        items.push_back(Item(wt[i], val[i], i));
    }
    sort(items.begin(), items.end(), [](Item a, Item b) { return a.ratio > b.ratio; });

    priority_queue<Node> Q;
    Node u(0, 0, 0, 0), v(0, 0, 0, 0);
    Q.push(u);
    int max_profit = 0;

    while (!Q.empty()) {
        u = Q.top();
        Q.pop();

        if (u.level == n || u.weight > W) continue;

        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= W && v.profit > max_profit) max_profit = v.profit;
        v.bound = bound(v, n, W, items);

        if (v.bound > max_profit) Q.push(v);

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, items);

        if (v.bound > max_profit) Q.push(v);
    }

    return max_profit;
}
#include <iostream>
#include <vector>
using namespace std;

int knapsack_dynamic_programming(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> K(n + 1, vector<int>(W + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    return K[n][W];
}

int main() {
    vector<int> wt = {2, 3, 4, 5};
    vector<int> val = {3, 4, 5, 6};
    int W = 5;
    int n = wt.size();

    int max_value1 = knapsack_backtracking(wt, val, W, n);
    cout << "Maximum value (Backtracking): " << max_value1 << endl;

    int max_value2 = knapsack_branch_and_bound(W, wt, val);
    cout << "Maximum value (Branch and Bound): " << max_value2 << endl;

    int max_value3 = knapsack_dynamic_programming(W, wt, val, n);
    cout << "Maximum value (Dynamic Programming): " << max_value3 << endl;

    return 0;
}