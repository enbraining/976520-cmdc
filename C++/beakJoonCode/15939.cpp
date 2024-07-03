#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

istream& operator >> (istream& in, pair<long long, long long>& t) { 
    in >> t.x >> t.y; return in; 
}
ostream& operator << (ostream& out, pair<long long, long long> t) { 
    out << t.x << " " << t.y; return out; 
}

int numVertices, numQueries;
pair<long long, long long> vertices[10101];
int nextVertex[2][5050];

int ccw(const pair<long long, long long>& a, const pair<long long, long long>& b, const pair<long long, long long>& c) {
    long long dx1 = b.x - a.x, dy1 = b.y - a.y;
    long long dx2 = c.x - b.x, dy2 = c.y - b.y;
    long long res = dx1 * dy2 - dx2 * dy1;
    if (res == 0) {
        return 0;
    }
    return res > 0 ? 1 : -1;
}

int isOutsidePolygon(pair<long long, long long> pt) {
    for (int i = 0; i < numVertices; i++) {
        if (ccw(vertices[i], vertices[i + 1], pt) != 1) {
            return 1;
        }
    }
    return 0;
}

void computeNextVertices(int* arr, pair<long long, long long> pt) {
    for (int i = 0; i < numVertices; i++) {
        arr[i] = arr[i - 1];
        if (i == arr[i] % numVertices) {
            arr[i]++;
        }
        while (ccw(vertices[i], vertices[arr[i] + 1], pt) == 1) {
            arr[i]++;
        }
    }
}

int moveInsidePolygon() {
    int totalMoves = 0;
    for (int i = 0; i < numVertices; i++) {
        totalMoves += abs(nextVertex[0][i] - nextVertex[1][i]);
    }
    return totalMoves / 2;
}

int sum1[10101], sum2[10101];

int moveOutsidePolygon(int* arr) {
    memset(sum1, 0, sizeof sum1);
    memset(sum2, 0, sizeof sum2);

    for (int i = 0; i < numVertices; i++) {
        int j = arr[i];
        sum1[i] += j - i - 1;
        sum1[i + 1] -= j - i - 1;
        sum1[i - 1 + numVertices] += numVertices + i - j - 2;
        sum1[i + numVertices] -= numVertices + i - j - 2;
        sum1[j] -= j;
        sum1[i - 1 + numVertices] += j;
        sum2[j]++;
        sum2[i - 1 + numVertices]--;
        sum1[i + 1] += j;
        sum1[j] -= j;
        sum2[i + 1]--;
        sum2[j]++;
    }

    for (int i = 1; i < numVertices + numVertices; i++) {
        sum1[i] += sum1[i - 1];
        sum2[i] += sum2[i - 1];
    }

    int minMoves = INT_MAX;
    for (int i = 0; i < numVertices; i++) {
        int currentMoves = sum1[i] + i * sum2[i];
        currentMoves += sum1[i + numVertices] + (i + numVertices) * sum2[i + numVertices];
        minMoves = min(minMoves, currentMoves);
    }
    return (minMoves / 2) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> numVertices;
    for (int i = 0; i < numVertices; i++) {
        cin >> vertices[i];
        vertices[i + numVertices] = vertices[i];
    }
    cin >> numQueries;

    while (numQueries--) {
        pair<long long, long long> point1, point2;
        cin >> point1 >> point2;

        int outside1 = isOutsidePolygon(point1), moves1 = 0;
        int outside2 = isOutsidePolygon(point2), moves2 = 0;

        if (outside1 && outside2) {
            cout << "0\n";
            continue;
        }

        if (outside1 && !outside2) {
            swap(point1, point2);
            swap(outside1, outside2);
        }

        if (!outside1) {
            computeNextVertices(nextVertex[0], point1);
            moves1 = moveOutsidePolygon(nextVertex[0]);
        }

        if (!outside2) {
            computeNextVertices(nextVertex[1], point2);
            moves2 = moveOutsidePolygon(nextVertex[1]);
        }

        if (!outside1 && outside2) {
            cout << moves1 << "\n";
        }
        else {
            cout << min(moveInsidePolygon(), moves1 + moves2) << "\n";
        }
    }
}
