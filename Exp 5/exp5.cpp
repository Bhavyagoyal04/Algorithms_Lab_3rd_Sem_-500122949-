#include <iostream>
#include <limits.h>
#include <vector>

void printOptimalParenthesis(std::vector<std::vector<int>>& s, int i, int j) {
    if (i == j) {
        std::cout << "A" << i;
    } else {
        std::cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        std::cout << ")";
    }
}

int matrixChainMultiplication(std::vector<int>& p, int n) {
    std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> s(n, std::vector<int>(n, 0));

    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    std::cout << "Minimum number of multiplications is " << m[1][n - 1] << std::endl;

    std::cout << "Optimal Parenthesization: ";
    printOptimalParenthesis(s, 1, n - 1);
    std::cout << std::endl;

    return m[1][n - 1];
}

int main() {
    std::vector<int> dimensions = {40, 20, 30, 10, 30};

    int n = dimensions.size();
    matrixChainMultiplication(dimensions, n);

    return 0;
}