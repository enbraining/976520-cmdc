#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

int numPoints, numSegments;
long long coordinatesX[1 << 18];
long long coordinatesY[1 << 18];

pair<long long, long long> segmentTree[1 << 19];
int treeBias = 1 << 18;

void initializeSegmentTree() {
    for (int i = 0; i < numPoints; i++) 
        segmentTree[i | treeBias] = {coordinatesY[i], i};
    for (int i = treeBias - 1; i; i--) 
        segmentTree[i] = min(segmentTree[i << 1], segmentTree[i << 1 | 1]);
}

int rangeMinimumQuery(int left, int right) {
    left |= treeBias;
    right |= treeBias;
    pair<long long, long long> result(1e18, 1e18);
    while (left <= right) {
        if (left & 1) result = min(result, segmentTree[left++]);
        if (~right & 1) result = min(result, segmentTree[right--]);
        left >>= 1;
        right >>= 1;
    }
    return result.y;
}

priority_queue<long long> maxHeap;
int currentHeight;

long long calculateArea(int start, int end) {
    if (start >= end) {
        return 0;
    }
    int minimumIndex = rangeMinimumQuery(start, end - 1);
    int previousHeight = currentHeight;
    currentHeight = coordinatesY[minimumIndex];
    long long leftArea = calculateArea(start, minimumIndex);
    long long rightArea = calculateArea(minimumIndex + 1, end);
    maxHeap.push(min(leftArea, rightArea));
    currentHeight = previousHeight;
    return max(leftArea, rightArea) + (coordinatesX[end] - coordinatesX[start]) * (coordinatesY[minimumIndex] - currentHeight);
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cin >> numPoints;
    numPoints >>= 1;
    for (int i = 0; i < numPoints; i++) {
        cin >> coordinatesX[i] >> coordinatesY[i];
        cin >> coordinatesX[i] >> coordinatesY[i];
    }
    cin >> numSegments;
    initializeSegmentTree();
    long long totalArea = calculateArea(0, numPoints - 1);
    maxHeap.push(totalArea);
    long long finalResult = 0;
    for (int i = 0; i < numSegments; i++) {
        if (!maxHeap.size()) break;
        finalResult += maxHeap.top(); 
        maxHeap.pop();
    }
    cout << finalResult;
}
