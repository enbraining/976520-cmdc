#include<bits/stdc++.h>
using namespace std;

struct Line {
    long long slope, intercept;
    Line() : slope(0), intercept(0) {}
    Line(long long slope_, long long intercept_) : slope(slope_), intercept(intercept_) {}
    long long evaluate(long long x) { return slope * x + intercept; }
};

vector<Line> lines;
int currentPointer = 1;
vector<long long> dp, vertexValues, weights;
vector<vector<pair<int, long long>>> graph;
int numberOfNodes;

long double computeIntersection(Line &line1, Line &line2) {
    return (long double)(line1.intercept - line2.intercept) / (line2.slope - line1.slope);
}

int addLine(Line &newLine) {
    int low = 1, high = currentPointer;
    while (low < high) {
        int mid = (low + high) >> 1;
        if (computeIntersection(lines[mid - 1], newLine) < computeIntersection(lines[mid], lines[mid - 1])) 
            high = mid;
        else 
            low = mid + 1;
    }
    return low;
}

long long query(long long x) {
    int low = 0, high = currentPointer - 1;
    while (low < high) {
        int mid = (low + high + 1) >> 1;
        if (computeIntersection(lines[mid], lines[mid - 1]) < x) 
            low = mid;
        else 
            high = mid - 1;
    }
    return lines[low].evaluate(x);
}

void depthFirstSearch(int currentNode, int parentNode, long long distance) {
    int rollbackIndex, rollbackPointer = currentPointer;
    Line rollbackLine;
    if (parentNode) {
        dp[currentNode] = query(vertexValues[currentNode]) + distance * vertexValues[currentNode] + weights[currentNode];
        Line currentLine(-distance, dp[currentNode]);
        rollbackIndex = addLine(currentLine);
        rollbackLine = lines[rollbackIndex];
        lines[rollbackIndex] = currentLine;
        currentPointer = rollbackIndex + 1;
    }
    for (auto &nextNode : graph[currentNode]) {
        int nextVertex = nextNode.first;
        long long weight = nextNode.second;
        if (nextVertex == parentNode) continue;
        depthFirstSearch(nextVertex, currentNode, distance + weight);
    }
    if (parentNode) {
        lines[rollbackIndex] = rollbackLine;
        currentPointer = rollbackPointer;
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> numberOfNodes;
    dp.resize(numberOfNodes + 1); weights.resize(numberOfNodes + 1); vertexValues.resize(numberOfNodes + 1);
    graph.resize(numberOfNodes + 1); lines.resize(numberOfNodes + 1, Line());
    for (int i = 1; i < numberOfNodes; ++i) {
        int nodeU, nodeV;
        long long edgeWeight;
        cin >> nodeU >> nodeV >> edgeWeight;
        graph[nodeU].emplace_back(nodeV, edgeWeight);
        graph[nodeV].emplace_back(nodeU, edgeWeight);
    }
    for (int i = 2; i <= numberOfNodes; ++i) cin >> weights[i] >> vertexValues[i];
    depthFirstSearch(1, 0, 0);
    for (int i = 2; i <= numberOfNodes; ++i) cout << dp[i] << " \n"[i == numberOfNodes];
    return 0;
}

