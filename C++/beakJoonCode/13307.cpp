#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    long long color;
    long long index;

    Point() {}

    Point(long long x, long long y, long long color, long long index)
        : x(x), y(y), color(color), index(index) {}

    bool operator<(const Point &other) const {
        return x * other.y > y * other.x;
    }

    Point operator-(const Point &other) {
        return {x - other.x, y - other.y, this->color, this->index};
    }
};

Point points[4000];
int results[1000][2];
int totalPoints;

void solve(vector<int> &pointIndices) {
    if (pointIndices.empty()) {
        return;
    }

    vector<Point> sortedPoints;
    for (int i = 0; i < pointIndices.size(); ++i) {
        sortedPoints.push_back(points[pointIndices[i]]);
        sortedPoints.back().index = pointIndices[i];
    }

    for (int i = 1; i < sortedPoints.size(); ++i) {
        if (sortedPoints[0].y > sortedPoints[i].y || 
            (sortedPoints[0].y == sortedPoints[i].y && sortedPoints[0].x > sortedPoints[i].x)) {
            swap(sortedPoints[0], sortedPoints[i]);
        }
    }

    for (int i = sortedPoints.size() - 1; i >= 0; --i) {
        sortedPoints[i] = sortedPoints[i] - sortedPoints[0];
    }

    sort(sortedPoints.begin() + 1, sortedPoints.end());

    int startIndex = -1;
    int firstPointIndex = sortedPoints[0].index;
    sortedPoints.erase(sortedPoints.begin());

    if (points[firstPointIndex].color) {
        startIndex = firstPointIndex;
    } else if (points[sortedPoints[0].index].color) {
        startIndex = sortedPoints[0].index;
    } else if (points[sortedPoints.back().index].color) {
        startIndex = sortedPoints.back().index;
    }

    if (startIndex != -1) {
        if (startIndex != firstPointIndex) {
            sortedPoints.clear();
            for (int i = 0; i < pointIndices.size(); ++i) {
                if (pointIndices[i] != startIndex) {
                    sortedPoints.push_back(points[pointIndices[i]] - points[startIndex]);
                    sortedPoints.back().index = pointIndices[i];
                }
            }
            sort(sortedPoints.begin(), sortedPoints.end());
        }

        int count = 0;
        int previousValue = -1;
        vector<int> nextPoints;
        for (int i = 0; i < sortedPoints.size(); ++i) {
            count += points[sortedPoints[i].index].color ? 2 : -1;
            if (count == previousValue) {
                if (previousValue == -1) {
                    results[startIndex][0] = sortedPoints[i].index;
                } else {
                    results[startIndex][1] = sortedPoints[i].index;
                }
                solve(nextPoints);
                nextPoints.clear();
                previousValue--;
                if (previousValue < -2) {
                    previousValue = INT_MAX;
                }
            } else {
                nextPoints.push_back(sortedPoints[i].index);
            }
        }
        solve(nextPoints);
        return;
    }

    for (int attempt = 0; attempt < 2; ++attempt) {
        int count = 0;
        vector<int> nextPoints;
        for (int i = 0; i < sortedPoints.size(); ++i) {
            count += points[sortedPoints[i].index].color ? 2 : -1;
            nextPoints.push_back(sortedPoints[i].index);
            if (count == 0) {
                solve(nextPoints);
                nextPoints.clear();
                for (int j = i + 1; j < sortedPoints.size(); ++j) {
                    nextPoints.push_back(sortedPoints[j].index);
                }
                nextPoints.push_back(firstPointIndex);
                solve(nextPoints);
                return;
            }
        }
        reverse(sortedPoints.begin(), sortedPoints.end());
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> totalPoints;
    vector<int> allIndices;
    for (int i = 0; i < 3 * totalPoints; ++i) {
        cin >> points[i].x >> points[i].y;
        if (i < totalPoints) {
            points[i].color = 1; 
        } else {
            points[i].color = 0; 
        }
        points[i].index = i;
        allIndices.push_back(i);
    }

    solve(allIndices);

    for (int i = 0; i < totalPoints; ++i) {
        cout << results[i][0] - totalPoints + 1 << " " << results[i][1] - totalPoints + 1 << "\n";
    }

    return 0;
}
