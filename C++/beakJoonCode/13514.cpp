#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace std;

const int direction_i[] = { 1, 0, -1, 0, 1, 1, -1, -1 }, direction_j[] = { 0, 1, 0, -1, 1, -1, 1, -1 };
long long greatestCommonDivisor(long long x, long long y) { return y ? greatestCommonDivisor(y, x % y) : x; }
long long leastCommonMultiple(long long x, long long y) { return x / greatestCommonDivisor(x, y) * y; }
long long modulo(long long a, long long b) { return ((a % b) + b) % b; }
long long extendedGCD(long long a, long long b, long long& x, long long& y) {
    long long g = a; x = 1, y = 0;
    if (b) g = extendedGCD(b, a % b, y, x), y -= a / b * x;
    return g;
}
long long modularInverse(long long a, long long m) {
    long long x, y;
    long long g = extendedGCD(a, m, x, y);
    if (g > 1) return -1;
    return modulo(x, m);
}
void terminate() { exit(0); }

int subtreeSize[999999], used[999999], depth[999999];
int ancestor[22][999999];
vector<int> graph[999999];
int centroidTree[999999];
multiset<int> distances[999999];
int nodeColor[999999];

void depthFirstSearch(int current, int previous = -1) {
    ancestor[0][current] = previous;
    depth[current] = depth[previous] + 1;
    for (auto neighbor : graph[current]) {
        if (neighbor == previous) continue;
        depthFirstSearch(neighbor, current);
    }
}

int lowestCommonAncestor(int first, int second) {
    if (depth[first] < depth[second]) swap(first, second);
    int difference = depth[first] - depth[second];
    for (int i = 0; difference; i++) {
        if (difference & 1) first = ancestor[i][first];
        difference >>= 1;
    }
    if (first == second) return first;
    for (int i = 21; i >= 0; i--) {
        if (ancestor[i][first] != ancestor[i][second]) first = ancestor[i][first], second = ancestor[i][second];
    }
    return ancestor[0][first];
}

int getDistance(int first, int second) {
    return depth[first] + depth[second] - 2 * depth[lowestCommonAncestor(first, second)];
}

int getSubtreeSize(int current, int previous = -1) {
    subtreeSize[current] = 1;
    for (auto neighbor : graph[current]) {
        if (used[neighbor] || previous == neighbor) continue;
        subtreeSize[current] += getSubtreeSize(neighbor, current);
    }
    return subtreeSize[current];
}

int getCentroid(int current, int previous, int count) {
    for (auto neighbor : graph[current]) {
        if (used[neighbor] || neighbor == previous) continue;
        if (subtreeSize[neighbor] > count / 2) return getCentroid(neighbor, current, count);
    }
    return current;
}

void centroidDecomposition(int current, int previous = -1) {
    int count = getSubtreeSize(current, previous);
    int centroid = getCentroid(current, previous, count);
    if (previous == -1) centroidTree[centroid] = centroid;
    else centroidTree[centroid] = previous;
    used[centroid] = 1;
    for (auto neighbor : graph[centroid]) {
        if (!used[neighbor]) centroidDecomposition(neighbor, centroid);
    }
}

void update(int vertex) {
    nodeColor[vertex] = !nodeColor[vertex];
    int i = vertex;
    while (1) {
        int distance = getDistance(i, vertex);
        if (nodeColor[vertex]) distances[i].insert(distance);
        else distances[i].erase(distances[i].find(distance));
        if (i == centroidTree[i]) break;
        i = centroidTree[i];
    }
}

int query(int vertex) {
    int i = vertex;
    int result = 1e9 + 7;
    while (1) {
        int distance = getDistance(i, vertex);
        if (!distances[i].empty()) result = min(result, distance + *distances[i].begin());
        if (i == centroidTree[i]) break;
        i = centroidTree[i];
    }
    if (result > 1e9) return -1;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int numberOfVertices; cin >> numberOfVertices;
    for (int i = 1; i < numberOfVertices; i++) {
        int start, end; cin >> start >> end;
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
    depthFirstSearch(1);
    for (int j = 1; j < 22; j++) {
        for (int i = 1; i <= numberOfVertices; i++) {
            ancestor[j][i] = ancestor[j - 1][ancestor[j - 1][i]];
        }
    }
    centroidDecomposition(1);
    int numberOfQueries; cin >> numberOfQueries;
    while (numberOfQueries--) {
        int operation, vertex; cin >> operation >> vertex;
        if (operation == 1) {
            update(vertex);

        }
        else {
            cout << query(vertex) << "\n";
        }
    }
}
