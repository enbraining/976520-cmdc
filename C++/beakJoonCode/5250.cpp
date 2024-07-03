#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9 + 7;

template<size_t SIZE = 1 << 11>
struct SegmentTree {
    vector<int> tree, lazy;
    SegmentTree() : tree(SIZE << 1, INF), lazy(SIZE << 1, INF) {}

    void push(int node, int leftBound, int rightBound) {
        if (node < SIZE) {
            for (const int nextNode : { node << 1, node << 1 | 1 }) {
                lazy[nextNode] = min(lazy[nextNode], lazy[node]);
            }
        }
        tree[node] = min(tree[node], lazy[node]);
        lazy[node] = INF;
    }

    void update(int left, int right, int value, int node = 1, int leftBound = 1, int rightBound = SIZE) {
        push(node, leftBound, rightBound);
        if (right < leftBound || rightBound < left) return;
        if (left <= leftBound && rightBound <= right) {
            lazy[node] = min(lazy[node], value);
            push(node, leftBound, rightBound);
            return;
        }
        int mid = (leftBound + rightBound) >> 1;
        update(left, right, value, node << 1, leftBound, mid);
        update(left, right, value, node << 1 | 1, mid + 1, rightBound);
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }

    int query(int left, int right, int node = 1, int leftBound = 1, int rightBound = SIZE) {
        push(node, leftBound, rightBound);
        if (right < leftBound || rightBound < left) return INF;
        if (left <= leftBound && rightBound <= right) return tree[node];
        int mid = (leftBound + rightBound) >> 1;
        return min(query(left, right, node << 1, leftBound, mid), query(left, right, node << 1 | 1, mid + 1, rightBound));
    }
};

int numNodes, numEdges, startNode, endNode, numVerticesInPath;
int vertices[2001], vertexIndexInPath[2001];
int startParent[2001], endParent[2001];
int startDist[2001], endDist[2001];
vector<pair<int, int>> adjacencyList[2001];

void runDijkstra(int distanceArray[], int start) {
    memset(distanceArray + 1, 0x3f, numNodes << 2);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;
    priorityQueue.push({ distanceArray[start] = 0, start });
    while (!priorityQueue.empty()) {
        auto [currentDistance, currentNode] = priorityQueue.top();
        priorityQueue.pop();
        if (distanceArray[currentNode] != currentDistance) continue;
        for (const auto& [nextNode, edgeCost] : adjacencyList[currentNode]) {
            if (distanceArray[nextNode] > currentDistance + edgeCost) {
                priorityQueue.push({ distanceArray[nextNode] = currentDistance + edgeCost, nextNode });
            }
        }
    }
}

void runDFS(int parentArray[], int distanceArray[], int currentNode, int previousNode, int targetNode) {
    if (parentArray[currentNode]) return;
    if (vertexIndexInPath[currentNode]) targetNode = currentNode;
    parentArray[currentNode] = targetNode;
    for (const auto& [nextNode, edgeCost] : adjacencyList[currentNode]) {
        if (nextNode == previousNode || distanceArray[currentNode] + edgeCost != distanceArray[nextNode]) continue;
        if (!vertexIndexInPath[currentNode] && vertexIndexInPath[nextNode]) continue;
        runDFS(parentArray, distanceArray, nextNode, currentNode, targetNode);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> numNodes >> numEdges >> startNode >> endNode;
    for (int i = 0; i < numEdges; i++) {
        int nodeA, nodeB, edgeCost;
        cin >> nodeA >> nodeB >> edgeCost;
        adjacencyList[nodeA].push_back({ nodeB, edgeCost });
        adjacencyList[nodeB].push_back({ nodeA, edgeCost });
    }
    cin >> numVerticesInPath;
    for (int i = 1; i <= numVerticesInPath; i++) {
        cin >> vertices[i];
        vertexIndexInPath[vertices[i]] = i;
    }

    runDijkstra(startDist, startNode);
    runDijkstra(endDist, endNode);
    runDFS(startParent, startDist, vertices[1], -1, vertices[1]);
    runDFS(endParent, endDist, vertices[numVerticesInPath], -1, vertices[numVerticesInPath]);

    SegmentTree<1 << 11> segTree;
    for (int i = 1; i <= numNodes; i++) {
        for (const auto& [j, edgeCost] : adjacencyList[i]) {
            if (vertexIndexInPath[i] && vertexIndexInPath[j] && abs(vertexIndexInPath[i] - vertexIndexInPath[j]) <= 1) continue;
            const int startVertexIndex = vertexIndexInPath[startParent[i]];
            const int endVertexIndex = vertexIndexInPath[endParent[j]];
            segTree.update(startVertexIndex, endVertexIndex - 1, startDist[i] + edgeCost + endDist[j]);
        }
    }

    for (int i = 1; i < numVerticesInPath; i++) {
        const int answer = segTree.query(i, i);
        cout << (answer == INF ? -1 : answer) << '\n';
    }
}
