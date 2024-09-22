#include <iostream>
#include <vector>

void traditionalMultiplication(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void addMatrices(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassenMultiplication(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> M1(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M2(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M3(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M4(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M5(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M6(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M7(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> AResult(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> BResult(newSize, std::vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    addMatrices(A11, A22, AResult, newSize);
    addMatrices(B11, B22, BResult, newSize);
    strassenMultiplication(AResult, BResult, M1, newSize);

    addMatrices(A21, A22, AResult, newSize);
    strassenMultiplication(AResult, B11, M2, newSize);

    subtractMatrices(B12, B22, BResult, newSize);
    strassenMultiplication(A11, BResult, M3, newSize);

    subtractMatrices(B21, B11, BResult, newSize);
    strassenMultiplication(A22, BResult, M4, newSize);

    addMatrices(A11, A12, AResult, newSize);
    strassenMultiplication(AResult, B22, M5, newSize);

    subtractMatrices(A21, A11, AResult, newSize);
    addMatrices(B11, B12, BResult, newSize);
    strassenMultiplication(AResult, BResult, M6, newSize);

    subtractMatrices(A12, A22, AResult, newSize);
    addMatrices(B21, B22, BResult, newSize);
    strassenMultiplication(AResult, BResult, M7, newSize);

    addMatrices(M1, M4, AResult, newSize);
    subtractMatrices(AResult, M5, BResult, newSize);
    addMatrices(BResult, M7, C, newSize);

    addMatrices(M3, M5, C, newSize);

    addMatrices(M2, M4, C, newSize);

    addMatrices(M1, M2, C, newSize);
}

int main() {
    int n = 2;

    std::vector<std::vector<int>> A = {{1, 2},
                                       {3, 4}};

    std::vector<std::vector<int>> B = {{5, 6},
                                       {7, 8}};

    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    traditionalMultiplication(A, B, C, n);
    std::cout << "Traditional Matrix Multiplication Result:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> CStrassen(n, std::vector<int>(n, 0));

    strassenMultiplication(A, B, CStrassen, n);
    std::cout << "Strassen's Matrix Multiplication Result:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << CStrassen[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}