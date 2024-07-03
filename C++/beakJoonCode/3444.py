#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct TreeNode {
    TreeNode *left, *right, *parent;
    int size, value;
    bool inverted;
    int index;
    int min_index, min_value;
    TreeNode() : left(nullptr), right(nullptr), parent(nullptr) {};
    TreeNode(int _value, int _index) {
        left = right = parent = nullptr;
        size = 1;
        value = _value;
        inverted = false;
        index = _index;
        min_index = index;
        min_value = value;
    }
} *root, pool[100005], *position[100005];

void reverseSubtree(TreeNode *current) {
    swap(current->left, current->right);
}

void propagate(TreeNode *current) {
    if(current->inverted) {
        reverseSubtree(current);
        if(current->left) current->left->inverted = !current->left->inverted;
        if(current->right) current->right->inverted = !current->right->inverted;
        current->inverted = false;
    }
}

void update(TreeNode *current) {
    current->size = 1;
    current->min_index = current->index;
    current->min_value = current->value;
    if(current->left) {
        propagate(current->left);
        current->size += current->left->size;
        if(current->left->min_value < current->min_value) {
            current->min_value = current->left->min_value;
            current->min_index = current->left->min_index;
        }
    }
    if(current->right) {
        propagate(current->right);
        current->size += current->right->size;
        if(current->right->min_value < current->min_value) {
            current->min_value = current->right->min_value;
            current->min_index = current->right->min_index;
        }
    }
}

void rotate(TreeNode *current) {
    TreeNode* parent = current->parent;
    if(!parent) return;
    propagate(parent);
    propagate(current);
    TreeNode *temp;
    if(parent->left == current) {
        temp = current->right;
        parent->left = current->right;
        current->right = parent;
    } else {
        temp = current->left;
        parent->right = current->left;
        current->left = parent;
    }
    TreeNode *grandparent = parent->parent;
    current->parent = grandparent;
    parent->parent = current;
    if(temp) temp->parent = parent;
    if(current->parent) {
        if(grandparent->left == parent) grandparent->left = current;
        else if(grandparent->right == parent) grandparent->right = current;
    } else root = current;
    update(parent);
    update(current);
}

void splay(TreeNode *current) {
    while(current->parent) {
        TreeNode *parent = current->parent;
        TreeNode *grandparent = parent->parent;
        if(grandparent) {
            if((grandparent->left == parent) == (parent->left == current)) rotate(parent);
            else rotate(current);
        }
        rotate(current);
    }
}

pair<TreeNode*, TreeNode*> split(TreeNode *current) {
    splay(current);
    TreeNode *left = current;
    TreeNode *right = current->right;
    if(left) left->parent = nullptr;
    if(right) right->parent = nullptr;
    return {left, right};
}

TreeNode* merge(TreeNode *left, TreeNode *right) {
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    TreeNode *temp = left;
    while(temp->right) temp = temp->right;
    propagate(temp);
    splay(temp);
    temp->right = right;
    right->parent = temp;
    update(temp);
    return temp;
}

TreeNode* findKthNode(TreeNode *current, int k) {
    TreeNode *temp = current;
    propagate(temp);
    while(1) {
        while(temp->left && temp->left->size > k) {
            temp = temp->left;
            propagate(temp);
        }
        if(temp->left) k -= temp->left->size;
        if(!k) break;
        else --k;
        temp = temp->right;
        propagate(temp);
    }
    splay(temp);
    return temp;
}

TreeNode* findInterval(TreeNode *current, int left, int right) {
    TreeNode *leftNode = findKthNode(current, left - 1);
    TreeNode *rightNode = leftNode->right;
    rightNode->parent = nullptr;
    rightNode = findKthNode(rightNode, right - left + 1);
    rightNode->parent = leftNode;
    leftNode->right = rightNode;
    root = leftNode;
    update(leftNode);
    return leftNode;
}

int numElements;
int elements[100005];

TreeNode* initializeNode(TreeNode *current, int value, int index) {
    current->left = current->right = current->parent = nullptr;
    current->value = current->min_value = value;
    current->index = current->min_index = index;
    current->inverted = false;
    current->size = 1;
    return current;
}

void initializeTree() {
    int nodeIndex = 0;
    TreeNode *currentNode = root = initializeNode(pool + nodeIndex++, INF, 0);
    for(int i = 1; i <= numElements; ++i) {
        position[elements[i]] = currentNode->right = initializeNode(pool + nodeIndex++, elements[i], i);
        currentNode->right->parent = currentNode;
        currentNode = currentNode->right;
    }
    currentNode->right = initializeNode(pool + nodeIndex++, INF, numElements + 1);
    currentNode->right->parent = currentNode;
    currentNode = currentNode->right;
    while(currentNode) {
        update(currentNode);
        currentNode = currentNode->parent;
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    while(1) {
        cin >> numElements;
        if(!numElements) break;
        vector<int> uniqueValues;
        for(int i = 1; i <= numElements; ++i) {
            cin >> elements[i];
            uniqueValues.push_back(elements[i]);
        }
        sort(uniqueValues.begin(), uniqueValues.end());
        uniqueValues.erase(unique(uniqueValues.begin(), uniqueValues.end()), uniqueValues.end());
        vector<vector<int>> temp(uniqueValues.size());
        for(int i = 1; i <= numElements; ++i) {
            elements[i] = lower_bound(uniqueValues.begin(), uniqueValues.end(), elements[i]) - uniqueValues.begin();
            temp[elements[i]].push_back(i);
        }
        int index = 0;
        for(int i = 0; i < uniqueValues.size(); ++i) {
            for(int j : temp[i]) elements[j] = ++index;
        }
        initializeTree();
        for(int i = 1; i <= numElements; ++i) {
            splay(position[i]);
            int result = root->left->size;
            cout << result << " \n"[i == numElements];
            TreeNode *intervalNode = findInterval(root, i, result);
            intervalNode = intervalNode->right->left;
            intervalNode->inverted = !intervalNode->inverted;
            propagate(intervalNode);
        }
    }
    return 0;
}
