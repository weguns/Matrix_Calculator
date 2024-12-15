#include <iostream>
#include <string>
#include <random>

using namespace std;

int **allocateMatrix(const int rows, const int cols) {
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

inline void deleteMatrix(int **&matrix, const int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

void fillMatrix(int **matrix, const int rows, const int cols, const string &method = "random") {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);

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
                matrix[i][j] = dis(gen);
            }
        }
    }
}

void swapMainAndMinorDiagonals(int **matrix, const int n) {
    for (int i = 0; i < n; i++) {
        swap(matrix[i][i], matrix[i][n - i - 1]);
    }
}

void sumSubtractMatrix(int **A, int **B, int **result, const int rows, const int cols, const char operation = '+') {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = (operation == '-') ? (A[i][j] - B[i][j]) : (A[i][j] + B[i][j]);
        }
    }
}

void matrixMultiply(int **A, int **B, int **result, const int rowA, const int colA_rowB, const int colB) {
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colA_rowB; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void displayMatrix(int **matrix, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void displayMenu() {
    cout << "\nMatrix Calculator Menu:\n";
    cout << "1. Add Matrices\n";
    cout << "2. Subtract Matrices\n";
    cout << "3. Multiply Matrices\n";
    cout << "4. Swap Main and Minor Diagonals (Square Matrix)\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int getPositiveInput(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (value > 0) return value;
        cout << "Invalid input. Please enter a positive integer.\n";
    }
}

void getMatrixDimensions(int &rows, int &cols, const string &matrixName) {
    while (true) {
        rows = getPositiveInput("Enter rows for " + matrixName + ": ");
        cols = getPositiveInput("Enter columns for " + matrixName + ": ");
        if (rows > 0 && cols > 0) break;
        cout << "Invalid input. Rows and columns must be positive integers.\n";
    }
}

string getFillMethod(const string &matrixName) {
    string method;
    while (true) {
        cout << "Fill " << matrixName << " (random/custom/zero): ";
        cin >> method;
        if (method == "random" || method == "custom" || method == "zero") return method;
        cout << "Invalid choice. Please enter 'random', 'custom', or 'zero'.\n";
    }
}

int **createAndFillMatrix(int rows, int cols, const string &matrixName) {
    int **matrix = allocateMatrix(rows, cols);
    fillMatrix(matrix, rows, cols, getFillMethod(matrixName));
    return matrix;
}

void handleMatrixOperation(const string &operationType) {
    int rows, cols;
    getMatrixDimensions(rows, cols, "the matrices");

    int **matrixA = createAndFillMatrix(rows, cols, "Matrix A");
    int **matrixB = createAndFillMatrix(rows, cols, "Matrix B");
    int **result = allocateMatrix(rows, cols);

    char operation = (operationType == "addition") ? '+' : '-';
    sumSubtractMatrix(matrixA, matrixB, result, rows, cols, operation);

    cout << "Result:\n";
    displayMatrix(result, rows, cols);

    deleteMatrix(matrixA, rows);
    deleteMatrix(matrixB, rows);
    deleteMatrix(result, rows);
}

void handleMultiplication() {
    int rowsA, colsA, rowsB, colsB;
    getMatrixDimensions(rowsA, colsA, "Matrix A");
    while (true) {
        getMatrixDimensions(rowsB, colsB, "Matrix B");
        if (colsA == rowsB) break;
        cout << "Invalid input. Columns of Matrix A must equal rows of Matrix B.\n";
    }

    int **matrixA = createAndFillMatrix(rowsA, colsA, "Matrix A");
    int **matrixB = createAndFillMatrix(rowsB, colsB, "Matrix B");
    int **result = allocateMatrix(rowsA, colsB);

    matrixMultiply(matrixA, matrixB, result, rowsA, colsA, colsB);
    cout << "Result of multiplication:\n";
    displayMatrix(result, rowsA, colsB);

    deleteMatrix(matrixA, rowsA);
    deleteMatrix(matrixB, rowsB);
    deleteMatrix(result, rowsA);
}

void handleDiagonalSwap() {
    int n = getPositiveInput("Enter the size of the square matrix: ");
    int **matrix = createAndFillMatrix(n, n, "Matrix");

    swapMainAndMinorDiagonals(matrix, n);
    cout << "Matrix after swapping diagonals:\n";
    displayMatrix(matrix, n, n);

    deleteMatrix(matrix, n);
}

int main() {
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                handleMatrixOperation("addition");
                break;
            case 2:
                handleMatrixOperation("subtraction");
                break;
            case 3:
                handleMultiplication();
                break;
            case 4:
                handleDiagonalSwap();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
