#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int** allocateMatrix(const int rows, const int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void deleteMatrix(int** matrix, const int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillMatrix(int** matrix, const int rows, const int cols, const string& method = "random") {
    srand(time(nullptr));
    if (method == "zero") {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = 0;
            }
        }
    } else if (method == "custom") {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Enter value for row " << i << ", col " << j << ": ";
                cin >> matrix[i][j];
            }
        }
    } else {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = rand() % 10 + 1;
            }
        }
    }
}

void swapMainAndMinorDiagonals(int** matrix, const int n) {
    for (int i = 0; i < n; i++) {
        swap(matrix[i][i], matrix[i][n - i - 1]);
    }
}

void sumSubtractMatrix(int** A, int** B, int** result, const int rows, const int cols, const char operation = '+') {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = (operation == '-') ? (A[i][j] - B[i][j]) : (A[i][j] + B[i][j]);
        }
    }
}

void matrixMultiply(int** A, int** B, int** result, const int rowA, const int colA_rowB, const int colB) {
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colA_rowB; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void displayMatrix(int** matrix, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}