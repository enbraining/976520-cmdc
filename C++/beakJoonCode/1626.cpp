#include <bits/stdc++.h>
using namespace std;

int vertexCount, edgeCount;
vector<pair<int, int>> adjacencyList[100005];

int parent[100005][31];
int maxEdgeInPath[100005][31];
int secondMaxEdgeInPath[100005][31];
int depth[100005];
bool visited[100005];
vector<pair<int, int>> mstAdjacencyList[100005];

int disjointSet[100005];
vector<pair<pair<int, int>, int>> mstEdges;
vector<pair<pair<int, int>, int>> nonMstEdges;
long long mstTotalWeight;

int Find(int node) {
    if (disjointSet[node]) {
        return (disjointSet[node] = Find(disjointSet[node]));
    } else {
        return node;
    }
}

void Union(int nodeA, int nodeB) {
    int setA = Find(nodeA);
    int setB = Find(nodeB);
    if (setA == setB) return;
    disjointSet[setA] = setB;
}

void DFS(int currentNode) {
    visited[currentNode] = true;
    for (auto edge : mstAdjacencyList[currentNode]) {
        if (!visited[edge.first]) {
            parent[edge.first][0] = currentNode;
            depth[edge.first] = depth[currentNode] + 1;
            maxEdgeInPath[edge.first][0] = edge.second;
            secondMaxEdgeInPath[edge.first][0] = edge.second;
            DFS(edge.first);
        }
    }
}

pair<int, int> LCA(int nodeA, int nodeB) {
    set<int, greater<int>> edgeSet;

    if (depth[nodeA] > depth[nodeB]) swap(nodeA, nodeB);
    for (int i = 30; i >= 0; i--) {
        if (depth[nodeB] - depth[nodeA] >= (1 << i)) {
            edgeSet.insert(maxEdgeInPath[nodeB][i]);
            edgeSet.insert(secondMaxEdgeInPath[nodeB][i]);
            nodeB = parent[nodeB][i];
        }
    }
    if (nodeA == nodeB) {
        int firstMax = *edgeSet.begin(), secondMax = *edgeSet.begin();
        edgeSet.erase(edgeSet.begin());
        if (!edgeSet.empty()) secondMax = *edgeSet.begin();
        return {firstMax, secondMax};
    }

    for (int i = 30; i >= 0; i--) {
        if (parent[nodeA][i] != parent[nodeB][i]) {
            edgeSet.insert(maxEdgeInPath[nodeA][i]);
            edgeSet.insert(secondMaxEdgeInPath[nodeA][i]);
            edgeSet.insert(maxEdgeInPath[nodeB][i]);
            edgeSet.insert(secondMaxEdgeInPath[nodeB][i]);
            nodeA = parent[nodeA][i];
            nodeB = parent[nodeB][i];
        }
    }

    edgeSet.insert(maxEdgeInPath[nodeA][0]);
    edgeSet.insert(secondMaxEdgeInPath[nodeA][0]);
    edgeSet.insert(maxEdgeInPath[nodeB][0]);
    edgeSet.insert(secondMaxEdgeInPath[nodeB][0]);

    int firstMax = *edgeSet.begin(), secondMax = *edgeSet.begin();
    edgeSet.erase(edgeSet.begin());
    if (!edgeSet.empty()) secondMax = *edgeSet.begin();
    return {firstMax, secondMax};
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    cin >> vertexCount >> edgeCount;

    if (vertexCount == 1) {
        cout << -1;
        return 0;
    }

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> edgeQueue;

    for (int i = 0; i < edgeCount; i++) {
        int vertexA, vertexB, weight;
        cin >> vertexA >> vertexB >> weight;

        if (vertexA == vertexB) continue;

        adjacencyList[vertexA].push_back({vertexB, weight});
        adjacencyList[vertexB].push_back({vertexA, weight});
        edgeQueue.push({weight, {vertexA, vertexB}});
    }

    while (!edgeQueue.empty()) {
        pair<int, pair<int, int>> edge = edgeQueue.top(); 
        edgeQueue.pop();

        if (Find(edge.second.first) != Find(edge.second.second)) {
            Union(edge.second.first, edge.second.second);
            mstEdges.push_back({edge.second, edge.first});
            mstAdjacencyList[edge.second.first].push_back({edge.second.second, edge.first});
            mstAdjacencyList[edge.second.second].push_back({edge.second.first, edge.first});
            mstTotalWeight += edge.first;
        } else {
            nonMstEdges.push_back({edge.second, edge.first});
        }
    }

    if (mstEdges.size() < vertexCount - 1) {
        cout << -1;
        return 0;
    }

    DFS(1);

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= vertexCount; j++) {
            parent[j][i] = parent[parent[j][i - 1]][i - 1];
            maxEdgeInPath[j][i] = max(maxEdgeInPath[j][i - 1], maxEdgeInPath[parent[j][i - 1]][i - 1]);

            set<int, greater<int>> tempSet;
            tempSet.insert(maxEdgeInPath[j][i - 1]);
            tempSet.insert(maxEdgeInPath[parent[j][i - 1]][i - 1]);
            tempSet.insert(secondMaxEdgeInPath[j][i - 1]);
            tempSet.insert(secondMaxEdgeInPath[parent[j][i - 1]][i - 1]);

            if (tempSet.size() == 1) {
                secondMaxEdgeInPath[j][i] = *tempSet.begin();
            } else {
                tempSet.erase(tempSet.begin());
                secondMaxEdgeInPath[j][i] = *tempSet.begin();
            }
        }
    }

    long long result = LLONG_MAX;

    for (auto edge : nonMstEdges) {
        pair<int, int> lcaResult = LCA(edge.first.first, edge.first.second);
        long long newMstValue = mstTotalWeight + edge.second;

        if (newMstValue - lcaResult.first > mstTotalWeight) {
            result = min(result, newMstValue - lcaResult.first);
        } else if (newMstValue - lcaResult.second > mstTotalWeight) {
            result = min(result, newMstValue - lcaResult.second);
        }
    }

    if (result == mstTotalWeight || result == LLONG_MAX) {
        cout << -1;
    } else {
        cout << result;
    }

    return 0;
}
