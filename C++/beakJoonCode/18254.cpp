#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100005, BLOCK_SIZE = 330, MAX_BLOCKS = 310;

int numElements, numUpdates, numQueries, numBlocks;
int array[MAX_N], leftBound[MAX_N], rightBound[MAX_N], blockXor[MAX_BLOCKS];
bool queryFlag[MAX_BLOCKS][MAX_N];

struct FenwickTree {
    int tree[MAX_N];
    void update(int index, int value) { 
        while (index <= numElements) {
            tree[index] ^= value;
            index += index & -index;
        }
    }
    int query(int index) { 
        int result = 0;
        while (index) {
            result ^= tree[index];
            index -= index & -index;
        }
        return result;
    }
    int query(int start, int end) { 
        return query(end) ^ query(start - 1);
    }
} arrayFenwick, oddFenwick, evenFenwick;

void updateRange(int left, int right, int value) {
    if (left % 2) oddFenwick.update(left, value);
    else evenFenwick.update(left, value);

    if ((left ^ right) & 1) {
        if (left % 2) oddFenwick.update(right + 1, value);
        else evenFenwick.update(right + 1, value);
    } else {
        if (left % 2) evenFenwick.update(right, value);
        else oddFenwick.update(right, value);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> numElements >> numUpdates >> numQueries;

    for (int i = 1, value; i <= numElements; i++) {
        cin >> value;
        arrayFenwick.update(i, value);
    }

    numBlocks = (numUpdates + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int start = 0, left, right, value; start < numUpdates; start += BLOCK_SIZE) {
        int end = min(numUpdates, start + BLOCK_SIZE) - 1;
        int blockIndex = start / BLOCK_SIZE;

        for (int i = start; i <= end; i++) {
            cin >> left >> right >> value;
            leftBound[i] = left;
            rightBound[i] = right;
            updateRange(left, right, value);
            queryFlag[blockIndex][left] ^= 1;
            queryFlag[blockIndex][right + 1] ^= 1;
        }

        for (int i = 1; i <= numElements; i++) {
            queryFlag[blockIndex][i] ^= queryFlag[blockIndex][i - 1];
        }
        for (int i = 1; i <= numElements; i++) {
            queryFlag[blockIndex][i] ^= queryFlag[blockIndex][i - 1];
        }
    }

    while (numQueries--) {
        int queryType, left, right, value;
        cin >> queryType >> left >> right;

        if (queryType == 1) {
            cin >> value;
            left--; right--;
            for (int i = left - 1; i >= left / BLOCK_SIZE * BLOCK_SIZE; i--) 
                updateRange(leftBound[i], rightBound[i], value);
            for (int i = right + 1; i < numUpdates && i < (right / BLOCK_SIZE + 1) * BLOCK_SIZE; i++) 
                updateRange(leftBound[i], rightBound[i], value);
            for (int i = left / BLOCK_SIZE; i <= right / BLOCK_SIZE; i++) 
                blockXor[i] ^= value;
        }

        if (queryType == 2) {
            int result = arrayFenwick.query(left, right);
            result ^= ((left - 1) & 1 ? oddFenwick : evenFenwick).query(left - 1) ^ 
                      (right & 1 ? oddFenwick : evenFenwick).query(right);
            for (int i = 0; i < numBlocks; i++) 
                result ^= blockXor[i] * (queryFlag[i][right] ^ queryFlag[i][left - 1]);
            cout << result << '\n';
        }
    }

    return 0;
}
