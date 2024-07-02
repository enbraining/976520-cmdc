#include <cstdio>
#include <algorithm>
#include <queue>
#include <functional>
#include <utility>
#include <vector>
using namespace std;

const int MAXIMUM_NUMBER_OF_ELEMENTS = 100002;
const int MAXIMUM_INFINITY = 1e9;

int numberOfElements, numberOfOperations, previousValue, currentValue;
int distanceBetweenElements[MAXIMUM_NUMBER_OF_ELEMENTS];
int leftNeighbor[MAXIMUM_NUMBER_OF_ELEMENTS], rightNeighbor[MAXIMUM_NUMBER_OF_ELEMENTS];
bool isVisited[MAXIMUM_NUMBER_OF_ELEMENTS];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;

int main() {
    scanf("%d%d", &numberOfElements, &numberOfOperations);

    distanceBetweenElements[1] = distanceBetweenElements[numberOfElements + 1] = MAXIMUM_INFINITY;
    rightNeighbor[1] = 2;
    leftNeighbor[numberOfElements + 1] = numberOfElements;
    priorityQueue.push({MAXIMUM_INFINITY, 1});
    priorityQueue.push({MAXIMUM_INFINITY, numberOfElements + 1});
    
    scanf("%d", &previousValue);
    for (int i = 2; i <= numberOfElements; i++) {
        scanf("%d", &currentValue);
        distanceBetweenElements[i] = currentValue - previousValue;
        priorityQueue.push({distanceBetweenElements[i], i});
        leftNeighbor[i] = i - 1;
        rightNeighbor[i] = i + 1;
        previousValue = currentValue;
    }

    int totalDistance = 0;

    while (numberOfOperations--) {
        while (isVisited[priorityQueue.top().second]) {
            priorityQueue.pop();
        }
        
        int minimumDistance = priorityQueue.top().first;
        int index = priorityQueue.top().second;
        priorityQueue.pop();
        
        totalDistance += minimumDistance;
        
        distanceBetweenElements[index] = distanceBetweenElements[leftNeighbor[index]] + distanceBetweenElements[rightNeighbor[index]] - distanceBetweenElements[index];
        priorityQueue.push({distanceBetweenElements[index], index});
        
        isVisited[leftNeighbor[index]] = isVisited[rightNeighbor[index]] = true;
        leftNeighbor[index] = leftNeighbor[leftNeighbor[index]];
        rightNeighbor[index] = rightNeighbor[rightNeighbor[index]];
        rightNeighbor[leftNeighbor[index]] = index;
        leftNeighbor[rightNeighbor[index]] = index;
    }

    printf("%d\n", totalDistance);
    return 0;
}
