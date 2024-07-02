#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

int nodeCount, queryCount;
vector<pair<long long, long long>> adjacencyList[999999];
int parent[22][999999], depth[999999];
long long distanceFromRoot[999999];
int inTime[999999], outTime[999999], timeCounter;

void depthFirstSearch(int currentNode = 1, int parentNode = -1) {
    inTime[currentNode] = ++timeCounter;
    for (auto edge : adjacencyList[currentNode]) {
        if (edge.x != parentNode) {
            parent[0][timeCounter + 1] = inTime[currentNode];
            depth[timeCounter + 1] = depth[inTime[currentNode]] + 1;
            distanceFromRoot[timeCounter + 1] = distanceFromRoot[inTime[currentNode]] + edge.y;
            depthFirstSearch(edge.x, currentNode);
        }
    }
    outTime[inTime[currentNode]] = timeCounter;
}

int lowestCommonAncestor(int nodeU, int nodeV) {
    if (depth[nodeU] < depth[nodeV]) {
        swap(nodeU, nodeV);
    }
    int depthDifference = depth[nodeU] - depth[nodeV];
    for (int i = 0; depthDifference; i++) {
        if (depthDifference & 1) {
            nodeU = parent[i][nodeU];
        }
        depthDifference >>= 1;
    }
    if (nodeU == nodeV) {
        return nodeU;
    }
    for (int i = 21; ~i; i--) {
        if (parent[i][nodeU] != parent[i][nodeV]) {
            nodeU = parent[i][nodeU];
            nodeV = parent[i][nodeV];
        }
    }
    return parent[0][nodeU];
}

int color[505050];
vector<int> vertexList;
long long minimumDistance = 1e18;

pair<long long, long long> findMinimumDistances(int currentNode) {
    long long distanceToSetS = color[currentNode] == 1 ? 0 : 1e18;
    long long distanceToSetT = color[currentNode] == 2 ? 0 : 1e18;
    color[currentNode] = 0;

    while (timeCounter < vertexList.size() && vertexList[timeCounter] <= outTime[currentNode]) {
        int nextNode = vertexList[timeCounter];
        timeCounter++;
        auto distances = findMinimumDistances(nextNode);
        distanceToSetS = min(distanceToSetS, distances.x + distanceFromRoot[nextNode] - distanceFromRoot[currentNode]);
        distanceToSetT = min(distanceToSetT, distances.y + distanceFromRoot[nextNode] - distanceFromRoot[currentNode]);
    }

    minimumDistance = min(minimumDistance, distanceToSetS + distanceToSetT);
    return {distanceToSetS, distanceToSetT};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> nodeCount >> queryCount;
    for (int i = 1; i < nodeCount; i++) {
        int startNode, endNode, edgeWeight;
        cin >> startNode >> endNode >> edgeWeight;
        startNode++;
        endNode++;
        adjacencyList[startNode].emplace_back(endNode, edgeWeight);
        adjacencyList[endNode].emplace_back(startNode, edgeWeight);
    }

    depthFirstSearch();
    for (int i = 1; i < 22; i++) {
        for (int j = 1; j <= nodeCount; j++) {
            parent[i][j] = parent[i - 1][parent[i - 1][j]];
        }
    }

    while (queryCount--) {
        int setSizeS, setSizeT;
        cin >> setSizeS >> setSizeT;
        vertexList.clear();
        for (int i = 0; i < setSizeS; i++) {
            int node;
            cin >> node;
            node++;
            vertexList.push_back(inTime[node]);
            color[inTime[node]] = 1;
        }
        for (int i = 0; i < setSizeT; i++) {
            int node;
            cin >> node;
            node++;
            vertexList.push_back(inTime[node]);
            color[inTime[node]] = 2;
        }

        compress(vertexList);
        vector<int> lowestCommonAncestors;
        for (int i = 1; i < vertexList.size(); i++) {
            lowestCommonAncestors.push_back(lowestCommonAncestor(vertexList[i - 1], vertexList[i]));
        }
        for (auto lcaNode : lowestCommonAncestors) {
            vertexList.push_back(lcaNode);
        }

        compress(vertexList);
        minimumDistance = 1e18;
        timeCounter = 0;
        findMinimumDistances(1);
        cout << minimumDistance << "\n";
    }
    return 0;
}
