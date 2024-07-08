#ifndef LOCAL
#include "seats.h"
#endif
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;


int rowCount, colCount, totalSeats, seatAssignments[1 << 20];
vector<int> rowPositions, colPositions;
vector<vector<int>> grid;
pair<int, int> segmentTree[1 << 21];
int lazy[1 << 21];

pair<int, int> Merge(const pair<int, int>& left, const pair<int, int>& right) {
    if (left.x == right.x) {
        return pair<int, int>(left.x, left.y + right.y);
    }
    else {
        return min(left, right);
    }
}

void Push(int node, int start, int end) {
    segmentTree[node].x += lazy[node];
    if (start != end) {
        lazy[node << 1] += lazy[node];
        lazy[node << 1 | 1] += lazy[node];
    }
    lazy[node] = 0;
}

void InitSegmentTree(int node = 1, int start = 1, int end = totalSeats) {
    if (start == end) {
        segmentTree[node] = { seatAssignments[start], 1 };
        return;
    }
    int mid = (start + end) >> 1;
    InitSegmentTree(node << 1, start, mid);
    InitSegmentTree(node << 1 | 1, mid + 1, end);
    segmentTree[node] = Merge(segmentTree[node << 1], segmentTree[node << 1 | 1]);
}

void UpdateSegmentTree(int left, int right, int value, int node = 1, int start = 1, int end = totalSeats) {
    Push(node, start, end);
    if (right < start || end < left) {
        return;
    }
    if (left <= start && end <= right) {
        lazy[node] += value;
        Push(node, start, end);
        return;
    }
    int mid = (start + end) >> 1;
    UpdateSegmentTree(left, right, value, node << 1, start, mid);
    UpdateSegmentTree(left, right, value, node << 1 | 1, mid + 1, end);
    segmentTree[node] = Merge(segmentTree[node << 1], segmentTree[node << 1 | 1]);
}


void give_initial_chart(int height, int width, vector<int> initialRow, vector<int> initialCol) {
    rowCount = height;
    colCount = width;
    totalSeats = rowCount * colCount;
    swap(rowPositions, initialRow);
    swap(colPositions, initialCol);

    grid = vector<vector<int>>(rowCount + 2, vector<int>(colCount + 2, totalSeats + 1));
    for (int i = 0; i < totalSeats; i++) {
        grid[++rowPositions[i]][++colPositions[i]] = i + 1;
    }

    for (int i = 0; i <= rowCount; i++) {
        for (int j = 0; j <= colCount; j++) {
            vector<int> tmp = { grid[i][j], grid[i + 1][j], grid[i][j + 1], grid[i + 1][j + 1] };
            sort(tmp.begin(), tmp.end());
            seatAssignments[tmp[0]]++;
            seatAssignments[tmp[1]]--;
            seatAssignments[tmp[2]]++;
            seatAssignments[tmp[3]]--;
        }
    }
    partial_sum(seatAssignments, seatAssignments + (1 << 20), seatAssignments);
    InitSegmentTree();
}

void ChangeSeats(int x, int y, int value) {
    for (int dx = 0; dx < 2; dx++) {
        for (int dy = 0; dy < 2; dy++) {
            int i = x - dx;
            int j = y - dy;
            vector<int> tmp = { grid[i][j], grid[i + 1][j], grid[i][j + 1], grid[i + 1][j + 1] };
            sort(tmp.begin(), tmp.end());
            UpdateSegmentTree(tmp[0], tmp[1] - 1, value);
            UpdateSegmentTree(tmp[2], tmp[3] - 1, value);
        }
    }
}

int swap_seats(int a, int b) {
    ChangeSeats(rowPositions[a], colPositions[a], -1);
    ChangeSeats(rowPositions[b], colPositions[b], -1);
    swap(rowPositions[a], rowPositions[b]);
    swap(colPositions[a], colPositions[b]);
    swap(grid[rowPositions[a]][colPositions[a]], grid[rowPositions[b]][colPositions[b]]);
    ChangeSeats(rowPositions[a], colPositions[a], 1);
    ChangeSeats(rowPositions[b], colPositions[b], 1);
    return segmentTree[1].x == 4 ? segmentTree[1].y : 0;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int height, width, queryCount;
    cin >> height >> width >> queryCount;
    vector<int> initialRow(height * width), initialCol(height * width);
    for (int i = 0; i < height * width; i++) {
        cin >> initialRow[i] >> initialCol[i];
    }
    vector<int> swapA(queryCount), swapB(queryCount);
    for (int i = 0; i < queryCount; i++) {
        cin >> swapA[i] >> swapB[i];
    }
    give_initial_chart(height, width, initialRow, initialCol);
    for (int i = 0; i < queryCount; i++) {
        cout << swap_seats(swapA[i], swapB[i]) << "\n";
    }
    return 0;
}
#endif
