// 수열과 쿼리 16
// https://www.acmicpc.net/problem/14428
#include <stdio.h>

int segtree[1000010], arr[1000010];
int queryType, left, right;

int minIndex(int index1, int index2) {
    if (arr[index1] < arr[index2]) {
        return index1;
    }
    if (arr[index1] > arr[index2]) {
        return index2;
    }
    return index1 < index2 ? index1 : index2;
}

int buildSegmentTree(int start, int end, int node) {
    if (start == end) {
        return segtree[node] = start;
    }
    int mid = (start + end) / 2;
    return segtree[node] = minIndex(buildSegmentTree(start, mid, node * 2), buildSegmentTree(mid + 1, end, node * 2 + 1));
}

int getMinIndex(int start, int end, int node, int queryLeft, int queryRight) {
    if (queryRight < start || queryLeft > end) {
        return right;
    }
    if (queryLeft <= start && end <= queryRight) {
        return segtree[node];
    }

    int mid = (start + end) / 2;
    return minIndex(getMinIndex(start, mid, node * 2, queryLeft, queryRight), getMinIndex(mid + 1, end, node * 2 + 1, queryLeft, queryRight));
}

int updateSegmentTree(int start, int end, int node, int idx) {
    if (idx < start || idx > end) {
        return segtree[node];
    }
    if (start == idx && end == idx) {
        return segtree[node];
    }

    int mid = (start + end) / 2;
    return segtree[node] = minIndex(updateSegmentTree(start, mid, node * 2, idx), updateSegmentTree(mid + 1, end, node * 2 + 1, idx));
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }

    buildSegmentTree(1, n, 1);

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &queryType, &left, &right);
        if (queryType == 1) {
            arr[left] = right;
            updateSegmentTree(1, n, 1, left);
        } else {
            printf("%d\n", getMinIndex(1, n, 1, left, right));
        }
    }
}
