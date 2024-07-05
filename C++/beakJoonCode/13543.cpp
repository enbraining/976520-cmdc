#include<bits/stdc++.h>
using namespace std;

unsigned int combination[11][11];

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    unsigned int size;
    unsigned int value;
    bool inverted;

    unsigned int answer[11];
    bool isDummy;
    
    TreeNode() : left(nullptr), right(nullptr), parent(nullptr) {};
    TreeNode(unsigned int _value) {
        left = right = parent = nullptr;
        size = 1;
        value = _value;
        inverted = false;
        isDummy = false;
        for (int i = 0; i <= 10; ++i) {
            answer[i] = value;
        }
    }
} *root;

void updateNode(TreeNode* currentNode) {
    currentNode->size = 1;
    if (currentNode->left) {
        currentNode->size += currentNode->left->size;
    }
    if (currentNode->right) {
        currentNode->size += currentNode->right->size;
    }

    unsigned int leftSize = currentNode->left ? currentNode->left->size : 0;
    unsigned int power[11];
    power[0] = 1;
    
    for (int i = 1; i <= 10; ++i) {
        power[i] = power[i - 1] * (leftSize + 1);
    }
    
    for (int i = 0; i <= 10; ++i) {
        currentNode->answer[i] = power[i] * currentNode->value;
    }
    
    for (int i = 0; i <= 10; ++i) {
        if (currentNode->left) {
            currentNode->answer[i] += currentNode->left->answer[i];
        }
        if (currentNode->right) {
            for (int j = 0; j <= i; ++j) {
                currentNode->answer[i] += currentNode->right->answer[j] * power[i - j] * combination[i][j];
            }
        }
    }
}

void reverseChildren(TreeNode* currentNode) {
    swap(currentNode->left, currentNode->right);
}

void propagate(TreeNode* currentNode) {
    if (currentNode->inverted) {
        reverseChildren(currentNode);
        if (currentNode->left) {
            currentNode->left->inverted = !currentNode->left->inverted;
        }
        if (currentNode->right) {
            currentNode->right->inverted = !currentNode->right->inverted;
        }
        currentNode->inverted = false;
    }
}

void rotateNode(TreeNode* currentNode) {
    TreeNode* parentNode = currentNode->parent;
    if (!parentNode) {
        return;
    }
    
    propagate(parentNode);
    propagate(currentNode);
    
    TreeNode* temporaryNode;
    if (parentNode->left == currentNode) {
        temporaryNode = currentNode->right;
        parentNode->left = currentNode->right;
        currentNode->right = parentNode;
    } else {
        temporaryNode = currentNode->left;
        parentNode->right = currentNode->left;
        currentNode->left = parentNode;
    }
    
    TreeNode* grandParentNode = parentNode->parent;
    currentNode->parent = grandParentNode;
    parentNode->parent = currentNode;
    if (temporaryNode) {
        temporaryNode->parent = parentNode;
    }
    
    if (currentNode->parent) {
        if (grandParentNode->left == parentNode) {
            grandParentNode->left = currentNode;
        } else if (grandParentNode->right == parentNode) {
            grandParentNode->right = currentNode;
        }
    } else {
        root = currentNode;
    }
    
    updateNode(parentNode);
    updateNode(currentNode);
}

void splayNode(TreeNode* currentNode) {
    while (currentNode->parent) {
        TreeNode* parentNode = currentNode->parent;
        TreeNode* grandParentNode = parentNode->parent;
        
        if (grandParentNode) {
            if ((grandParentNode->left == parentNode) == (parentNode->left == currentNode)) {
                rotateNode(parentNode);
            } else {
                rotateNode(currentNode);
            }
        }
        rotateNode(currentNode);
    }
}

pair<TreeNode*, TreeNode*> splitTree(TreeNode* currentNode) {
    splayNode(currentNode);
    TreeNode* leftTree = currentNode;
    TreeNode* rightTree = currentNode->right;
    if (leftTree) {
        leftTree->parent = nullptr;
    }
    if (rightTree) {
        rightTree->parent = nullptr;
    }
    return { leftTree, rightTree };
}

TreeNode* mergeTrees(TreeNode* leftTree, TreeNode* rightTree) {
    if (leftTree == nullptr) {
        return rightTree;
    }
    if (rightTree == nullptr) {
        return leftTree;
    }
    
    TreeNode* tempNode = leftTree;
    while (tempNode->right) {
        tempNode = tempNode->right;
    }
    
    propagate(tempNode);
    splayNode(tempNode);
    tempNode->right = rightTree;
    rightTree->parent = tempNode;
    updateNode(tempNode);
    
    return tempNode;
}

TreeNode* findKth(TreeNode* currentNode, int k) {
    TreeNode* tempNode = currentNode;
    propagate(tempNode);
    
    while (true) {
        while (tempNode->left && tempNode->left->size > k) {
            tempNode = tempNode->left;
            propagate(tempNode);
        }
        if (tempNode->left) {
            k -= tempNode->left->size;
        }
        if (!k) {
            break;
        } else {
            --k;
        }
        tempNode = tempNode->right;
        propagate(tempNode);
    }
    
    splayNode(tempNode);
    return tempNode;
}

TreeNode* getInterval(TreeNode* currentNode, int left, int right) {
    TreeNode* tempNode = findKth(currentNode, left - 1);
    TreeNode* rightNode = tempNode->right;
    rightNode->parent = nullptr;
    rightNode = findKth(rightNode, right - left + 1);
    rightNode->parent = tempNode;
    tempNode->right = rightNode;
    root = tempNode;
    updateNode(tempNode);
    return tempNode;
}

int numberOfNodes, numberOfQueries;
unsigned int nodeValues[100005];

void initialize() {
    combination[0][0] = 1;
    for (int i = 1; i <= 10; ++i) {
        combination[i][0] = combination[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            combination[i][j] = combination[i - 1][j - 1] + combination[i - 1][j];
        }
    }
    
    TreeNode* tempNode = root = new TreeNode(0);
    tempNode->isDummy = true;
    
    for (int i = 1; i <= numberOfNodes; ++i) {
        tempNode->right = new TreeNode(nodeValues[i]);
        tempNode->right->parent = tempNode;
        tempNode = tempNode->right;
    }
    
    tempNode->right = new TreeNode(0);
    tempNode->right->parent = tempNode;
    tempNode = tempNode->right;
    tempNode->isDummy = true;
    
    while (tempNode) {
        updateNode(tempNode);
        tempNode = tempNode->parent;
    }
}

TreeNode* insertValue(TreeNode* currentNode, int position, unsigned int value) {
    TreeNode* tempNode = findKth(root, position)->right;
    while (tempNode->left) {
        tempNode = tempNode->left;
    }
    tempNode->left = new TreeNode(value);
    tempNode->left->parent = tempNode;
    splayNode(tempNode->left);
    return root;
}

TreeNode* deleteValue(TreeNode* currentNode, int position) {
    TreeNode* tempNode = findKth(root, position);
    pair<TreeNode*, TreeNode*> splittedTrees = splitTree(tempNode);
    if (splittedTrees.first) {
        propagate(splittedTrees.first);
    }
    if (splittedTrees.second) {
        propagate(splittedTrees.second);
    }
    root = mergeTrees(splittedTrees.first->left, splittedTrees.second);
    return root;
}

TreeNode* updateValue(TreeNode* currentNode, int position, int value) {
    TreeNode* tempNode = findKth(root, position);
    tempNode->value = value;
    updateNode(tempNode);
    return root;
}

unsigned int querySum(TreeNode* currentNode, unsigned int left, unsigned int right, unsigned int k) {
    TreeNode* tempNode = getInterval(root, left, right);
    return tempNode->right->left->answer[k];
}

void printTree(TreeNode* currentNode) {
    if (currentNode->left) {
        printTree(currentNode->left);
    }
    if (!currentNode->isDummy) {
        cout << currentNode->value << ' ';
    }
    if (currentNode->right) {
        printTree(currentNode->right);
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> numberOfNodes;
    
    for (int i = 1; i <= numberOfNodes; ++i) {
        cin >> nodeValues[i];
    }
    
    initialize();
    cin >> numberOfQueries;
    
    for (int i = 0; i < numberOfQueries; ++i) {
        string command;
        unsigned int queryType, position, value, left, right, k;
        cin >> queryType;
        
        if (queryType == 1) {
            cin >> position >> value;
            insertValue(root, position, value);
        } else if (queryType == 2) {
            cin >> position;
            deleteValue(root, position + 1);
        } else if (queryType == 3) {
            cin >> position >> value;
            updateValue(root, position + 1, value);
        } else if (queryType == 4) {
            cin >> left >> right >> k;
            ++left; ++right;
            cout << querySum(root, left, right, k) << '\n';
        }
    }
    
    return 0;
}
