#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

#define MAXN 100001

int numPoints, numQueries, treeSize;

struct SegmentTreeNode {
    int leftChild, rightChild, value;
    SegmentTreeNode() : leftChild(0), rightChild(0), value(0) {};
    SegmentTreeNode(int left, int right, int val) : leftChild(left), rightChild(right), value(val) {};
};

void initializeSegmentTree(vector<SegmentTreeNode>& tree) {
    int size = treeSize >> 1;
    for (int i = 1; i <= size; ++i) {
        tree[i].leftChild = i << 1;
        tree[i].rightChild = i << 1 | 1;
    }
}

void updateSegmentTree(vector<SegmentTreeNode>& tree, int node, int start, int end, int value, int index) {
    if (start != end) {
        int mid = (start + end) >> 1;
        int leftChildIndex = tree[node].leftChild, rightChildIndex = tree[node].rightChild;
        if (index <= mid) {
            tree[node].leftChild = tree.size();
            tree.push_back(SegmentTreeNode(tree[leftChildIndex].leftChild, tree[leftChildIndex].rightChild, tree[leftChildIndex].value + value));
            updateSegmentTree(tree, tree[node].leftChild, start, mid, value, index);
        } else {
            tree[node].rightChild = tree.size();
            tree.push_back(SegmentTreeNode(tree[rightChildIndex].leftChild, tree[rightChildIndex].rightChild, tree[rightChildIndex].value + value));
            updateSegmentTree(tree, tree[node].rightChild, mid + 1, end, value, index);
        }
    }
}

int rangeQuery(vector<SegmentTreeNode>& tree, int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node].value;
    }
    int mid = (start + end) >> 1;
    int leftChildIndex = tree[node].leftChild, rightChildIndex = tree[node].rightChild;
    return rangeQuery(tree, leftChildIndex, start, mid, left, right) + rangeQuery(tree, rightChildIndex, mid + 1, end, left, right);
}

int rootIndices[100005];
vector<SegmentTreeNode> segmentTree;

int main() {
    treeSize = 1;
    while (treeSize < MAXN) {
        treeSize <<= 1;
    }
    treeSize <<= 1;

    cin.tie(nullptr); 
    ios::sync_with_stdio(false);

    int testCases; 
    cin >> testCases;

    while (testCases--) {
        cin >> numPoints >> numQueries;

        vector<vector<int>> yCoordinates(MAXN + 1);
        segmentTree = vector<SegmentTreeNode>(treeSize);

        for (int i = 0; i < numPoints; ++i) {
            int x, y;
            cin >> x >> y;
            ++x; 
            ++y;
            yCoordinates[x].push_back(y);
        }

        initializeSegmentTree(segmentTree);
        rootIndices[0] = 1;

        for (int i = 1; i <= MAXN; ++i) {
            rootIndices[i] = segmentTree.size();
            int previousIndex = rootIndices[i - 1];
            segmentTree.push_back(SegmentTreeNode(segmentTree[previousIndex].leftChild, segmentTree[previousIndex].rightChild, segmentTree[previousIndex].value));

            for (auto y : yCoordinates[i]) {
                segmentTree[rootIndices[i]].value += 1;
                updateSegmentTree(segmentTree, rootIndices[i], 1, MAXN, 1, y);
            }
        }

        long long totalSum = 0;
        for (int i = 0; i < numQueries; ++i) {
            int left, right, bottom, top;
            cin >> left >> right >> bottom >> top;
            ++right; 
            ++bottom; 
            ++top;
            totalSum += rangeQuery(segmentTree, rootIndices[right], 1, MAXN, bottom, top) - rangeQuery(segmentTree, rootIndices[left], 1, MAXN, bottom, top);
        }
        cout << totalSum << '\n';
    }

    return 0;
}
