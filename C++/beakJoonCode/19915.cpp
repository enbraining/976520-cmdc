#include "split.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int nodeCount, result[MAXN + 10];
pair<int, int> partitionSizeColor[4];
vector<int> originalGraph[MAXN + 10], treeGraph[MAXN + 10], reducedGraph[MAXN + 10];

int subtreeSize[MAXN + 10], rootId[MAXN + 10];

void calculateSubtreeSize(int currentNode, int parent) {
    subtreeSize[currentNode] = 1;
    for (int neighbor : treeGraph[currentNode]) {
        if (neighbor == parent) continue;
        calculateSubtreeSize(neighbor, currentNode);
        subtreeSize[currentNode] += subtreeSize[neighbor];
    }
}

int findCentroid(int currentNode, int parent, int totalSize) {
    for (int neighbor : treeGraph[currentNode]) {
        if (neighbor == parent) continue;
        if (subtreeSize[neighbor] > totalSize / 2) {
            return findCentroid(neighbor, currentNode, totalSize);
        }
    }
    return currentNode;
}

void assignColor(int currentNode, int parent, int color, int& remainingNodes) {
    if (remainingNodes <= 0) return;
    result[currentNode] = color;
    remainingNodes--;
    for (int neighbor : treeGraph[currentNode]) {
        if (neighbor == parent || result[neighbor]) continue;
        assignColor(neighbor, currentNode, color, remainingNodes);
    }
}

void assignRootId(int currentNode, int parent, int root) {
    rootId[currentNode] = root;
    for (int neighbor : treeGraph[currentNode]) {
        if (neighbor == parent) continue;
        assignRootId(neighbor, currentNode, root);
    }
}

bool visited[MAXN + 10];
void buildTreeGraph(int currentNode) {
    visited[currentNode] = true;
    for (int neighbor : originalGraph[currentNode]) {
        if (visited[neighbor]) continue;
        treeGraph[currentNode].push_back(neighbor);
        treeGraph[neighbor].push_back(currentNode);
        buildTreeGraph(neighbor);
    }
}

vector<int> nodes;
void collectNodes(int currentNode, int& count) {
    visited[currentNode] = true;
    count += subtreeSize[currentNode];
    nodes.push_back(currentNode);
    if (count >= partitionSizeColor[1].first) return;
    for (int neighbor : reducedGraph[currentNode]) {
        if (visited[neighbor]) continue;
        collectNodes(neighbor, count);
    }
}

void solve() {
    memset(visited, 0, sizeof(visited));
    buildTreeGraph(1);
    calculateSubtreeSize(1, 1);
    int centroid = findCentroid(1, 1, nodeCount);
    calculateSubtreeSize(centroid, centroid);

    for (int neighbor : treeGraph[centroid]) {
        assignRootId(neighbor, centroid, neighbor);
        if (partitionSizeColor[1].first <= subtreeSize[neighbor]) {
            int remainingNodes = partitionSizeColor[1].first;
            assignColor(neighbor, centroid, partitionSizeColor[1].second, remainingNodes);
            remainingNodes = partitionSizeColor[2].first;
            assignColor(centroid, neighbor, partitionSizeColor[2].second, remainingNodes);
            for (int i = 1; i <= nodeCount; i++) {
                if (result[i] == 0) result[i] = partitionSizeColor[3].second;
            }
            return;
        }
    }

    for (int i = 1; i <= nodeCount; i++) {
        if (i == centroid) continue;
        for (int neighbor : originalGraph[i]) {
            if (neighbor == centroid || rootId[i] == rootId[neighbor]) continue;
            reducedGraph[rootId[i]].push_back(rootId[neighbor]);
        }
    }

    memset(visited, 0, sizeof(visited));
    for (int neighbor : treeGraph[centroid]) {
        if (visited[neighbor]) continue;
        int count = 0;
        collectNodes(neighbor, count);
        if (count < partitionSizeColor[1].first) continue;

        int remainingNodes = partitionSizeColor[1].first;
        for (int node : nodes) {
            assignColor(node, centroid, partitionSizeColor[1].second, remainingNodes);
        }
        assignColor(centroid, centroid, partitionSizeColor[2].second, partitionSizeColor[2].first);
        for (int i = 1; i <= nodeCount; i++) {
            if (result[i] == 0) result[i] = partitionSizeColor[3].second;
        }
        return;
    }
}

vector<int> find_split(int _N, int _A, int _B, int _C, vector<int> _P, vector<int> _Q) {
    nodeCount = _N;
    partitionSizeColor[1] = {_A, 1};
    partitionSizeColor[2] = {_B, 2};
    partitionSizeColor[3] = {_C, 3};
    
    for (int i = 0; i < _P.size(); i++) {
        int u = _P[i] + 1, v = _Q[i] + 1;
        originalGraph[u].push_back(v);
        originalGraph[v].push_back(u);
    }
    
    sort(partitionSizeColor + 1, partitionSizeColor + 4);
    solve();

    vector<int> resultArray(nodeCount);
    for (int i = 1; i <= nodeCount; i++) {
        resultArray[i - 1] = result[i];
    }
    return resultArray;
}
