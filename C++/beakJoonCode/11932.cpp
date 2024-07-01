#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
int NumberOfNodes, NumberOfQueries;
int Depth[MAXN], SparseTable[20][MAXN];
vector<vector<int>> Graph(MAXN);
vector<int> UniqueValues;

void DepthFirstSearch(int currentNode, int parentNode, int currentDepth) {
    Depth[currentNode] = currentDepth;
    for(const int &neighbor : Graph[currentNode]) {
        if(neighbor == parentNode) continue;
        DepthFirstSearch(neighbor, currentNode, currentDepth + 1);
        SparseTable[0][neighbor] = currentNode;
    }
}

int FindLowestCommonAncestor(int nodeU, int nodeV) {
    if(Depth[nodeU] > Depth[nodeV]) swap(nodeU, nodeV);
    int depthDifference = Depth[nodeV] - Depth[nodeU];
    int index = 0;
    while(depthDifference) {
        if(depthDifference & 1) nodeV = SparseTable[index][nodeV];
        depthDifference >>= 1; ++index;
    }
    if(nodeU == nodeV) return nodeU;
    for(int i = 19; i >= 0; --i) {
        if(SparseTable[i][nodeU] != SparseTable[i][nodeV]) {
            nodeU = SparseTable[i][nodeU];
            nodeV = SparseTable[i][nodeV];
        }
    }
    return SparseTable[0][nodeU];
}

struct SegmentTreeNode {
    int leftChild, rightChild, value;
    SegmentTreeNode() : leftChild(0), rightChild(0), value(0) {};
    SegmentTreeNode(int left, int right, int val) : leftChild(left), rightChild(right), value(val) {};
};

vector<int> NodeValues, ValueIndices;
vector<SegmentTreeNode> SegmentTree(200005);
vector<int> RootNodes(100005);
int ParentNodes[100005];

void InitializeSegmentTree() {
    for(int i = 1; i < UniqueValues.size(); ++i) {
        SegmentTree[i].leftChild = i << 1;
        SegmentTree[i].rightChild = i << 1 | 1;
    }
}

void UpdateSegmentTree(int currentNode, int start, int end, int value, int index) {
    SegmentTree[currentNode].value += value;
    if(start != end) {
        int mid = (start + end) >> 1;
        int leftNode = SegmentTree[currentNode].leftChild, rightNode = SegmentTree[currentNode].rightChild;
        if(index <= mid) {
            SegmentTree[currentNode].leftChild = SegmentTree.size();
            SegmentTree.push_back(SegmentTree[leftNode]);
            UpdateSegmentTree(SegmentTree[currentNode].leftChild, start, mid, value, index);
        }
        else {
            SegmentTree[currentNode].rightChild = SegmentTree.size();
            SegmentTree.push_back(SegmentTree[rightNode]);
            UpdateSegmentTree(SegmentTree[currentNode].rightChild, mid + 1, end, value, index);
        }
    }
}

void BuildPersistentSegmentTree(int currentNode, int parentNode) {
    ParentNodes[currentNode] = parentNode;
    RootNodes[currentNode] = SegmentTree.size(); 
    SegmentTree.push_back(SegmentTree[RootNodes[parentNode]]);
    UpdateSegmentTree(RootNodes[currentNode], 0, UniqueValues.size() - 1, 1, ValueIndices[currentNode]);
    for(auto nextNode : Graph[currentNode]) {
        if(nextNode == parentNode) continue;
        BuildPersistentSegmentTree(nextNode, currentNode);
    }
}

int QuerySegmentTree(int start, int end, int lowestCommonAncestor, int parentOfLCA, int k) {
    int left = 0, right = UniqueValues.size() - 1;
    while(left != right) {
        int mid = (left + right) >> 1;
        int leftSize = SegmentTree[SegmentTree[end].leftChild].value + SegmentTree[SegmentTree[start].leftChild].value - SegmentTree[SegmentTree[lowestCommonAncestor].leftChild].value - SegmentTree[SegmentTree[parentOfLCA].leftChild].value;
        if(leftSize >= k) {
            start = SegmentTree[start].leftChild; 
            end = SegmentTree[end].leftChild;
            lowestCommonAncestor = SegmentTree[lowestCommonAncestor].leftChild; 
            parentOfLCA = SegmentTree[parentOfLCA].leftChild;
            right = mid;
        }
        else {
            k -= leftSize;
            start = SegmentTree[start].rightChild; 
            end = SegmentTree[end].rightChild;
            lowestCommonAncestor = SegmentTree[lowestCommonAncestor].rightChild; 
            parentOfLCA = SegmentTree[parentOfLCA].rightChild;
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> NumberOfNodes >> NumberOfQueries;
    NodeValues.resize(NumberOfNodes + 1);
    for(int i = 1; i <= NumberOfNodes; ++i) {
        cin >> NodeValues[i]; 
        UniqueValues.push_back(NodeValues[i]);
    }
    sort(UniqueValues.begin(), UniqueValues.end());
    UniqueValues.erase(unique(UniqueValues.begin(), UniqueValues.end()), UniqueValues.end());
    ValueIndices.resize(NumberOfNodes + 1);
    for(int i = 1; i <= NumberOfNodes; ++i) 
        ValueIndices[i] = lower_bound(UniqueValues.begin(), UniqueValues.end(), NodeValues[i]) - UniqueValues.begin();
    for(int i = 1; i < NumberOfNodes; ++i) {
        int nodeU, nodeV; 
        cin >> nodeU >> nodeV;
        Graph[nodeU].push_back(nodeV);
        Graph[nodeV].push_back(nodeU);
    }
    DepthFirstSearch(1, 0, 0);
    for(int i = 1; i < 20; ++i) 
        for(int j = 1; j <= NumberOfNodes; ++j) 
            SparseTable[i][j] = SparseTable[i-1][SparseTable[i-1][j]];
    InitializeSegmentTree();
    RootNodes[0] = 1;
    BuildPersistentSegmentTree(1, 0);
    for(int i = 0; i < NumberOfQueries; ++i) {
        int nodeX, nodeY, k; 
        cin >> nodeX >> nodeY >> k;
        if(nodeX == nodeY) {
            cout << NodeValues[nodeX] << '\n';
            continue;
        }
        int lowestCommonAncestor = FindLowestCommonAncestor(nodeX, nodeY);
        cout << UniqueValues[QuerySegmentTree(RootNodes[nodeX], RootNodes[nodeY], RootNodes[lowestCommonAncestor], RootNodes[ParentNodes[lowestCommonAncestor]], k)] << '\n';
    }
    return 0;
}
