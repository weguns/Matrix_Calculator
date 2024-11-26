#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> // EDIT: Added this for using std::string
using namespace std;

int** allocateMatrix(const int rows, const int cols) {
    int** matrix = new int*[rows]; // Allocate memory for row pointers
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols]; // Allocate memory for each row
    }
    return matrix;
}

void deleteMatrix(int** matrix, const int row) {
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillMatrix(int **matrix, const int row, const int col, const string &method = "random") {
    srand(time(nullptr));

    if (method == "zero") {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = 0;
            }
        }
    } else if (method == "custom") {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << "Please enter value for row " << i << " and col " << j << ": ";
                cin >> matrix[i][j];
            }
        }
    } else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = rand() % 10 + 1;
            }
        }
    }
}

void sumSubtractMatrix(int **A, int **B, int **result, const int row, const int col, const char &operation = '+') {
    int sum[row][col];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (operation == '-') {
                result[i][j] = A[i][j] - B[i][j];
            } else {
                result[i][j] = A[i][j] + B[i][j];
            }
        }
    }
}

void matrixMultiply(const int **A,const int **B, int **result, const int rowA, const int colA_rowB, const int colB) {

    // Perform matrix multiplication
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; ++j) {
          result[i][j] = 0;
            for (int k = 0; k < colA_rowB; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

}

void displayMatrix(const int** matrix, const int row, const int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}