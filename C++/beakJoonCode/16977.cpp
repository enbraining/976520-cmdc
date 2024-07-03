#include <bits/stdc++.h>
using namespace std;

const int MAX_NODE_COUNT = 1e5;
int numElements, numQueries;
vector<long long> elementValues;
vector<pair<long long, int>> sortedElements;

struct SegmentTreeNode {
    int leftSum = 0, rightSum = 0, maxSum = 0;
    int leftChild = 0, rightChild = 0, size = 0;
};

int nodeCount;
vector<SegmentTreeNode> segmentTree(40 * MAX_NODE_COUNT);
vector<int> segmentTreeRoots(MAX_NODE_COUNT + 5);

void initializeSegmentTree(int node, int start, int end) {
    if (start == end) {
        segmentTree[node].size = 1;
    } else {
        int mid = (start + end) >> 1;
        int leftChild = node << 1;
        int rightChild = (node << 1) | 1;
        segmentTree[node].leftChild = leftChild;
        segmentTree[node].rightChild = rightChild;
        initializeSegmentTree(leftChild, start, mid);
        initializeSegmentTree(rightChild, mid + 1, end);
        segmentTree[node].size = segmentTree[leftChild].size + segmentTree[rightChild].size;
    }
}

void combineNodes(const SegmentTreeNode &leftNode, const SegmentTreeNode &rightNode, SegmentTreeNode &resultNode) {
    if (leftNode.maxSum == -1) {
        resultNode = rightNode;
        return;
    } else if (rightNode.maxSum == -1) {
        resultNode = leftNode;
        return;
    }
    resultNode.size = leftNode.size + rightNode.size;
    resultNode.leftSum = leftNode.leftSum;
    if (leftNode.leftSum && leftNode.leftSum == leftNode.size) {
        resultNode.leftSum += rightNode.leftSum;
    }
    resultNode.rightSum = rightNode.rightSum;
    if (rightNode.rightSum && rightNode.rightSum == rightNode.size) {
        resultNode.rightSum += leftNode.rightSum;
    }
    resultNode.maxSum = max(leftNode.maxSum, rightNode.maxSum);
    resultNode.maxSum = max(resultNode.maxSum, max(resultNode.leftSum, resultNode.rightSum));
    resultNode.maxSum = max(resultNode.maxSum, leftNode.rightSum + rightNode.leftSum);
}

void updateSegmentTree(int node, int start, int end, int index) {
    if (start == end) {
        segmentTree[node].leftSum = segmentTree[node].rightSum = segmentTree[node].maxSum = 1;
    } else {
        int mid = (start + end) >> 1;
        int leftChild = segmentTree[node].leftChild;
        int rightChild = segmentTree[node].rightChild;
        if (index <= mid) {
            segmentTree[node].leftChild = nodeCount;
            segmentTree[nodeCount++] = segmentTree[leftChild];
            updateSegmentTree(segmentTree[node].leftChild, start, mid, index);
        } else {
            segmentTree[node].rightChild = nodeCount;
            segmentTree[nodeCount++] = segmentTree[rightChild];
            updateSegmentTree(segmentTree[node].rightChild, mid + 1, end, index);
        }
        combineNodes(segmentTree[segmentTree[node].leftChild], segmentTree[segmentTree[node].rightChild], segmentTree[node]);
    }
}

SegmentTreeNode querySegmentTree(int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        SegmentTreeNode result;
        result.maxSum = -1;
        return result;
    }
    if (left <= start && end <= right) {
        return segmentTree[node];
    }
    int mid = (start + end) >> 1;
    int leftChild = segmentTree[node].leftChild;
    int rightChild = segmentTree[node].rightChild;
    SegmentTreeNode leftResult = querySegmentTree(leftChild, start, mid, left, right);
    SegmentTreeNode rightResult = querySegmentTree(rightChild, mid + 1, end, left, right);
    SegmentTreeNode result;
    combineNodes(leftResult, rightResult, result);
    return result;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> numElements;

    for (int i = 1; i <= numElements; ++i) {
        long long value;
        cin >> value;
        sortedElements.emplace_back(value, i);
        elementValues.push_back(value);
    }

    sort(sortedElements.begin(), sortedElements.end(), greater<>());
    elementValues.push_back(0);
    sort(elementValues.begin(), elementValues.end());
    elementValues.erase(unique(elementValues.begin(), elementValues.end()), elementValues.end());

    for (auto &element : sortedElements) {
        element.first = lower_bound(elementValues.begin(), elementValues.end(), element.first) - elementValues.begin();
    }

    nodeCount = 1;
    while (nodeCount < numElements) {
        nodeCount <<= 1;
    }
    nodeCount <<= 1;

    int totalSize = nodeCount;
    initializeSegmentTree(1, 1, numElements);

    segmentTreeRoots[0] = 1;
    int currentIndex = sortedElements[0].first;
    segmentTreeRoots[currentIndex] = segmentTreeRoots[0];

    for (auto &element : sortedElements) {
        if (element.first != currentIndex) {
            --currentIndex;
            segmentTreeRoots[currentIndex] = segmentTreeRoots[currentIndex + 1];
        }
        segmentTree[nodeCount] = segmentTree[segmentTreeRoots[currentIndex]];
        segmentTreeRoots[currentIndex] = nodeCount++;
        updateSegmentTree(segmentTreeRoots[currentIndex], 1, numElements, element.second);
    }

    cin >> numQueries;

    for (int i = 0; i < numQueries; ++i) {
        int left, right, threshold;
        cin >> left >> right >> threshold;

        int low = 1, high = elementValues.size() - 1;
        int answer = 0;

        while (low <= high) {
            int mid = (low + high) >> 1;
            int queryResult = querySegmentTree(segmentTreeRoots[mid], 1, numElements, left, right).maxSum;

            if (queryResult >= threshold) {
                answer = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << elementValues[answer] << '\n';
    }

    return 0;
}
