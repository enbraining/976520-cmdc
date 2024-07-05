#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
bool nodeColor[100100];

struct SegmentTreeNode {
    int minBlack, minWhite, countBlack, countWhite;
    SegmentTreeNode() {}
    SegmentTreeNode(int _minBlack, int _minWhite, int _countBlack, int _countWhite) 
        : minBlack(_minBlack), minWhite(_minWhite), countBlack(_countBlack), countWhite(_countWhite) {};
};

struct SegmentTree {
    int orTree[200200], andTree[200200];
    int size;
    void updateNode(int index) {
        index += size - 1;
        orTree[index] ^= 1;
        andTree[index] ^= 1;
        for (; index > 1; index >>= 1) {
            orTree[index >> 1] = orTree[index] | orTree[index ^ 1];
            andTree[index >> 1] = andTree[index] & andTree[index ^ 1];
        }
    }
    int queryOr(int left, int right) {
        int result = 0;
        left--;
        for (left += size, right += size; left < right; left >>= 1, right >>= 1) {
            if (left & 1) result |= orTree[left++];
            if (right & 1) result |= orTree[--right];
        }
        return result;
    }
    int queryAnd(int left, int right) {
        int result = 1;
        left--;
        for (left += size, right += size; left < right; left >>= 1, right >>= 1) {
            if (left & 1) result &= andTree[left++];
            if (right & 1) result &= andTree[--right];
        }
        return result;
    }
} hldSegmentTree;

struct LazySegmentTree {
    vector<SegmentTreeNode> array, tree;
    vector<pair<int, int>> lazy;
    int size;
    SegmentTreeNode combineNodes(SegmentTreeNode a, SegmentTreeNode b) {
        SegmentTreeNode result = a;
        if (result.minBlack > b.minBlack) {
            result.minBlack = b.minBlack;
            result.countBlack = b.countBlack;
        }
        else if (result.minBlack == b.minBlack) {
            result.countBlack += b.countBlack;
        }
        if (result.minWhite > b.minWhite) {
            result.minWhite = b.minWhite;
            result.countWhite = b.countWhite;
        }
        else if (result.minWhite == b.minWhite) {
            result.countWhite += b.countWhite;
        }
        return result;
    }
    void initialize(int index = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;
        if (left == right) {
            tree[index] = array[left];
            return;
        }
        int mid = (left + right) >> 1;
        initialize(index << 1, left, mid);
        initialize(index << 1 | 1, mid + 1, right);
        tree[index] = combineNodes(tree[index << 1], tree[index << 1 | 1]);
    }
    void propagate(int index, int left, int right) {
        tree[index].minBlack += lazy[index].first;
        tree[index].minWhite += lazy[index].second;
        if (left != right) {
            lazy[index << 1].first += lazy[index].first;
            lazy[index << 1].second += lazy[index].second;
            lazy[index << 1 | 1].first += lazy[index].first;
            lazy[index << 1 | 1].second += lazy[index].second;
        }
        lazy[index] = make_pair(0, 0);
    }
    void updateRange(int index, int left, int right, int start, int end, int value1, int value2) {
        propagate(index, left, right);
        if (right < start || end < left) return;
        if (start <= left && right <= end) {
            lazy[index].first += value1;
            lazy[index].second += value2;
            propagate(index, left, right);
            return;
        }
        int mid = (left + right) >> 1;
        updateRange(index << 1, left, mid, start, end, value1, value2);
        updateRange(index << 1 | 1, mid + 1, right, start, end, value1, value2);
        tree[index] = combineNodes(tree[index << 1], tree[index << 1 | 1]);
    }
    SegmentTreeNode queryRange(int index, int left, int right, int start, int end) {
        propagate(index, left, right);
        if (right < start || end < left) return SegmentTreeNode(1e9, 1e9, 0, 0);
        if (start <= left && right <= end) return tree[index];
        int mid = (left + right) >> 1;
        return combineNodes(queryRange(index << 1, left, mid, start, end),
                            queryRange(index << 1 | 1, mid + 1, right, start, end));
    }
} segmentTrees[100100];

vector<int> adjacencyList[100100], hldGraph[100100];
pair<int, int> subtreeRange[100100][20];
bool centroidVisited[100100];
int subtreeSize[100100], hldSize[100100], centroidParent[100100], hldParent[100100];
int chainTop[100100], dfsOrder[100100], hldDepth[100100], depthArray[100100][20];
int centroidDepth[100100], numNodes, segmentTimer;

int calculateSubtreeSize(int node, int parent = -1) {
    subtreeSize[node] = 1;
    for (int neighbor : adjacencyList[node]) {
        if (!centroidVisited[neighbor] && neighbor != parent) {
            subtreeSize[node] += calculateSubtreeSize(neighbor, node);
        }
    }
    return subtreeSize[node];
}

int findCentroid(int node, int parent, int capacity) {
    for (int neighbor : adjacencyList[node]) {
        if (!centroidVisited[neighbor] && neighbor != parent && (subtreeSize[neighbor] << 1) > capacity) {
            return findCentroid(neighbor, node, capacity);
        }
    }
    return node;
}

void initializeSubtree(int node, int parent, int root, int index, int depth, int dfsDepth) {
    depthArray[node][depth] = root;
    segmentTrees[index].array[segmentTimer] = SegmentTreeNode(dfsDepth, 0, 1, 1);
    subtreeRange[node][depth].first = segmentTimer + 1;
    segmentTimer++;
    for (int neighbor : adjacencyList[node]) {
        if (!centroidVisited[neighbor] && neighbor != parent) {
            if (root == -1) {
                initializeSubtree(neighbor, node, neighbor, index, depth, dfsDepth + 1);
            } else {
                initializeSubtree(neighbor, node, root, index, depth, dfsDepth + 1);
            }
        }
    }
    subtreeRange[node][depth].second = segmentTimer;
}

void buildCentroidTree(int node = 1, int parent = -1, int capacity = numNodes, int depth = 0) {
    calculateSubtreeSize(node, parent);
    int centroid = findCentroid(node, parent, capacity);
    centroidDepth[centroid] = depth;
    segmentTrees[centroid].tree.resize(capacity << 2);
    segmentTrees[centroid].lazy.resize(capacity << 2);
    segmentTrees[centroid].array.resize(capacity);
    segmentTrees[centroid].size = capacity;
    segmentTimer = 0;
    initializeSubtree(centroid, -1, -1, centroid, depth, 1);
    segmentTrees[centroid].initialize();
    centroidVisited[centroid] = true;
    if (parent != -1) centroidParent[centroid] = parent;
    for (int neighbor : adjacencyList[centroid]) {
        if (!centroidVisited[neighbor]) {
            buildCentroidTree(neighbor, centroid, subtreeSize[neighbor], depth + 1);
        }
    }
}

bool hldVisited[100100];
void dfsHLD(int node = 1) {
    hldVisited[node] = true;
    for (int neighbor : adjacencyList[node]) {
        if (!hldVisited[neighbor]) {
            hldGraph[node].push_back(neighbor);
            dfsHLD(neighbor);
        }
    }
}

void dfsHLD1(int node = 1) {
    hldSize[node] = 1;
    for (int& neighbor : hldGraph[node]) {
        hldParent[neighbor] = node;
        hldDepth[neighbor] = hldDepth[node] + 1;
        dfsHLD1(neighbor);
        hldSize[node] += hldSize[neighbor];
        if (hldSize[neighbor] > hldSize[hldGraph[node][0]]) {
            swap(neighbor, hldGraph[node][0]);
        }
    }
}

int dfsOrderCounter;
void dfsHLD2(int node = 1) {
    dfsOrder[node] = ++dfsOrderCounter;
    for (int neighbor : hldGraph[node]) {
        chainTop[neighbor] = (neighbor == hldGraph[node][0]) ? chainTop[node] : neighbor;
        dfsHLD2(neighbor);
    }
}

int queryHLD(int x, int y) {
    int orResult = 0, andResult = 1;
    while (chainTop[x] != chainTop[y]) {
        if (hldDepth[chainTop[x]] < hldDepth[chainTop[y]]) {
            swap(x, y);
        }
        int start = chainTop[x];
        orResult |= hldSegmentTree.queryOr(dfsOrder[start], dfsOrder[x]);
        andResult &= hldSegmentTree.queryAnd(dfsOrder[start], dfsOrder[x]);
        x = hldParent[start];
    }
    if (hldDepth[x] > hldDepth[y]) {
        swap(x, y);
    }
    orResult |= hldSegmentTree.queryOr(dfsOrder[x], dfsOrder[y]);
    andResult &= hldSegmentTree.queryAnd(dfsOrder[x], dfsOrder[y]);
    if (orResult ^ andResult) return -1;
    return orResult;
}

void updateNodeColor(int node) {
    hldSegmentTree.updateNode(dfsOrder[node]);
    for (int i = node; i; i = centroidParent[i]) {
        if (nodeColor[node]) {
            segmentTrees[i].updateRange(1, 1, segmentTrees[i].size, 
                                        subtreeRange[node][centroidDepth[i]].first, subtreeRange[node][centroidDepth[i]].second, 
                                        1, -1);
        } else {
            segmentTrees[i].updateRange(1, 1, segmentTrees[i].size, 
                                        subtreeRange[node][centroidDepth[i]].first, subtreeRange[node][centroidDepth[i]].second, 
                                        -1, 1);
        }
    }
    nodeColor[node] = !nodeColor[node];
}

int queryNode(int node) {
    int result = 0;
    for (int i = node; i; i = centroidParent[i]) {
        int temp = queryHLD(node, i);
        if (temp == -1) continue;
        if (!temp) {
            result += segmentTrees[i].tree[1].countWhite;
            if (depthArray[node][centroidDepth[i]] > 0) {
                SegmentTreeNode tempNode = segmentTrees[i].queryRange(1, 1, segmentTrees[i].size, 
                                                                      subtreeRange[depthArray[node][centroidDepth[i]]][centroidDepth[i]].first, 
                                                                      subtreeRange[depthArray[node][centroidDepth[i]]][centroidDepth[i]].second);
                if (!tempNode.minWhite) result -= tempNode.countWhite;
            }
        } else {
            result += segmentTrees[i].tree[1].countBlack;
            if (depthArray[node][centroidDepth[i]] > 0) {
                SegmentTreeNode tempNode = segmentTrees[i].queryRange(1, 1, segmentTrees[i].size, 
                                                                      subtreeRange[depthArray[node][centroidDepth[i]]][centroidDepth[i]].first, 
                                                                      subtreeRange[depthArray[node][centroidDepth[i]]][centroidDepth[i]].second);
                if (!tempNode.minBlack) result -= tempNode.countBlack;
            }
        }
    }
    return result;
}

int main() {
    scanf("%d", &numNodes);
    for (int i = 0; i < numNodes - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adjacencyList[a].push_back(b);
        adjacencyList[b].push_back(a);
    }
    hldSegmentTree.size = numNodes;
    buildCentroidTree();
    dfsHLD();
    dfsHLD1();
    dfsHLD2();
    int numQueries;
    scanf("%d", &numQueries);
    while (numQueries--) {
        int queryType, node;
        scanf("%d %d", &queryType, &node);
        if (queryType & 1) {
            updateNodeColor(node);
        } else {
            printf("%d\n", queryNode(node));
        }
    }
    return 0;
}
