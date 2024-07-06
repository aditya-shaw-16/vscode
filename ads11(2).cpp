#include <iostream> 
#include <vector> 
using namespace std; 
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) { 
    int rowsA = matrixA.size(); 
    int colsA = matrixA[0].size(); 
    int colsB = matrixB[0].size(); 
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0)); 
    for (int i = 0; i < rowsA; ++i) { 
        for (int j = 0; j < colsB; ++j) { 
            for (int k = 0; k < colsA; ++k) { 
                result[i][j] += matrixA[i][k] * matrixB[k][j]; 
            } 
        } 
    } 
    return result; 
} 
int main() { 
    vector<vector<int>> matrixA = {{1, 2, 3}, {4, 5, 6}}; 
    vector<vector<int>> matrixB = {{7, 8}, {9, 10}, {11, 12}}; 
    vector<vector<int>> resultMatrix = multiplyMatrices(matrixA, matrixB); 
    cout << "Resultant Matrix (A * B):" << endl; 
    for (const auto& row : resultMatrix) { 
        for (int val : row) { 
            cout << val << " "; 
        } 
        cout << endl; 
    } 
    return 0; 
} 