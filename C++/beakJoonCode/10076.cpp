#include<bits/stdc++.h>
using namespace std;
const int MAX_NODES = 1e5;

struct SegmentTreeNode {
    int left, right; 
    long long sum;
    int count;
    SegmentTreeNode() : count(0), sum(0) {};
};

vector<long long> distinctValues;
vector<int> inputArray;
vector<int> rootIndices(MAX_NODES + 1);
int numElements, startIdx, maxDiff;
vector<SegmentTreeNode> segmentTree(MAX_NODES * 20);
long long maxSumResult;
int currentNodeCount;

void initializeSegmentTree() {
    currentNodeCount = distinctValues.size() * 2;
    for(int i = 1; i < distinctValues.size(); ++i) {
        segmentTree[i].count = segmentTree[i].sum = 0;
        segmentTree[i].left = i << 1;
        segmentTree[i].right = i << 1 | 1;
    }
}

void updateSegmentTree(int node, int start, int end, int index, long long value) {
    segmentTree[node].count += value;
    segmentTree[node].sum += value * distinctValues[index];
    if(start != end) {
        int mid = (start + end) >> 1;
        int leftChild = segmentTree[node].left, rightChild = segmentTree[node].right;
        if(index <= mid) {
            segmentTree[currentNodeCount] = segmentTree[leftChild];
            segmentTree[node].left = currentNodeCount++;
            updateSegmentTree(segmentTree[node].left, start, mid, index, value);
        } else {
            segmentTree[currentNodeCount] = segmentTree[rightChild];
            segmentTree[node].right = currentNodeCount++;
            updateSegmentTree(segmentTree[node].right, mid + 1, end, index, value);
        }
    }
}

long long querySegmentTree(int start, int end, int k) {
    int left = 0, right = distinctValues.size() - 1;
    long long result = 0;
    while(left != right) {
        int mid = (left + right) >> 1;
        int leftSize = segmentTree[segmentTree[end].left].count - segmentTree[segmentTree[start].left].count;
        long long leftSum = segmentTree[segmentTree[end].left].sum - segmentTree[segmentTree[start].left].sum;
        if(leftSize >= k) {
            start = segmentTree[start].left;
            end = segmentTree[end].left;
            right = mid;
        } else {
            result += leftSum;
            k -= leftSize;
            start = segmentTree[start].right;
            end = segmentTree[end].right;
            left = mid + 1;
        }
    }
    assert(left == right);
    result += distinctValues[left] * min(k, segmentTree[end].count - segmentTree[start].count);
    return result;
}

void buildSegmentTree() {
    rootIndices[0] = 1;
    for(int i = 1; i <= numElements; ++i) {
        rootIndices[i] = currentNodeCount;
        segmentTree[currentNodeCount++] = segmentTree[rootIndices[i - 1]];
        updateSegmentTree(rootIndices[i], 0, distinctValues.size() - 1, inputArray[i], 1);
    }
}

void divideAndConquer(int start, int end, int optStart, int optEnd) {
    if(start > end) return;
    long long localMax = 0;
    int optimalMid = optStart;
    int mid = (start + end) >> 1;
    for(int i = optStart; i <= optEnd; ++i) {
        int k = max(0, maxDiff - startIdx - i + 2 * mid);
        k = min(k, i - mid + 1);
        long long temp = querySegmentTree(rootIndices[mid - 1], rootIndices[i], k);
        if(temp > localMax) {
            localMax = temp;
            optimalMid = i;
        }
    }
    maxSumResult = max(localMax, maxSumResult);
    divideAndConquer(start, mid - 1, optStart, optimalMid);
    divideAndConquer(mid + 1, end, optimalMid, optEnd);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> numElements >> startIdx >> maxDiff;
    ++startIdx;
    inputArray.resize(numElements + 1);
    for(int i = 1; i <= numElements; ++i) {
        cin >> inputArray[i];
        distinctValues.push_back(inputArray[i]);
    }
    sort(distinctValues.begin(), distinctValues.end(), greater<long long>());
    distinctValues.erase(unique(distinctValues.begin(), distinctValues.end()), distinctValues.end());
    for(int i = 1; i <= numElements; ++i) {
        inputArray[i] = lower_bound(distinctValues.begin(), distinctValues.end(), inputArray[i], greater<long long>()) - distinctValues.begin();
    }
    initializeSegmentTree();
    buildSegmentTree();
    divideAndConquer(1, startIdx, startIdx, numElements);
    reverse(inputArray.begin() + 1, inputArray.begin() + numElements + 1);
    startIdx = numElements - startIdx + 1;
    initializeSegmentTree();
    buildSegmentTree();
    divideAndConquer(1, startIdx, startIdx, numElements);
    cout << maxSumResult << '\n';
    return 0;
}
