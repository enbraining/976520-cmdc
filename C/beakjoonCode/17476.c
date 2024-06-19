//https://www.acmicpc.net/problem/17476 
//수열과 쿼리
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int arr[100000];
long long int maxTree[300000], minTree[300000], sumTree[300000], lazy[300000] = { 0 };

long long max(long long a, long long b);
long long min(long long a, long long b);
long long getMax(int node, int start, int end, int left, int right);
long long getMin(int node, int start, int end, int left, int right);
long long int getSum(int node, int start, int end, int left, int right);
void buildTree(int node, int start, int end);
void propagate(int node, int start, int end);
void addRange(int node, int start, int end, int left, int right, int value);
void sqrtRange(int node, int start, int end, int left, int right);

int main() {
    int n, q, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    buildTree(1, 0, n - 1);
    scanf("%d", &q);
    int op, l, r, x;
    for (i = 0; i < q; i++) {
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &x);
            addRange(1, 0, n - 1, l - 1, r - 1, x);
        } else if (op == 2) {
            sqrtRange(1, 0, n - 1, l - 1, r - 1);
        } else {
            printf("%lld\n", getSum(1, 0, n - 1, l - 1, r - 1));
        }
    }
}

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

long long int getMax(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    if (right < start || end < left) {
        return 0;
    }
    if (left <= start && end <= right) {
        return maxTree[node];
    }
    int mid = (start + end) / 2;
    return max(getMax(node * 2, start, mid, left, right), getMax(node * 2 + 1, mid + 1, end, left, right));
}

long long int getMin(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    if (right < start || end < left) {
        return 1000000000000;
    }
    if (left <= start && end <= right) {
        return minTree[node];
    }
    int mid = (start + end) / 2;
    return min(getMin(node * 2, start, mid, left, right), getMin(node * 2 + 1, mid + 1, end, left, right));
}

long long int getSum(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    if (right < start || end < left) {
        return 0;
    }
    if (left <= start && end <= right) {
        return sumTree[node];
    }
    int mid = (start + end) / 2;
    return getSum(node * 2, start, mid, left, right) + getSum(node * 2 + 1, mid + 1, end, left, right);
}

void buildTree(int node, int start, int end) {
    if (start == end) {
        maxTree[node] = arr[start];
        minTree[node] = arr[start];
        sumTree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildTree(node * 2, start, mid);
        buildTree(node * 2 + 1, mid + 1, end);
        maxTree[node] = max(maxTree[node * 2], maxTree[node * 2 + 1]);
        minTree[node] = min(minTree[node * 2], minTree[node * 2 + 1]);
        sumTree[node] = sumTree[node * 2] + sumTree[node * 2 + 1];
    }
}

void propagate(int node, int start, int end) {
    if (lazy[node]) {
        maxTree[node] += lazy[node];
        minTree[node] += lazy[node];
        sumTree[node] += lazy[node] * (end - start + 1);
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void addRange(int node, int start, int end, int left, int right, int value) {
    propagate(node, start, end);
    if (right < start || end < left) {
        return;
    }
    if (left <= start && end <= right) {
        maxTree[node] += value;
        minTree[node] += value;
        sumTree[node] += (long long)value * (end - start + 1);
        if (start != end) {
            lazy[node * 2] += value;
            lazy[node * 2 + 1] += value;
        }
        return;
    }
    int mid = (start + end) / 2;
    addRange(node * 2, start, mid, left, right, value);
    addRange(node * 2 + 1, mid + 1, end, left, right, value);
    maxTree[node] = max(maxTree[node * 2], maxTree[node * 2 + 1]);
    minTree[node] = min(minTree[node * 2], minTree[node * 2 + 1]);
    sumTree[node] = sumTree[node * 2] + sumTree[node * 2 + 1];
}

void sqrtRange(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    if (right < start || end < left) {
        return;
    }
    if (left <= start && end <= right) {
        long long current_max = maxTree[node], current_min = minTree[node];
        long long delta = floor(sqrt(current_max)) - current_max;
        if (delta == floor(sqrt(current_min)) - current_min) {
            maxTree[node] += delta;
            minTree[node] += delta;
            sumTree[node] += delta * (end - start + 1);
            if (start != end) {
                lazy[node * 2] += delta;
                lazy[node * 2 + 1] += delta;
            }
            return;
        }
    }
    int mid = (start + end) / 2;
    sqrtRange(node * 2, start, mid, left, right);
    sqrtRange(node * 2 + 1, mid + 1, end, left, right);
    maxTree[node] = max(maxTree[node * 2], maxTree[node * 2 + 1]);
    minTree[node] = min(minTree[node * 2], minTree[node * 2 + 1]);
    sumTree[node] = sumTree[node * 2] + sumTree[node * 2 + 1];
}
