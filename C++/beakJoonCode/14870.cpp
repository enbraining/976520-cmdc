#include <bits/stdc++.h>
using namespace std;

int gridSize;

struct BinaryIndexedTree {
    long long tree[1515];

    void update(int left, int right, int value) {
        for (; left <= gridSize; left += left & -left) {
            tree[left] += value;
        }
        for (right++; right <= gridSize; right += right & -right) {
            tree[right] -= value;
        }
    }

    long long query(int index) {
        long long result = 0;
        for (; index; index ^= index & -index) {
            result += tree[index];
        }
        return result;
    }
} bit[1515];

int matrix[1515][1515];
int dynamicProgramming[1515][1515];
long long totalSum = 0;
int startColumn[1515], endColumn[1515];

inline long long getValue(int row, int column) {
    return dynamicProgramming[row][column] + bit[row].query(column);
}

void computeDynamicProgramming() {
    for (int i = 1; i <= gridSize; i++) {
        for (int j = 1; j <= gridSize; j++) {
            dynamicProgramming[i][j] = max(dynamicProgramming[i - 1][j], dynamicProgramming[i][j - 1]) + matrix[i][j];
            totalSum += dynamicProgramming[i][j];
        }
    }
}

void processQuery(int startRow, int startColumn, int value) {
    ::startColumn[startRow] = ::endColumn[startRow] = startColumn;
    for (int i = startRow + 1; i <= gridSize; i++) {
        ::startColumn[i] = gridSize + 1;
        ::endColumn[i] = 0;
    }

    for (int i = startRow, j = startColumn;;) {
        if (j < gridSize && max(getValue(i - 1, j + 1), getValue(i, j)) + value == max(getValue(i - 1, j + 1), getValue(i, j) + value)) {
            j++;
        } else {
            i++;
        }
        if (i > gridSize) {
            break;
        }
        ::endColumn[i] = j;
    }

    for (int i = startRow, j = startColumn;;) {
        if (i < gridSize && max(getValue(i + 1, j - 1), getValue(i, j)) + value == max(getValue(i + 1, j - 1), getValue(i, j) + value)) {
            i++;
        } else {
            j++;
        }
        if (j > gridSize || ::endColumn[i] < j) {
            break;
        }
        ::startColumn[i] = min(::startColumn[i], j);
    }

    for (int i = startRow; i <= gridSize; i++) {
        if (::startColumn[i] > ::endColumn[i]) {
            continue;
        }
        bit[i].update(::startColumn[i], ::endColumn[i], value);
        totalSum += value * (::endColumn[i] - ::startColumn[i] + 1);
    }
    cout << totalSum << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> gridSize;
    for (int i = 1; i <= gridSize; i++) {
        for (int j = 1; j <= gridSize; j++) {
            cin >> matrix[i][j];
        }
    }
    computeDynamicProgramming();
    cout << totalSum << "\n";

    for (int i = 1; i <= gridSize; i++) {
        int row, column;
        char operation;
        cin >> operation >> row >> column;
        if (operation == 'U') {
            processQuery(row, column, 1);
        } else {
            processQuery(row, column, -1);
        }
    }
}
