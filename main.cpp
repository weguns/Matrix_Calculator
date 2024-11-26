#include <iostream>
#include "matrixFunctions.h"

using namespace std;


int main() {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\nMatrix Calculator Menu:\n";
        cout << "1. Fill a matrix\n";
        cout << "2. Display a matrix\n";
        cout << "3. Swap main and minor diagonals (square matrix only)\n";
        cout << "4. Add two matrices\n";
        cout << "5. Subtract two matrices\n";
        cout << "6. Multiply two matrices\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int rows, cols;
                cout << "Enter the number of rows: ";
                cin >> rows;
                cout << "Enter the number of columns: ";
                cin >> cols;
                int **matrix = allocateMatrix(rows, cols);
                fillMatrix(matrix, rows, cols, "custom");
                cout << "Matrix filled successfully.\n";
                displayMatrix(matrix, rows, cols);
                deleteMatrix(matrix, rows);
                break;
            }
            case 2: {
                int rows, cols;
                cout << "Enter the number of rows: ";
                cin >> rows;
                cout << "Enter the number of columns: ";
                cin >> cols;
                int **matrix = allocateMatrix(rows, cols);
                fillMatrix(matrix, rows, cols);
                cout << "Matrix:\n";
                displayMatrix(matrix, rows, cols);
                deleteMatrix(matrix, rows);
                break;
            }
            case 3: {
                int n;
                cout << "Enter the size of the square matrix: ";
                cin >> n;
                int **matrix = allocateMatrix(n, n);
                fillMatrix(matrix, n, n);
                cout << "Original Matrix:\n";
                displayMatrix(matrix, n, n);
                swapMainAndMinorDiagonals(matrix, n);
                cout << "Matrix after swapping diagonals:\n";
                displayMatrix(matrix, n, n);
                deleteMatrix(matrix, n);
                break;
            }
            case 4: {
                int rows, cols;
                cout << "Enter the dimensions of the matrices (rows and columns): ";
                cin >> rows >> cols;
                int **A = allocateMatrix(rows, cols);
                int **B = allocateMatrix(rows, cols);
                int **result = allocateMatrix(rows, cols);
                cout << "Fill matrix A:\n";
                fillMatrix(A, rows, cols, "custom");
                cout << "Fill matrix B:\n";
                fillMatrix(B, rows, cols, "custom");
                sumSubtractMatrix(A, B, result, rows, cols);
                cout << "Result of addition:\n";
                displayMatrix(result, rows, cols);
                deleteMatrix(A, rows);
                deleteMatrix(B, rows);
                deleteMatrix(result, rows);
                break;
            }
            case 5: {
                int rows, cols;
                cout << "Enter the dimensions of the matrices (rows and columns): ";
                cin >> rows >> cols;
                int **A = allocateMatrix(rows, cols);
                int **B = allocateMatrix(rows, cols);
                int **result = allocateMatrix(rows, cols);
                cout << "Fill matrix A:\n";
                fillMatrix(A, rows, cols, "custom");
                cout << "Fill matrix B:\n";
                fillMatrix(B, rows, cols, "custom");
                sumSubtractMatrix(A, B, result, rows, cols, '-');
                cout << "Result of subtraction:\n";
                displayMatrix(result, rows, cols);
                deleteMatrix(A, rows);
                deleteMatrix(B, rows);
                deleteMatrix(result, rows);
                break;
            }
            case 6: {
                int rowA, colA, rowB, colB;
                cout << "Enter dimensions of matrix A (rows and cols): ";
                cin >> rowA >> colA;
                cout << "Enter dimensions of matrix B (rows and cols): ";
                cin >> rowB >> colB;
                if (colA != rowB) {
                    cout << "Matrix multiplication not possible. Columns of A must equal rows of B.\n";
                    break;
                }
                int **A = allocateMatrix(rowA, colA);
                int **B = allocateMatrix(rowB, colB);
                int **result = allocateMatrix(rowA, colB);
                cout << "Fill matrix A:\n";
                fillMatrix(A, rowA, colA, "custom");
                cout << "Fill matrix B:\n";
                fillMatrix(B, rowB, colB, "custom");
                matrixMultiply(A, B, result, rowA, colA, colB);
                cout << "Result of multiplication:\n";
                displayMatrix(result, rowA, colB);
                deleteMatrix(A, rowA);
                deleteMatrix(B, rowB);
                deleteMatrix(result, rowA);
                break;
            }
            case 7:
                exitProgram = true;
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
