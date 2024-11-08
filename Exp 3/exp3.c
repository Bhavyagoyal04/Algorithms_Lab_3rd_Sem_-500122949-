#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Traditional matrix multiplication for 2x2 matrices
void multiplyTraditional(int A[][2], int B[][2], int result[][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;  // Initialize result cell to 0
            for (int k = 0; k < 2; k++) {
                result[i][j] += A[i][k] * B[k][j];  // Sum of products
            }
        }
    }
}

// Helper function to add two 2x2 matrices
void addMatrix(int A[][2], int B[][2], int result[][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = A[i][j] + B[i][j];  // Element-wise addition
        }
    }
}

// Helper function to subtract two 2x2 matrices
void subtractMatrix(int A[][2], int B[][2], int result[][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = A[i][j] - B[i][j];  // Element-wise subtraction
        }
    }
}

// Strassen's matrix multiplication for 2x2 matrices
void strassenMultiply(int A[][2], int B[][2], int result[][2]) {
    // Extract elements for easy reference
    int A11 = A[0][0], A12 = A[0][1], A21 = A[1][0], A22 = A[1][1];
    int B11 = B[0][0], B12 = B[0][1], B21 = B[1][0], B22 = B[1][1];
    
    // Compute the seven products required by Strassen's method
    int M1 = (A11 + A22) * (B11 + B22);
    int M2 = (A21 + A22) * B11;
    int M3 = A11 * (B12 - B22);
    int M4 = A22 * (B21 - B11);
    int M5 = (A11 + A12) * B22;
    int M6 = (A21 - A11) * (B11 + B12);
    int M7 = (A12 - A22) * (B21 + B22);
    
    // Combine products to get the final result matrix
    result[0][0] = M1 + M4 - M5 + M7;
    result[0][1] = M3 + M5;
    result[1][0] = M2 + M4;
    result[1][1] = M1 + M3 - M2 + M6;
}

// Function to print a 2x2 matrix
void printMatrix(int matrix[][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to compare the performance of traditional and Strassen matrix multiplication
void compareMatrixMultiplication() {
    int A[2][2] = {{1, 2}, {3, 4}};  // First matrix
    int B[2][2] = {{5, 6}, {7, 8}};  // Second matrix
    int resultTraditional[2][2], resultStrassen[2][2];
    
    // Measure time for traditional matrix multiplication
    clock_t startTraditional = clock();
    multiplyTraditional(A, B, resultTraditional);
    clock_t endTraditional = clock();
    double durationTraditional = (double)(endTraditional - startTraditional) * 1000000 / CLOCKS_PER_SEC;
    
    // Measure time for Strassen matrix multiplication
    clock_t startStrassen = clock();
    strassenMultiply(A, B, resultStrassen);
    clock_t endStrassen = clock();
    double durationStrassen = (double)(endStrassen - startStrassen) * 1000000 / CLOCKS_PER_SEC;
    
    // Print results and timing for traditional multiplication
    printf("Traditional Matrix Multiplication Result:\n");
    printMatrix(resultTraditional);
    printf("Time taken for Traditional Matrix Multiplication: %.2f microseconds\n", durationTraditional);
    
    // Print results and timing for Strassen multiplication
    printf("Strassen Matrix Multiplication Result:\n");
    printMatrix(resultStrassen);
    printf("Time taken for Strassen Matrix Multiplication: %.2f microseconds\n", durationStrassen);
}

// Main function to execute the comparison
int main() {
    compareMatrixMultiplication();
    return 0;
}