#include <bits/stdc++.h>
#define SIZE 100010
using namespace std;

struct SegmentTreeNode {
    long long leftMax, rightMax, maxSum, totalSum, fullyZero;
};

long long numberOfElements, numberOfQueries;
long long inputArray[SIZE], differenceArray[SIZE];
SegmentTreeNode segmentTree[SIZE << 2];

SegmentTreeNode mergeNodes(SegmentTreeNode leftNode, SegmentTreeNode rightNode) {
    SegmentTreeNode resultNode;
    resultNode.fullyZero = leftNode.fullyZero & rightNode.fullyZero;
    resultNode.leftMax = leftNode.leftMax;
    if (leftNode.fullyZero) resultNode.leftMax = leftNode.totalSum + rightNode.leftMax;
    resultNode.rightMax = rightNode.rightMax;
    if (rightNode.fullyZero) resultNode.rightMax = leftNode.rightMax + rightNode.totalSum;
    resultNode.totalSum = leftNode.totalSum + rightNode.totalSum;
    resultNode.maxSum = max(max(leftNode.maxSum, rightNode.maxSum), leftNode.rightMax + rightNode.leftMax);
    return resultNode;
}

SegmentTreeNode initializeSegmentTree(long long left, long long right, long long index) {
    if (left == right) {
        if (differenceArray[left] == 0) return segmentTree[index] = {1, 1, 1, 1, 1};
        return segmentTree[index] = {0, 0, 0, 1, 0};
    }
    long long mid = (left + right) >> 1;
    return segmentTree[index] = mergeNodes(initializeSegmentTree(left, mid, index << 1), initializeSegmentTree(mid + 1, right, (index << 1) + 1));
}

SegmentTreeNode updateSegmentTree(long long left, long long right, long long index, long long position, long long value) {
    if (left > position || right < position)
        return segmentTree[index];
    if (left == position && right == position) {
        if (value == 0) return segmentTree[index] = {1, 1, 1, 1, 1};
        return segmentTree[index] = {0, 0, 0, 1, 0};
    }
    long long mid = (left + right) >> 1;
    return segmentTree[index] = mergeNodes(updateSegmentTree(left, mid, index << 1, position, value), updateSegmentTree(mid + 1, right, (index << 1) + 1, position, value));
}

SegmentTreeNode querySegmentTree(long long left, long long right, long long index, long long queryStart, long long queryEnd) {
    if (left > queryEnd || right < queryStart) return {0, 0, 0, 0, 1};
    if (queryStart <= left && right <= queryEnd) return segmentTree[index];
    long long mid = (left + right) >> 1;
    return mergeNodes(querySegmentTree(left, mid, index << 1, queryStart, queryEnd), querySegmentTree(mid + 1, right, (index << 1) + 1, queryStart, queryEnd));
}

void updateDifferenceArray(long long position, long long value) {
    if (differenceArray[position] == 0) updateSegmentTree(2, numberOfElements - 1, 1, position, 1);
    differenceArray[position] += value;
    if (differenceArray[position] == 0) updateSegmentTree(2, numberOfElements - 1, 1, position, 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> numberOfElements;
    
    for (long long i = 1; i <= numberOfElements; i++) cin >> inputArray[i];
    
    for (long long i = 2; i < numberOfElements; i++) differenceArray[i] = inputArray[i - 1] + inputArray[i + 1] - 2 * inputArray[i];
    
    initializeSegmentTree(2, numberOfElements - 1, 1);
    
    cin >> numberOfQueries;
    
    for (; numberOfQueries--;) {
        long long queryType, start, end, value1, value2;
        cin >> queryType >> start >> end;
        
        if (queryType == 1) {
            cin >> value1 >> value2;
            updateDifferenceArray(start - 1, value1);
            updateDifferenceArray(start, -value1 + value2);
            updateDifferenceArray(end, -value1 - (end - start + 1) * value2);
            updateDifferenceArray(end + 1, value1 + (end - start) * value2);
        }
        
        if (queryType == 2) printf("%lld\n", 2 + querySegmentTree(2, numberOfElements - 1, 1, start + 1, end - 1).maxSum);
    }
}
