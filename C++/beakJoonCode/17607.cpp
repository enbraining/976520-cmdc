#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int numberOfNodes, numberOfQueries;
int arrayOfValues[100005];

struct SplayTreeNode {
    SplayTreeNode *leftChild, *rightChild, *parent;
    ll subtreeSize;
    ll leftSegmentSum, rightSegmentSum, maxSegmentSum;
    ll nodeValue;
    bool inversionFlag;
    SplayTreeNode() : leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
} *root, *nodePointers[100005];

void propagateInversion(SplayTreeNode *currentNode) {
    if (!currentNode->inversionFlag) return;
    swap(currentNode->leftChild, currentNode->rightChild);
    swap(currentNode->leftSegmentSum, currentNode->rightSegmentSum);
    if (currentNode->leftChild) currentNode->leftChild->inversionFlag = !currentNode->leftChild->inversionFlag;
    if (currentNode->rightChild) currentNode->rightChild->inversionFlag = !currentNode->rightChild->inversionFlag;
    currentNode->inversionFlag = false;
}

void updateNode(SplayTreeNode *currentNode) {
    propagateInversion(currentNode);
    currentNode->subtreeSize = 1;
    if (currentNode->nodeValue) {
        currentNode->maxSegmentSum = currentNode->leftSegmentSum = currentNode->rightSegmentSum = 1;
    } else {
        currentNode->maxSegmentSum = currentNode->leftSegmentSum = currentNode->rightSegmentSum = 0;
    }
    if (currentNode->leftChild && currentNode->rightChild) {
        propagateInversion(currentNode->leftChild);
        propagateInversion(currentNode->rightChild);
        currentNode->subtreeSize += currentNode->leftChild->subtreeSize + currentNode->rightChild->subtreeSize;
        currentNode->leftSegmentSum = currentNode->leftChild->leftSegmentSum;
        if (currentNode->leftChild->subtreeSize == currentNode->leftChild->leftSegmentSum && currentNode->nodeValue) {
            currentNode->leftSegmentSum += currentNode->rightChild->leftSegmentSum + currentNode->nodeValue;
        }
        currentNode->rightSegmentSum = currentNode->rightChild->rightSegmentSum;
        if (currentNode->rightChild->subtreeSize == currentNode->rightChild->rightSegmentSum && currentNode->nodeValue) {
            currentNode->rightSegmentSum += currentNode->leftChild->rightSegmentSum + currentNode->nodeValue;
        }
        currentNode->maxSegmentSum = max(currentNode->rightChild->maxSegmentSum, currentNode->leftChild->maxSegmentSum);
        if (currentNode->nodeValue) {
            currentNode->maxSegmentSum = max(currentNode->maxSegmentSum, currentNode->leftChild->rightSegmentSum + currentNode->rightChild->leftSegmentSum + 1);
        }
        currentNode->maxSegmentSum = max({currentNode->maxSegmentSum, currentNode->leftSegmentSum, currentNode->rightSegmentSum});
        currentNode->maxSegmentSum = max({currentNode->maxSegmentSum, currentNode->leftChild->rightSegmentSum + currentNode->nodeValue, currentNode->rightChild->leftSegmentSum + currentNode->nodeValue});
    } else if (currentNode->leftChild) {
        propagateInversion(currentNode->leftChild);
        currentNode->subtreeSize += currentNode->leftChild->subtreeSize;
        currentNode->leftSegmentSum = currentNode->leftChild->leftSegmentSum;
        if (currentNode->leftChild->leftSegmentSum == currentNode->leftChild->subtreeSize) {
            currentNode->leftSegmentSum = currentNode->leftChild->subtreeSize + currentNode->nodeValue;
        }
        currentNode->rightSegmentSum = currentNode->nodeValue ? currentNode->nodeValue + currentNode->leftChild->rightSegmentSum : 0;
        currentNode->maxSegmentSum = max(currentNode->leftChild->maxSegmentSum, currentNode->nodeValue);
        currentNode->maxSegmentSum = max(currentNode->maxSegmentSum, currentNode->leftChild->rightSegmentSum + currentNode->nodeValue);
        currentNode->maxSegmentSum = max({currentNode->maxSegmentSum, currentNode->leftSegmentSum, currentNode->rightSegmentSum});
    } else if (currentNode->rightChild) {
        propagateInversion(currentNode->rightChild);
        currentNode->subtreeSize += currentNode->rightChild->subtreeSize;
        currentNode->rightSegmentSum = currentNode->rightChild->rightSegmentSum;
        if (currentNode->rightChild->rightSegmentSum == currentNode->rightChild->subtreeSize) {
            currentNode->rightSegmentSum = currentNode->rightChild->subtreeSize + currentNode->nodeValue;
        }
        currentNode->leftSegmentSum = currentNode->nodeValue ? currentNode->nodeValue + currentNode->rightChild->leftSegmentSum : 0;
        currentNode->maxSegmentSum = max(currentNode->nodeValue, currentNode->rightChild->maxSegmentSum);
        currentNode->maxSegmentSum = max(currentNode->maxSegmentSum, currentNode->nodeValue + currentNode->rightChild->leftSegmentSum);
        currentNode->maxSegmentSum = max({currentNode->maxSegmentSum, currentNode->leftSegmentSum, currentNode->rightSegmentSum});
    }
}

void rotateNode(SplayTreeNode *currentNode) {
    SplayTreeNode *parentNode, *childNode;
    parentNode = currentNode->parent;
    if (!parentNode) return;
    propagateInversion(parentNode);
    propagateInversion(currentNode);
    SplayTreeNode *grandparentNode = parentNode->parent;
    if (parentNode->leftChild == currentNode) {
        parentNode->leftChild = childNode = currentNode->rightChild;
        currentNode->rightChild = parentNode;
    } else {
        parentNode->rightChild = childNode = currentNode->leftChild;
        currentNode->leftChild = parentNode;
    }
    parentNode->parent = currentNode;
    currentNode->parent = grandparentNode;
    if (childNode) childNode->parent = parentNode;
    if (!grandparentNode) {
        root = currentNode;
    } else {
        if (grandparentNode->leftChild == parentNode) {
            grandparentNode->leftChild = currentNode;
        } else {
            grandparentNode->rightChild = currentNode;
        }
    }
    updateNode(parentNode);
    updateNode(currentNode);
}

void splay(SplayTreeNode *currentNode) {
    while (currentNode->parent) {
        SplayTreeNode *parentNode = currentNode->parent;
        SplayTreeNode *grandparentNode = parentNode->parent;
        if (grandparentNode) {
            if ((grandparentNode->leftChild == parentNode) == (parentNode->leftChild == currentNode)) {
                rotateNode(parentNode);
            } else {
                rotateNode(currentNode);
            }
        }
        rotateNode(currentNode);
    }
}

void findKthNode(ll k) {
    SplayTreeNode *currentNode = root;
    propagateInversion(currentNode);
    while (true) {
        while (currentNode->leftChild && currentNode->leftChild->subtreeSize > k) {
            currentNode = currentNode->leftChild;
            propagateInversion(currentNode);
        }
        if (currentNode->leftChild) k -= currentNode->leftChild->subtreeSize;
        if (!k) break;
        else --k;
        currentNode = currentNode->rightChild;
        propagateInversion(currentNode);
    }
    splay(currentNode);
}

SplayTreeNode* getSegment(int leftIndex, int rightIndex) {
    if (leftIndex != 1 && rightIndex != numberOfNodes) {
        findKthNode(leftIndex - 2);
        SplayTreeNode *currentNode = root;
        root = currentNode->rightChild;
        root->parent = nullptr;
        findKthNode(rightIndex - leftIndex + 1);
        root->parent = currentNode;
        currentNode->rightChild = root;
        root = currentNode;
        return root->rightChild->leftChild;
    } else if (leftIndex == 1 && rightIndex == numberOfNodes) {
        splay(nodePointers[(numberOfNodes + 1) / 2]);
        return root;
    } else if (leftIndex == 1) {
        findKthNode(rightIndex);
        return root->leftChild;
    } else if (rightIndex == numberOfNodes) {
        if (leftIndex != rightIndex) findKthNode(leftIndex - 2);
        else findKthNode(numberOfNodes - 2);
        return root->rightChild;
    }
    return nullptr;
}

void initializeTree() {
    SplayTreeNode *currentNode;
    root = currentNode = new SplayTreeNode;
    currentNode->nodeValue = arrayOfValues[1];
    currentNode->inversionFlag = false;
    nodePointers[1] = currentNode;
    for (int i = 2; i <= numberOfNodes; ++i) {
        currentNode->rightChild = new SplayTreeNode;
        currentNode->rightChild->parent = currentNode;
        currentNode = currentNode->rightChild;
        currentNode->nodeValue = arrayOfValues[i];
        currentNode->inversionFlag = false;
        nodePointers[i] = currentNode;
    }
    while (currentNode) {
        updateNode(currentNode);
        currentNode = currentNode->parent;
    }
}

void flipSegment(int leftIndex, int rightIndex) {
    SplayTreeNode *segmentNode = getSegment(leftIndex, rightIndex);
    segmentNode->inversionFlag = !segmentNode->inversionFlag;
    while (segmentNode) {
        updateNode(segmentNode);
        segmentNode = segmentNode->parent;
    }
}

void printTree(SplayTreeNode *currentNode) {
    if (currentNode->leftChild) printTree(currentNode->leftChild);
    cout << currentNode->nodeValue << ' ';
    if (currentNode->rightChild) printTree(currentNode->rightChild);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> numberOfNodes;
    for (int i = 1; i <= numberOfNodes; ++i) {
        cin >> arrayOfValues[i];
    }
    initializeTree();
    cin >> numberOfQueries;
    for (int i = 0; i < numberOfQueries; ++i) {
        int queryType, leftIndex, rightIndex;
        cin >> queryType >> leftIndex >> rightIndex;
        if (queryType == 1) {
            flipSegment(leftIndex, rightIndex);
        } else {
            SplayTreeNode *segmentNode = getSegment(leftIndex, rightIndex);
            cout << segmentNode->maxSegmentSum << '\n';
        }
    }
    return 0;
}
