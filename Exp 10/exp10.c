#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEXT_LENGTH 100000

// Naive String Matching
int naiveStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            count++;
        }
    }
    return count;
}

// Rabin-Karp String Matching
#define d 256
#define q 101

int rabinKarpMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    int i, j;
    int pHash = 0, tHash = 0;
    int h = 1;

    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % q;
        tHash = (d * tHash + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++) {
        if (pHash == tHash) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                count++;
            }
        }

        if (i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + m]) % q;
            if (tHash < 0) {
                tHash = (tHash + q);
            }
        }
    }
    return count;
}

// Knuth-Morris-Pratt (KMP) String Matching
void computeLPSArray(char* pattern, int m, int* lps) {
    int length = 0;
    lps[0] = 0;
    
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int kmpStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    
    int lps[m];
    computeLPSArray(pattern, m, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}

// Timing function to compare algorithms
void compareStringMatchingAlgorithms(char* text, char* pattern) {
    clock_t start, end;
    double time_spent;

    // Naive String Matching
    start = clock();
    printf("Naive String Matching: %d matches\n", naiveStringMatch(text, pattern));
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for Naive String Matching: %f seconds\n", time_spent);

    // Rabin-Karp Algorithm
    start = clock();
    printf("Rabin-Karp String Matching: %d matches\n", rabinKarpMatch(text, pattern));
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for Rabin-Karp: %f seconds\n", time_spent);

    // KMP Algorithm
    start = clock();
    printf("KMP String Matching: %d matches\n", kmpStringMatch(text, pattern));
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken for KMP: %f seconds\n", time_spent);
}

int main() {
    char text[MAX_TEXT_LENGTH] = "ABABDABACDABABCABAB";
    char pattern[] = "ABAB";
    
    compareStringMatchingAlgorithms(text, pattern);
    
    return 0;
}