#include <stdio.h>

const int Z = 1 << 21;

int numNodes, numEdges, totalVertices, parent[Z/2], distance[Z/2], numChildren[Z/2], subtreeSize[Z/2], subtreeStart[Z/2], subtreeEnd[Z/2];
long long subtreeSum[Z/2];

struct Node {
    Node() {
        value = index = 0;
    }
    Node(long long value_, int index_) {
        value = value_; index = index_;
    }
    long long value; 
    int index;

    bool operator <(const Node &t) const {
        return value < t.value;
    };

    Node operator +(const Node &t) const {
        if (value < t.value) return t;
        return (*this);
    }
} segmentTree[Z * 2];

void updateSegmentTree(long long value, int index) {
    segmentTree[index + Z] = Node(value, index);
    index = (index + Z) >> 1;
    while (index) {
        segmentTree[index] = segmentTree[index * 2] + segmentTree[index * 2 + 1];
        index >>= 1;
    }
}

Node querySegmentTree(int left, int right) {
    Node result;
    left += Z; right += Z;
    while (left < right) {
        if (left & 1) {
            if (result < segmentTree[left]) result = segmentTree[left];
            left++;
        }
        if (~right & 1) {
            if (result < segmentTree[right]) result = segmentTree[right];
            right--;
        }
        left >>= 1; right >>= 1;
    }
    if (left == right) {
        if (result < segmentTree[left]) result = segmentTree[left];
    }
    return result;
}

long long removeMaxInRange(int start, int end) {
    Node maxNode = querySegmentTree(start, end);
    updateSegmentTree(0, maxNode.index);
    return maxNode.value;
}

int main() {
    scanf("%d %d", &numNodes, &numEdges); 
    totalVertices = numNodes + numEdges;

    for (int i = 2; i <= totalVertices; i++) {
        scanf("%d %d", &parent[i], &distance[i]);
        numChildren[parent[i]]++;
    }

    for (int i = totalVertices; i >= 1; i--) {
        subtreeSize[i]++;
        subtreeSize[parent[i]] += subtreeSize[i];
    }

    subtreeEnd[1] = 1;
    for (int i = 2; i <= totalVertices; i++) {
        subtreeStart[i] = subtreeEnd[parent[i]] + 1;
        subtreeEnd[i] = subtreeStart[i] + 1;
        subtreeEnd[parent[i]] = subtreeStart[i] + subtreeSize[i] * 2 - 1;
    }

    for (int i = totalVertices; i >= 2; i--) {
        int start = subtreeStart[i], end = subtreeEnd[i];
        for (int k = 1; k < numChildren[i]; k++) {
            subtreeSum[i] += removeMaxInRange(start, end);
        }
        long long max1 = removeMaxInRange(start, end);
        long long max2 = removeMaxInRange(start, end);
        updateSegmentTree(distance[i] + max1, start);
        updateSegmentTree(distance[i] + max2, start + 1);
        subtreeSum[i] -= distance[i];
        subtreeSum[parent[i]] += subtreeSum[i];
    }

    for (int k = 0; k < numChildren[1]; k++) {
        subtreeSum[1] += removeMaxInRange(subtreeStart[1], subtreeEnd[1]);
    }
    printf("%lld\n", subtreeSum[1]);

    return 0;
}
