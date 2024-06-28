#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const long long INF = 1e14;
const int MAX_ARRAY_SIZE = (1 << 12);

int numberOfPoints;
struct Point {
    int xCoordinate, yCoordinate;
    long long weight;
    bool operator <(Point& otherPoint) const {
        if (xCoordinate == otherPoint.xCoordinate) return yCoordinate < otherPoint.yCoordinate;
        return xCoordinate < otherPoint.xCoordinate;
    }
} points[MAX_ARRAY_SIZE + 5];

long long binaryIndexedTree[MAX_ARRAY_SIZE + 5];
struct SegmentTreeNode {
    int startRange, endRange;
    long long maximumSubarraySum, leftMaximumSum, rightMaximumSum;
} segmentTree[MAX_ARRAY_SIZE * 4 + 5];

void updateBinaryIndexedTree(int index, long long value) { // point update
    for (; index <= numberOfPoints; index += index & -index) {
        binaryIndexedTree[index] += value;
    }
}

long long queryBinaryIndexedTree(int start, int end) { // range sum [start, end]
    long long sumEnd = 0, sumStart = 0;
    for (; end; end -= end & -end) {
        sumEnd += binaryIndexedTree[end];
    }
    for (--start; start; start -= start & -start) {
        sumStart += binaryIndexedTree[start];
    }
    return sumEnd - sumStart;
}

void updateSegmentTree(int currentIndex) {
    int segmentTreeIndex = points[currentIndex].yCoordinate + MAX_ARRAY_SIZE - 1;
    updateBinaryIndexedTree(points[currentIndex].yCoordinate, points[currentIndex].weight);
    long long temporaryValue = (segmentTree[segmentTreeIndex].maximumSubarraySum == -INF ? INF + points[currentIndex].weight : points[currentIndex].weight);
    segmentTree[segmentTreeIndex].maximumSubarraySum += temporaryValue;
    segmentTree[segmentTreeIndex].leftMaximumSum += temporaryValue;
    segmentTree[segmentTreeIndex].rightMaximumSum += temporaryValue;
    segmentTreeIndex /= 2;
    while (segmentTreeIndex) {
        auto& leftChild = segmentTree[segmentTreeIndex * 2];
        auto& rightChild = segmentTree[segmentTreeIndex * 2 + 1];
        auto& currentNode = segmentTree[segmentTreeIndex];
        currentNode.maximumSubarraySum = max({ leftChild.maximumSubarraySum, rightChild.maximumSubarraySum, leftChild.leftMaximumSum + rightChild.rightMaximumSum });
        currentNode.leftMaximumSum = max(rightChild.leftMaximumSum, leftChild.leftMaximumSum + queryBinaryIndexedTree(rightChild.startRange, rightChild.endRange));
        currentNode.rightMaximumSum = max(leftChild.rightMaximumSum, rightChild.rightMaximumSum + queryBinaryIndexedTree(leftChild.startRange, leftChild.endRange));
        segmentTreeIndex /= 2;
    }
}

int main() {
    scanf("%d", &numberOfPoints);
    vector<int> xCoordinates, yCoordinates;
    for (int i = 1; i <= numberOfPoints; i++) {
        scanf("%d %d %lld", &points[i].xCoordinate, &points[i].yCoordinate, &points[i].weight);
        xCoordinates.push_back(points[i].xCoordinate);
        yCoordinates.push_back(points[i].yCoordinate);
    }
    sort(xCoordinates.begin(), xCoordinates.end());
    sort(yCoordinates.begin(), yCoordinates.end());
    for (int i = 1; i <= numberOfPoints; i++) {
        points[i].xCoordinate = lower_bound(xCoordinates.begin(), xCoordinates.end(), points[i].xCoordinate) - xCoordinates.begin() + 1;
        points[i].yCoordinate = lower_bound(yCoordinates.begin(), yCoordinates.end(), points[i].yCoordinate) - yCoordinates.begin() + 1;
    }
    sort(points + 1, points + 1 + numberOfPoints);
    segmentTree[1].startRange = 1, segmentTree[1].endRange = MAX_ARRAY_SIZE;
    for (int i = 2; i <= MAX_ARRAY_SIZE * 4; i++) {
        int start = segmentTree[i / 2].startRange, end = segmentTree[i / 2].endRange;
        if (i % 2) start = (start + end) / 2 + 1;
        else end = (start + end) / 2;
        segmentTree[i] = { start, end, -INF, -INF, -INF };
    }

    long long maximumSum = -INF;
    int resetCheck[3333] = {};
    for (int i = 1; i <= numberOfPoints; i++) {
        if (points[i - 1].xCoordinate != points[i].xCoordinate) resetCheck[i] = 1;
    }
    for (int i = 1; i <= numberOfPoints; i++) {
        if (!resetCheck[i]) continue;
        long long currentMaximum = -INF;
        for (int j = i; j <= numberOfPoints; j++) {
            updateSegmentTree(j);
            if (resetCheck[j + 1] || j == numberOfPoints) currentMaximum = max(currentMaximum, segmentTree[1].maximumSubarraySum);
        }
        maximumSum = max(maximumSum, currentMaximum);
        for (int i = 1; i <= MAX_ARRAY_SIZE * 2; i++) {
            segmentTree[i].maximumSubarraySum = segmentTree[i].leftMaximumSum = segmentTree[i].rightMaximumSum = -INF;
            if (i <= MAX_ARRAY_SIZE) binaryIndexedTree[i] = 0;
        }
    }

    printf("%lld\n", maximumSum);

    return 0;
}
