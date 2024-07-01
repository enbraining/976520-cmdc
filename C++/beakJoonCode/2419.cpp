#include <bits/stdc++.h>

using namespace std;

int numPositions, pointsPerMove;
int dp[256][256][2];
bool visited[256][256][2];
vector<int> positions;

int distanceBetween(int start, int end) {
    return abs(positions[start] - positions[end]);
}

int maximizePoints(int left, int right, int direction, int remainingMoves) {
    if (remainingMoves == 0) { 
        return 0; 
    }
    if (left == 0 && right == numPositions) { 
        return 0; 
    }

    int& result = dp[left][right][direction];
    if (visited[left][right][direction]) { 
        return result; 
    }

    int currentPos = direction ? right : left;
    if (left > 0) {
        result = max(result, maximizePoints(left - 1, right, 0, remainingMoves - 1) - remainingMoves * distanceBetween(currentPos, left - 1) + pointsPerMove);
    }
    if (right < numPositions) {
        result = max(result, maximizePoints(left, right + 1, 1, remainingMoves - 1) - remainingMoves * distanceBetween(currentPos, right + 1) + pointsPerMove);
    }
    visited[left][right][direction] = true;
    return result;
}

int main() {
    cin >> numPositions >> pointsPerMove;

    positions.resize(numPositions);
    bool hasZero = false;
    for (int i = 0; i < numPositions; i++) {
        cin >> positions[i];
        if (positions[i] == 0) { 
            hasZero = true; 
        }
    }

    if (!hasZero) {
        positions.push_back(0);
    } else {
        numPositions--; 
    }

    sort(positions.begin(), positions.end());
    int zeroIndex = lower_bound(positions.begin(), positions.end(), 0) - positions.begin();

    int maxPoints = 0;
    for (int i = 0; i <= numPositions; i++) {
        memset(dp, 0, sizeof(dp));
        memset(visited, 0, sizeof(visited));
        int currentPoints = maximizePoints(zeroIndex, zeroIndex, 0, i);
        if (hasZero) {
            currentPoints += pointsPerMove;
        }
        maxPoints = max(maxPoints, currentPoints);
    }

    cout << maxPoints;
}
