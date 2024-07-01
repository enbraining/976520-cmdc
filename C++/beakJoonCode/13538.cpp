#include<bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 1 << 19;

struct SegmentTreeNode {
    int leftChild, rightChild, value;
    SegmentTreeNode() : leftChild(0), rightChild(0), value(0) {};
    SegmentTreeNode(int l, int r, int v) : leftChild(l), rightChild(r), value(v) {};
};

int numQueries, numUpdates;
vector<SegmentTreeNode> segmentTree(1 << 20);
int rootIndices[500005];

void initializeSegmentTree() {
    for (int i = 1; i < MAX_SIZE; ++i) {
        segmentTree[i].leftChild = i << 1;
        segmentTree[i].rightChild = i << 1 | 1;
    }
}

void updateSegmentTree(int node, int start, int end, int value, int index) {
    segmentTree[node].value += value;
    if (start != end) {    // not a leaf node
        int mid = (start + end) >> 1;
        int leftChildIndex = segmentTree[node].leftChild, rightChildIndex = segmentTree[node].rightChild;
        if (index <= mid) {
            segmentTree[node].leftChild = segmentTree.size();
            segmentTree.push_back(segmentTree[leftChildIndex]);
            updateSegmentTree(segmentTree[node].leftChild, start, mid, value, index);
        } else {
            segmentTree[node].rightChild = segmentTree.size();
            segmentTree.push_back(segmentTree[rightChildIndex]);
            updateSegmentTree(segmentTree[node].rightChild, mid + 1, end, value, index);
        }
    } else {
        assert(start == index);
    }
}

int xorQuery(int start, int end, int x) {
    int left = 0, right = MAX_SIZE - 1;
    int shift = 18;
    int result = 0;
    while (left != right) {
        int mid = (left + right) >> 1;
        int leftSize = segmentTree[segmentTree[end].leftChild].value - segmentTree[segmentTree[start].leftChild].value;
        int rightSize = segmentTree[segmentTree[end].rightChild].value - segmentTree[segmentTree[start].rightChild].value;
        if (x & (1 << shift)) {
            if (leftSize > 0) {
                start = segmentTree[start].leftChild;
                end = segmentTree[end].leftChild;
                right = mid;
            } else {
                result |= (1 << shift);
                start = segmentTree[start].rightChild;
                end = segmentTree[end].rightChild;
                left = mid + 1;
            }
        } else {
            if (rightSize > 0) {
                result |= (1 << shift);
                start = segmentTree[start].rightChild;
                end = segmentTree[end].rightChild;
                left = mid + 1;
            } else {
                start = segmentTree[start].leftChild;
                end = segmentTree[end].leftChild;
                right = mid;
            }
        }
        --shift;
    }
    assert(left == right);
    assert(shift == -1);
    return result;
}

int sumQuery(int start, int end, int x) {
    int left = 0, right = MAX_SIZE - 1;
    int result = 0;
    while (left != right) {
        int mid = (left + right) >> 1;
        if (x <= mid) {
            start = segmentTree[start].leftChild;
            end = segmentTree[end].leftChild;
            right = mid;
        } else {
            result += segmentTree[segmentTree[end].leftChild].value - segmentTree[segmentTree[start].leftChild].value;
            start = segmentTree[start].rightChild;
            end = segmentTree[end].rightChild;
            left = mid + 1;
        }
    }
    assert(left == right);
    return result + (segmentTree[end].value - segmentTree[start].value);
}

int getKthElement(int start, int end, int k) {
    int left = 0, right = MAX_SIZE - 1;
    while (left != right) {
        int mid = (left + right) >> 1;
        int leftSize = segmentTree[segmentTree[end].leftChild].value - segmentTree[segmentTree[start].leftChild].value;
        if (leftSize >= k) {
            start = segmentTree[start].leftChild;
            end = segmentTree[end].leftChild;
            right = mid;
        } else {
            start = segmentTree[start].rightChild;
            end = segmentTree[end].rightChild;
            k -= leftSize;
            left = mid + 1;
        }
    }
    assert(left == right);
    return left;
}

int main() {
    cin.tie(nullptr); 
    ios::sync_with_stdio(false);
    cin >> numQueries;
    initializeSegmentTree();
    rootIndices[0] = 1;
    for (int i = 0; i < numQueries; ++i) {
        int queryType; 
        cin >> queryType;
        if (queryType == 1) {
            int value; 
            cin >> value;
            rootIndices[++numUpdates] = segmentTree.size();
            segmentTree.push_back(segmentTree[rootIndices[numUpdates - 1]]);
            updateSegmentTree(rootIndices[numUpdates], 0, MAX_SIZE - 1, 1, value);
        } else if (queryType == 2) {
            int left, right, x; 
            cin >> left >> right >> x;
            cout << xorQuery(rootIndices[left - 1], rootIndices[right], x) << '\n';
        } else if (queryType == 3) {
            int numReverts; 
            cin >> numReverts;
            numUpdates -= numReverts;
        } else if (queryType == 4) {
            int left, right, x; 
            cin >> left >> right >> x;
            cout << sumQuery(rootIndices[left - 1], rootIndices[right], x) << '\n';
        } else if (queryType == 5) {
            int left, right, k; 
            cin >> left >> right >> k;
            cout << getKthElement(rootIndices[left - 1], rootIndices[right], k) << '\n';
        } else {
            assert(false);
        }
    }
    return 0;
}
