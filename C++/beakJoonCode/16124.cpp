#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

typedef long long LongLong;
typedef unsigned long long UnsignedLongLong;

#define MODULO 998244353

struct SegmentTreeNode {
    LongLong bitwiseAnd;
    LongLong bitwiseOr;
    UnsignedLongLong value;
    
    SegmentTreeNode(LongLong _bitwiseAnd = 0, LongLong _bitwiseOr = 0, UnsignedLongLong _value = 0)
        : bitwiseAnd(_bitwiseAnd), bitwiseOr(_bitwiseOr), value(_value) {}
};

struct LazyUpdate {
    LongLong fromValue;
    LongLong toValue;
};

struct QueryResult {
    UnsignedLongLong value;
    UnsignedLongLong size;
};

string inputString;
LongLong queryCount, inputArray[1000001];
SegmentTreeNode segmentTree[4000001];
vector<LazyUpdate> lazyUpdates(4000001, {-1, 0});
LongLong powerOfTen[1000001];
LongLong sumOfPowers[1000001];

SegmentTreeNode mergeNodes(SegmentTreeNode leftNode, SegmentTreeNode rightNode, LongLong size) {
    return SegmentTreeNode(
        leftNode.bitwiseAnd & rightNode.bitwiseAnd,
        leftNode.bitwiseOr | rightNode.bitwiseOr,
        ((((leftNode.value % MODULO) * powerOfTen[size / 2]) % MODULO) + (rightNode.value % MODULO)) % MODULO
    );
}

QueryResult mergeQueryResults(QueryResult leftResult, QueryResult rightResult) {
    if (leftResult.value == numeric_limits<UnsignedLongLong>::max()) {
        return rightResult;
    }
    if (rightResult.value == numeric_limits<UnsignedLongLong>::max()) {
        return leftResult;
    }
    return { 
        ((((leftResult.value % MODULO) * powerOfTen[rightResult.size]) % MODULO) + (rightResult.value % MODULO)) % MODULO, 
        leftResult.size + rightResult.size 
    };
}

SegmentTreeNode initializeSegmentTree(int start, int end, int nodeIndex) {
    if (start == end) {
        return segmentTree[nodeIndex] = SegmentTreeNode(1 << inputArray[start], 1 << inputArray[start], (UnsignedLongLong)inputArray[start]);
    }
    int mid = (start + end) >> 1;
    return segmentTree[nodeIndex] = mergeNodes(
        initializeSegmentTree(start, mid, nodeIndex << 1), 
        initializeSegmentTree(mid + 1, end, nodeIndex << 1 | 1), 
        (end - start + 1)
    );
}

void propagateLazyUpdates(int start, int end, int nodeIndex) {
    if (lazyUpdates[nodeIndex].fromValue == -1) {
        return;
    }

    LongLong transformedValue = ((sumOfPowers[end - start + 1] % MODULO) * lazyUpdates[nodeIndex].toValue) % MODULO;
    segmentTree[nodeIndex] = SegmentTreeNode(1 << lazyUpdates[nodeIndex].toValue, 1 << lazyUpdates[nodeIndex].toValue, (UnsignedLongLong)(transformedValue % MODULO));

    if (start != end) {
        lazyUpdates[nodeIndex << 1] = lazyUpdates[nodeIndex];
        lazyUpdates[nodeIndex << 1 | 1] = lazyUpdates[nodeIndex];
    }
    lazyUpdates[nodeIndex] = {-1, 0};
}

void updateSegmentTree(int start, int end, int nodeIndex, int left, int right, int fromValue, int toValue) {
    propagateLazyUpdates(start, end, nodeIndex);
    if (right < start || end < left || !(segmentTree[nodeIndex].bitwiseOr & (1 << fromValue))) {
        return;
    }
    if (left <= start && end <= right && segmentTree[nodeIndex].bitwiseAnd == (1 << fromValue)) {
        lazyUpdates[nodeIndex].fromValue = fromValue;
        lazyUpdates[nodeIndex].toValue = toValue;
        propagateLazyUpdates(start, end, nodeIndex);
        return;
    }
    if (start == end) {
        return;
    }
    int mid = (start + end) >> 1;
    updateSegmentTree(start, mid, nodeIndex << 1, left, right, fromValue, toValue);
    updateSegmentTree(mid + 1, end, nodeIndex << 1 | 1, left, right, fromValue, toValue);
    segmentTree[nodeIndex] = mergeNodes(segmentTree[nodeIndex << 1], segmentTree[nodeIndex << 1 | 1], end - start + 1);
}

QueryResult querySegmentTree(int start, int end, int nodeIndex, int left, int right) {
    propagateLazyUpdates(start, end, nodeIndex);
    if (right < start || end < left) {
        return {numeric_limits<UnsignedLongLong>::max(), 0};
    }
    if (left <= start && end <= right) {
        return {segmentTree[nodeIndex].value, (UnsignedLongLong)(end - start + 1)};
    }
    int mid = (start + end) >> 1;
    return mergeQueryResults(
        querySegmentTree(start, mid, nodeIndex << 1, left, right), 
        querySegmentTree(mid + 1, end, nodeIndex << 1 | 1, left, right)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> inputString >> queryCount;

    powerOfTen[0] = 1;
    for (int i = 1; i < 1000001; i++) {
        powerOfTen[i] = (powerOfTen[i - 1] * 10) % MODULO;
    }
    for (int i = 1; i < 1000001; i++) {
        sumOfPowers[i] = ((sumOfPowers[i - 1] * 10) % MODULO + 1) % MODULO;
    }
    for (int i = 0; i < inputString.length(); i++) {
        inputArray[i + 1] = inputString[i] - '0';
    }

    initializeSegmentTree(1, inputString.length(), 1);

    while (queryCount--) {
        int queryType; 
        cin >> queryType;
        if (queryType == 1) {
            int leftIndex, rightIndex, fromValue, toValue; 
            cin >> leftIndex >> rightIndex >> fromValue >> toValue;
            updateSegmentTree(1, inputString.length(), 1, leftIndex, rightIndex, fromValue, toValue);
        }
        else {
            int leftIndex, rightIndex; 
            cin >> leftIndex >> rightIndex;
            cout << querySegmentTree(1, inputString.length(), 1, leftIndex, rightIndex).value % MODULO << '\n';
        }
    }
}
