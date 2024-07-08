#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

int numRows, numCols;
long long maxSum;
long long inputMatrix[2300][2300];
long long prefixSumMatrix[2300][2300];
long long tempMatrix[2300][2300];

inline long long computeSubmatrixSum(int x1, int x2, int y1, int y2) { 
    return prefixSumMatrix[x2][y2] - prefixSumMatrix[x1 - 1][y2] - prefixSumMatrix[x2][y1 - 1] + prefixSumMatrix[x1 - 1][y1 - 1]; 
}

int isSubmatrixWithinLimit(int left, int right) {
    int size = right - left + 1;
    int topRow = 1, bottomRow = numRows, leftCol = 1, rightCol = numCols;
    for (int i = 0; i < numRows + numCols - size - 1; i++) {
        if (bottomRow - topRow + 1 > 1 && computeSubmatrixSum(topRow, topRow, leftCol, rightCol) <= maxSum) { 
            topRow++; 
            continue; 
        }
        if (bottomRow - topRow + 1 > 1 && computeSubmatrixSum(bottomRow, bottomRow, leftCol, rightCol) <= maxSum) { 
            bottomRow--; 
            continue; 
        }
        if (leftCol < left && computeSubmatrixSum(topRow, bottomRow, leftCol, leftCol) <= maxSum) { 
            leftCol++; 
            continue; 
        }
        if (rightCol > right && computeSubmatrixSum(topRow, bottomRow, rightCol, rightCol) <= maxSum) { 
            rightCol--; 
            continue; 
        }
        return 0;
    }
    if (computeSubmatrixSum(topRow, bottomRow, leftCol, rightCol) <= maxSum) return 1;
    return 0;
}

int findMinimumSteps() {
    for (int i = 1; i <= numRows; i++) {
        for (int j = 1; j <= numCols; j++) {
            prefixSumMatrix[i][j] = inputMatrix[i][j] + prefixSumMatrix[i - 1][j] + prefixSumMatrix[i][j - 1] - prefixSumMatrix[i - 1][j - 1];
        }
    }
    
    int left = 1, right = 1;
    int minSteps = INT_MAX;
    while (true) {
        int result = isSubmatrixWithinLimit(left, right);
        if (result) {
            minSteps = min(minSteps, numRows + numCols - (right - left + 1));
        }
        if (left == numCols && right == numCols) break;
        if (right == numCols) left++;
        else if (left == right) right++;
        else if (result) right++;
        else left++;
    }
    return minSteps;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> maxSum >> numCols >> numRows;
    for (int i = 1; i <= numRows; i++) {
        for (int j = 1; j <= numCols; j++) {
            cin >> inputMatrix[i][j];
            prefixSumMatrix[i][j] = inputMatrix[i][j];
        }
    }
    
    int steps1 = findMinimumSteps();
    
    memcpy(tempMatrix, inputMatrix, sizeof(tempMatrix));
    for (int i = 1; i <= numCols; i++) {
        for (int j = 1; j <= numRows; j++) {
            inputMatrix[i][j] = tempMatrix[numRows - j + 1][i];
        }
    }
    swap(numRows, numCols);
    
    int steps2 = findMinimumSteps();
    cout << min(steps1, steps2);
}
