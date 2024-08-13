#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    vector<vector<int>> C(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int matrixChainMultiplication(const vector<int>& p) {
    int n = p.size() - 1; // Number of matrices
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            int j = i + l - 1;
            for (int k = i; k < j; ++k) {
                int q = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;

    if (n < 2) {
        cout << "At least two matrices are required." << endl;
        return 1;
    }

    vector<vector<vector<int>>> matrices(n);
    vector<int> dimensions(n + 1);

    for (int m = 0; m < n; ++m) {
        int rows, cols;
        cout << "Enter the number of rows and columns for matrix " << (m + 1) << ": ";
        cin >> rows >> cols;
        
        if (m == 0) {
            dimensions[m] = rows;
        }
        dimensions[m + 1] = cols;
        
        matrices[m].resize(rows, vector<int>(cols));
        
        cout << "Enter the elements of matrix " << (m + 1) << ":" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> matrices[m][i][j];
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        if (matrices[i][0].size() != matrices[i + 1].size()) {
            cout << "Matrix dimensions are not compatible for multiplication." << endl;
            return 1;
        }
    }

    int minMultiplications = matrixChainMultiplication(dimensions);

    vector<vector<int>> result = matrices[0];
    for (int i = 1; i < n; ++i) {
        result = multiplyMatrices(result, matrices[i]);
    }

    cout << "Result matrix:" << endl;
    displayMatrix(result);

    cout << "Minimum number of multiplications is: " << minMultiplications << endl;

    return 0;
}
