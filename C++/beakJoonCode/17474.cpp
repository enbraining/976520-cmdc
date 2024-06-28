#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <limits.h>
#include <vector>

#define all(v) v.begin(), v.end()
#define pii pair<int, int>
#define make_unique(v) v.erase(unique(v.begin(), v.end()), v.end())
using namespace std;

typedef struct SegmentTreeNode {
    long long maximumValue, secondMaximumValue, countMaximumValue, totalSum;
} SegmentTreeNode;

vector<long long> arrayInputValues;
vector<SegmentTreeNode> segmentTree;

SegmentTreeNode mergeSegmentTreeNodes(SegmentTreeNode leftNode, SegmentTreeNode rightNode) {
    if (leftNode.maximumValue == rightNode.maximumValue) {
        return { leftNode.maximumValue, max(leftNode.secondMaximumValue, rightNode.secondMaximumValue), leftNode.countMaximumValue + rightNode.countMaximumValue, leftNode.totalSum + rightNode.totalSum };
    }
    else if (leftNode.maximumValue > rightNode.maximumValue) {
        return { leftNode.maximumValue, max(rightNode.maximumValue, leftNode.secondMaximumValue), leftNode.countMaximumValue, leftNode.totalSum + rightNode.totalSum };
    }
    else {
        return { rightNode.maximumValue, max(leftNode.maximumValue, rightNode.secondMaximumValue), rightNode.countMaximumValue, leftNode.totalSum + rightNode.totalSum };
    }
}

SegmentTreeNode initializeSegmentTree(int nodeIndex, int leftBound, int rightBound) {
    if (leftBound == rightBound) {
        return segmentTree[nodeIndex] = { arrayInputValues[leftBound], INT_MIN, 1, arrayInputValues[leftBound] };
    }
    int middle = (leftBound + rightBound) / 2;
    return segmentTree[nodeIndex] = mergeSegmentTreeNodes(initializeSegmentTree(2 * nodeIndex, leftBound, middle), initializeSegmentTree(2 * nodeIndex + 1, middle + 1, rightBound));
}

void propagateLazyUpdates(int nodeIndex, int leftBound, int rightBound) {
    if (leftBound == rightBound) return;
    for (int childIndex = 2 * nodeIndex; childIndex <= 2 * nodeIndex + 1; childIndex++) {
        if (segmentTree[nodeIndex].maximumValue < segmentTree[childIndex].maximumValue) {
            segmentTree[childIndex].totalSum -= segmentTree[childIndex].countMaximumValue * (segmentTree[childIndex].maximumValue - segmentTree[nodeIndex].maximumValue);
            segmentTree[childIndex].maximumValue = segmentTree[nodeIndex].maximumValue;
        }
    }
}

void updateRangeInSegmentTree(int nodeIndex, int leftBound, int rightBound, int queryLeft, int queryRight, long long newValue) {
    propagateLazyUpdates(nodeIndex, leftBound, rightBound);
    if (rightBound < queryLeft || queryRight < leftBound || segmentTree[nodeIndex].maximumValue <= newValue) return;
    if (queryLeft <= leftBound && rightBound <= queryRight && segmentTree[nodeIndex].secondMaximumValue < newValue) {
        segmentTree[nodeIndex].totalSum -= segmentTree[nodeIndex].countMaximumValue * (segmentTree[nodeIndex].maximumValue - newValue);
        segmentTree[nodeIndex].maximumValue = newValue;
        propagateLazyUpdates(nodeIndex, leftBound, rightBound);
        return;
    }
    int middle = (leftBound + rightBound) / 2;
    updateRangeInSegmentTree(2 * nodeIndex, leftBound, middle, queryLeft, queryRight, newValue);
    updateRangeInSegmentTree(2 * nodeIndex + 1, middle + 1, rightBound, queryLeft, queryRight, newValue);
    segmentTree[nodeIndex] = mergeSegmentTreeNodes(segmentTree[2 * nodeIndex], segmentTree[2 * nodeIndex + 1]);
}

long long queryMaximumValueInRange(int nodeIndex, int leftBound, int rightBound, int queryLeft, int queryRight) {
    propagateLazyUpdates(nodeIndex, leftBound, rightBound);
    if (rightBound < queryLeft || queryRight < leftBound) return INT_MIN;
    if (queryLeft <= leftBound && rightBound <= queryRight) return segmentTree[nodeIndex].maximumValue;
    int middle = (leftBound + rightBound) / 2;
    return max(queryMaximumValueInRange(2 * nodeIndex, leftBound, middle, queryLeft, queryRight), queryMaximumValueInRange(2 * nodeIndex + 1, middle + 1, rightBound, queryLeft, queryRight));
}

long long querySumInRange(int nodeIndex, int leftBound, int rightBound, int queryLeft, int queryRight) {
    propagateLazyUpdates(nodeIndex, leftBound, rightBound);
    if (rightBound < queryLeft || queryRight < leftBound) return 0;
    if (queryLeft <= leftBound && rightBound <= queryRight) return segmentTree[nodeIndex].totalSum;
    int middle = (leftBound + rightBound) / 2;
    return querySumInRange(2 * nodeIndex, leftBound, middle, queryLeft, queryRight) + querySumInRange(2 * nodeIndex + 1, middle + 1, rightBound, queryLeft, queryRight);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numberOfElements, numberOfQueries, queryType, leftIndex, rightIndex;
    long long newValue;
    cin >> numberOfElements;
    arrayInputValues.resize(numberOfElements);
    segmentTree.resize(4 * numberOfElements);
    for (int i = 0; i < numberOfElements; i++) cin >> arrayInputValues[i];
    initializeSegmentTree(1, 0, numberOfElements - 1);
    cin >> numberOfQueries;
    for (int i = 0; i < numberOfQueries; i++) {
        cin >> queryType;
        if (queryType == 1) {
            cin >> leftIndex >> rightIndex >> newValue;
            updateRangeInSegmentTree(1, 0, numberOfElements - 1, leftIndex - 1, rightIndex - 1, newValue);
        }
        else if (queryType == 2) {
            cin >> leftIndex >> rightIndex;
            cout << queryMaximumValueInRange(1, 0, numberOfElements - 1, leftIndex - 1, rightIndex - 1) << '\n';
        }
        else {
            cin >> leftIndex >> rightIndex;
            cout << querySumInRange(1, 0, numberOfElements - 1, leftIndex - 1, rightIndex - 1) << '\n';
        }
    }
}
