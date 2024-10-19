#include <iostream>
#include <string>
#include <vector>
#include <chrono>

void naiveStringMatch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            std::cout << "Pattern found at index: " << i << std::endl;
        }
    }
}

const int d = 256;
const int q = 101;

void rabinKarp(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    int p = 0;
    int t = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                std::cout << "Pattern found at index: " << i << std::endl;
            }
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) {
                t += q;
            }
        }
    }
}

void computeLPS(const std::string& pattern, std::vector<int>& lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmpSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> lps(m);
    computeLPS(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            std::cout << "Pattern found at index: " << (i - j) << std::endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::string text = "ABABDABACDABABCABABABABABDABACDABABCABAB";
    std::string pattern = "ABAB";

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Naive String Matching:\n";
    naiveStringMatch(text, pattern);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> naive_duration = end - start;
    std::cout << "Execution Time: " << naive_duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    std::cout << "\nRabin-Karp Algorithm:\n";
    rabinKarp(text, pattern);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> rabin_duration = end - start;
    std::cout << "Execution Time: " << rabin_duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    std::cout << "\nKnuth-Morris-Pratt Algorithm:\n";
    kmpSearch(text, pattern);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> kmp_duration = end - start;
    std::cout << "Execution Time: " << kmp_duration.count() << " ms\n";

    return 0;
}