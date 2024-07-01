#include <bits/stdc++.h>
using namespace std;

#define INF 987654321
#define SWAP(a, b) { int t = a; a = b; b = t; }
#define MAX_NODES 100010

int numNodes, numQueries;
vector<int> adjacencyList[MAX_NODES];

int depth[MAX_NODES], ancestor[MAX_NODES][25];
int maxLevel = (int)floor(log2(MAX_NODES));

void depthFirstSearch(int currentNode, int parent) {
    depth[currentNode] = depth[parent] + 1;
    ancestor[currentNode][0] = parent;

    for (int i = 1; i <= maxLevel; i++) {
        int previousAncestor = ancestor[currentNode][i - 1];
        ancestor[currentNode][i] = ancestor[previousAncestor][i - 1];
    }

    for (int nextNode : adjacencyList[currentNode]) {
        if (nextNode == parent) {
            continue;
        }
        depthFirstSearch(nextNode, currentNode);
    }
}

int findLowestCommonAncestor(int node1, int node2) {
    if (depth[node1] != depth[node2]) {
        if (depth[node1] > depth[node2]) {
            SWAP(node1, node2);
        }
        for (int i = maxLevel; i >= 0; i--) {
            if (depth[node1] <= depth[ancestor[node2][i]]) {
                node2 = ancestor[node2][i];
            }
        }
    }
    int lca = node1;
    if (node1 != node2) {
        for (int i = maxLevel; i >= 0; i--) {
            if (ancestor[node1][i] != ancestor[node2][i]) {
                node1 = ancestor[node1][i];
                node2 = ancestor[node2][i];
            }
            lca = ancestor[node1][i];
        }
    }
    return lca;
}

int calculateDistance(int node1, int node2) {
    if (node1 == -1 || node2 == -1) {
        return -1;
    }
    int lca = findLowestCommonAncestor(node1, node2);
    return depth[node1] + depth[node2] - 2 * depth[lca] + 1;
}

int findCenterNode(int node1, int node2) {
    if (node1 > node2) {
        SWAP(node1, node2);
    }
    int lca = findLowestCommonAncestor(node1, node2);
    int totalDistance = depth[node1] + depth[node2] - 2 * depth[lca] + 1;
    if ((totalDistance % 2) == 0) {
        return -1;
    }
    int midpoint = (totalDistance + 1) / 2;
    int kthNode = 0;

    if (depth[node1] - depth[lca] + 1 >= midpoint) {
        midpoint--;
        kthNode = node1;
        for (int i = maxLevel; i >= 0; i--) {
            if ((1 << i) <= midpoint) {
                midpoint -= (1 << i);
                kthNode = ancestor[kthNode][i];
            }
        }
    } else {
        kthNode = node2;
        midpoint = depth[node1] + depth[node2] - 2 * depth[lca] - (midpoint - 1);
        for (int i = maxLevel; i >= 0; i--) {
            if ((1 << i) <= midpoint) {
                midpoint -= (1 << i);
                kthNode = ancestor[kthNode][i];
            }
        }
    }
    return kthNode;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> numNodes;
    for (int i = 1; i < numNodes; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        adjacencyList[node1].push_back(node2);
        adjacencyList[node2].push_back(node1);
    }

    depth[0] = -1;
    depthFirstSearch(1, 0);

    cin >> numQueries;
    while (numQueries--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == b && b == c) {
            cout << a << '\n';
        } else if (a == b || b == c || c == a) {
            int minValue = min({a, b, c});
            int maxValue = max({a, b, c});
            cout << findCenterNode(minValue, maxValue) << '\n';
        } else {
            int abCenter = findCenterNode(a, b);
            int bcCenter = findCenterNode(b, c);
            int caCenter = findCenterNode(c, a);
            if (calculateDistance(a, abCenter) == calculateDistance(c, abCenter)) {
                cout << abCenter << '\n';
            } else if (calculateDistance(b, bcCenter) == calculateDistance(a, bcCenter)) {
                cout << bcCenter << '\n';
            } else if (calculateDistance(c, caCenter) == calculateDistance(b, caCenter)) {
                cout << caCenter << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
}
