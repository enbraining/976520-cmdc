#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegmentTreeNode {
    int totalSum, segmentSum;
    int leftMinus, leftPlus;
    int rightMinus, rightPlus;
    int length;
    SegmentTreeNode() 
        : totalSum(0), segmentSum(0), leftMinus(0), leftPlus(0), rightMinus(0), rightPlus(0), length(0) {};
    
    SegmentTreeNode operator+(SegmentTreeNode rhs) {
        SegmentTreeNode resultNode;
        resultNode.totalSum = totalSum + rhs.totalSum;
        resultNode.segmentSum = segmentSum + rhs.segmentSum;
        resultNode.length = length + rhs.length;
        if (rightMinus != length && rhs.leftPlus != rhs.length) {
            resultNode.segmentSum += (rightMinus + rhs.leftPlus) / 2;
        }
        if (rightPlus != length && rhs.leftMinus != rhs.length) {
            resultNode.segmentSum += (rightPlus + rhs.leftMinus) / 2;
        }
        resultNode.leftMinus = leftMinus;
        if (leftMinus == length) {
            if (length % 2 == 0) resultNode.leftMinus += rhs.leftMinus;
            else resultNode.leftMinus += rhs.leftPlus;
        }
        resultNode.leftPlus = leftPlus;
        if (leftPlus == length) {
            if (length % 2 == 0) resultNode.leftPlus += rhs.leftPlus;
            else resultNode.leftPlus += rhs.leftMinus;
        }
        resultNode.rightMinus = rhs.rightMinus;
        if (rhs.rightMinus == rhs.length) {
            if (rhs.length % 2 == 0) resultNode.rightMinus += rightMinus;
            else resultNode.rightMinus += rightPlus;
        }
        resultNode.rightPlus = rhs.rightPlus;
        if (rhs.rightPlus == rhs.length) {
            if (rhs.length % 2 == 0) resultNode.rightPlus += rightPlus;
            else resultNode.rightPlus += rightMinus;
        }
        return resultNode;
    }
};

SegmentTreeNode segmentTree[1 << 20];
vector<int> arrayElements(400005);
vector<vector<int>> indices(200005);
int numberOfElements, numberOfQueries;

void updateSegmentTree(int node, int start, int end, int index, int value) {
    if (index < start || index > end) return;
    if (start == index && index == end) {
        SegmentTreeNode& currentNode = segmentTree[node];
        if (value == 0) {
            currentNode.totalSum = 0;
            currentNode.segmentSum = 0;
            currentNode.leftMinus = 0;
            currentNode.leftPlus = 0;
            currentNode.rightMinus = 0;
            currentNode.rightPlus = 0;
            currentNode.length = 1;
        } else if (value > 0) {
            currentNode.totalSum = 1;
            currentNode.segmentSum = 0;
            currentNode.leftMinus = currentNode.rightMinus = 0;
            currentNode.leftPlus = currentNode.rightPlus = 1;
            currentNode.length = 1;
        } else {
            currentNode.totalSum = 1;
            currentNode.segmentSum = 0;
            currentNode.leftMinus = currentNode.rightMinus = 1;
            currentNode.leftPlus = currentNode.rightPlus = 0;
            currentNode.length = 1;
        }
        return;
    }
    int mid = (start + end) >> 1;
    int leftChild = node << 1;
    int rightChild = node << 1 | 1;
    updateSegmentTree(leftChild, start, mid, index, value);
    updateSegmentTree(rightChild, mid + 1, end, index, value);
    segmentTree[node] = segmentTree[leftChild] + segmentTree[rightChild];
}

SegmentTreeNode querySegmentTree(int node, int start, int end, int left, int right) {
    if (end < left || start > right) return SegmentTreeNode();
    if (left <= start && end <= right) return segmentTree[node];
    int mid = (start + end) >> 1;
    int leftChild = node << 1;
    int rightChild = node << 1 | 1;
    SegmentTreeNode leftResult = querySegmentTree(leftChild, start, mid, left, right);
    SegmentTreeNode rightResult = querySegmentTree(rightChild, mid + 1, end, left, right);
    SegmentTreeNode combinedResult = leftResult + rightResult;
    return combinedResult;
}

void initializeSegmentTree(int node, int start, int end) {
    if (start == end) {
        int value = arrayElements[start] != 1;
        SegmentTreeNode& currentNode = segmentTree[node];
        if (value == 0) {
            currentNode.totalSum = 0;
            currentNode.segmentSum = 0;
            currentNode.leftMinus = 0;
            currentNode.leftPlus = 0;
            currentNode.rightMinus = 0;
            currentNode.rightPlus = 0;
            currentNode.length = 1;
        } else if (value > 0) {
            currentNode.totalSum = 1;
            currentNode.segmentSum = 0;
            currentNode.leftMinus = currentNode.rightMinus = 0;
            currentNode.leftPlus = currentNode.rightPlus = 1;
            currentNode.length = 1;
        } else {
            currentNode.totalSum = 1;
            currentNode.segmentSum = 0;
            currentNode.leftMinus = currentNode.rightMinus = 1;
            currentNode.leftPlus = currentNode.rightPlus = 0;
            currentNode.length = 1;
        }
        return;
    }
    int mid = (start + end) >> 1;
    int leftChild = node << 1;
    int rightChild = node << 1 | 1;
    initializeSegmentTree(leftChild, start, mid);
    initializeSegmentTree(rightChild, mid + 1, end);
    segmentTree[node] = segmentTree[leftChild] + segmentTree[rightChild];
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> numberOfElements >> numberOfQueries;
    for (int i = 1; i <= numberOfElements; ++i) {
        cin >> arrayElements[i];
        arrayElements[numberOfElements + i] = arrayElements[i];
    }
    for (int i = 1; i <= 2 * numberOfElements; ++i) {
        indices[arrayElements[i]].push_back(i);
    }
    initializeSegmentTree(1, 1, 2 * numberOfElements);
    vector<int> result(numberOfQueries + 1);
    for (int i = 1; i <= numberOfQueries; ++i) {
        if (indices[i].empty()) {
            result[i] = -1;
        } else {
            int left = indices[i].front();
            int right = left + numberOfElements;
            auto queryResult = querySegmentTree(1, 1, 2 * numberOfElements, left, right);
            result[i] = queryResult.totalSum + queryResult.segmentSum;
        }
        for (int x : indices[i]) {
            updateSegmentTree(1, 1, 2 * numberOfElements, x, -1);
        }
        for (int x : indices[i + 1]) {
            updateSegmentTree(1, 1, 2 * numberOfElements, x, 0);
        }
    }
    for (int i = 1; i <= numberOfQueries; ++i) {
        cout << result[i] << " \n"[i == numberOfQueries];
    }
    return 0;
}
