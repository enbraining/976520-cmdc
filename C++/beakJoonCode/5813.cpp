#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef pair<int, int> PairInt;

const int MODULO = 1e9;
const int DIRECTION_X[] = { 1, -1, 0, 0 };
const int DIRECTION_Y[] = { 0, 0, 1, -1 };

int subtreeSize[999999];
int visited[999999];
int totalNodes;
map<PairInt, int> coordinatesMap;
set<int> graph[999999];

void depthFirstSearch(int currentNode, int previousNode, long long& totalDistance) {
    for (auto nextNode : graph[currentNode]) {
        if (nextNode != previousNode && !visited[nextNode]) {
            visited[nextNode] = 1;
            depthFirstSearch(nextNode, currentNode, totalDistance);
            subtreeSize[currentNode] += subtreeSize[nextNode];
        }
    }
    long long contribution = (long long)subtreeSize[currentNode] * (long long)(totalNodes - subtreeSize[currentNode]);
    contribution %= MODULO;
    totalDistance += contribution;
    totalDistance %= MODULO;
}

long long calculateDistanceSum() {
    long long totalDistance = 0;
    visited[1] = 1;
    depthFirstSearch(1, 0, totalDistance);
    return totalDistance;
}

void constructGraph(vector<PairInt>& coordinates) {
    sort(coordinates.begin() + 1, coordinates.end());
    memset(subtreeSize, 0, sizeof subtreeSize);
    memset(visited, 0, sizeof visited);
    for (int i = 0; i <= totalNodes; i++) {
        graph[i].clear();
    }
    coordinatesMap.clear();

    int nodeCounter = 1;
    coordinatesMap[coordinates[1]] = nodeCounter;
    subtreeSize[nodeCounter]++;
    for (int i = 2; i <= totalNodes; i++) {
        if (coordinates[i - 1].x == coordinates[i].x && coordinates[i - 1].y + 1 == coordinates[i].y) {
            coordinatesMap[coordinates[i]] = nodeCounter;
        } else {
            coordinatesMap[coordinates[i]] = ++nodeCounter;
        }
        subtreeSize[nodeCounter]++;
    }

    for (int i = 1; i <= totalNodes; i++) {
        int x = coordinates[i].x;
        int y = coordinates[i].y;
        int currentNode = coordinatesMap[coordinates[i]];
        for (int direction = 0; direction < 4; direction++) {
            int adjacentX = x + DIRECTION_X[direction];
            int adjacentY = y + DIRECTION_Y[direction];
            int adjacentNode = coordinatesMap[{adjacentX, adjacentY}];
            if (adjacentNode && currentNode != adjacentNode) {
                graph[currentNode].insert(adjacentNode);
            }
        }
    }
}

int calculateTotalDistanceSum(int nodeCount, int* xCoordinates, int* yCoordinates) {
    totalNodes = nodeCount;
    long long totalDistance = 0;
    vector<PairInt> coordinates(nodeCount + 1);
    for (int i = 0; i < nodeCount; i++) {
        coordinates[i + 1] = { xCoordinates[i], yCoordinates[i] };
    }
    constructGraph(coordinates);
    totalDistance += calculateDistanceSum() % MODULO;

    for (int i = 0; i < nodeCount; i++) {
        coordinates[i + 1] = { yCoordinates[i], xCoordinates[i] };
    }
    constructGraph(coordinates);
    totalDistance += calculateDistanceSum() % MODULO;
    totalDistance %= MODULO;
    return (int)totalDistance;
}

int main() {
    int nodeCount;
    cin >> nodeCount;

    int xCoordinates[nodeCount], yCoordinates[nodeCount];
    for (int i = 0; i < nodeCount; ++i) {
        cin >> xCoordinates[i] >> yCoordinates[i];
    }

    int result = calculateTotalDistanceSum(nodeCount, xCoordinates, yCoordinates);
    cout << result << endl;

    return 0;
}
