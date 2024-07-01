#include <bits/stdc++.h>
using namespace std;

long long parentArray[1010101];
long long sizeArray[1010101];
long long valueArray[1010101];

struct Point {
    long long otherPoint, combinedWeight, halfWeight, index;
};

struct CompareByHalfWeight {
    bool operator()(Point &a, Point &b) {
        return a.halfWeight > b.halfWeight;
    }
};

struct CompareByIndex {
    bool operator()(Point &a, Point &b) {
        return a.index > b.index;
    }
};

queue<long long> indexQueue;

priority_queue<Point, vector<Point>, CompareByHalfWeight> priorityQueueByHalfWeight[303030];
priority_queue<Point, vector<Point>, CompareByIndex> finalQueue;

long long findRoot(long long x) {
    if (parentArray[x] == x) return x;
    return parentArray[x] = findRoot(parentArray[x]);
}

long long mergeSets(long long a, long long b) {
    a = findRoot(a);
    b = findRoot(b);
    if (priorityQueueByHalfWeight[a].size() <= priorityQueueByHalfWeight[b].size()) {
        parentArray[a] = b;
        valueArray[b] += valueArray[a];
        while (!priorityQueueByHalfWeight[a].empty()) {
            auto x = priorityQueueByHalfWeight[a].top();
            priorityQueueByHalfWeight[a].pop();
            if (findRoot(x.otherPoint) == b) continue;
            priorityQueueByHalfWeight[b].push(x);
        }
        return b;
    } else {
        parentArray[b] = a;
        valueArray[a] += valueArray[b];
        while (!priorityQueueByHalfWeight[b].empty()) {
            auto x = priorityQueueByHalfWeight[b].top();
            priorityQueueByHalfWeight[b].pop();
            if (findRoot(x.otherPoint) == a) continue;
            priorityQueueByHalfWeight[a].push(x);
        }
        return a;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    long long numNodes, numEdges;
    cin >> numNodes >> numEdges;
    
    if (numNodes == 1) {
        while (1);
    }
    
    for (long long i = 1; i <= numNodes; i++) {
        cin >> valueArray[i];
        parentArray[i] = i;
    }
    
    for (long long i = 1; i <= numEdges; i++) {
        long long nodeA, nodeB, weight;
        cin >> nodeA >> nodeB >> weight;
        
        if (valueArray[nodeA] + valueArray[nodeB] >= weight) {
            finalQueue.push({nodeA, nodeB, weight, i});
            continue;
        }
        
        priorityQueueByHalfWeight[nodeA].push({nodeB, weight, valueArray[nodeA] + (weight - valueArray[nodeA] - valueArray[nodeB] + 1) / 2, i});
        priorityQueueByHalfWeight[nodeB].push({nodeA, weight, valueArray[nodeB] + (weight - valueArray[nodeA] - valueArray[nodeB] + 1) / 2, i});
    }

    while (!finalQueue.empty()) {
        auto x = finalQueue.top();
        finalQueue.pop();
        
        long long nodeA = x.otherPoint;
        long long nodeB = x.combinedWeight;
        
        if (findRoot(nodeA) == findRoot(nodeB)) continue;
        
        indexQueue.push(x.index);

        long long mergedRoot = mergeSets(nodeA, nodeB);

        while (!priorityQueueByHalfWeight[mergedRoot].empty()) {
            auto k = priorityQueueByHalfWeight[mergedRoot].top();
            k.otherPoint = findRoot(k.otherPoint);
            
            if (findRoot(mergedRoot) == findRoot(k.otherPoint)) {
                priorityQueueByHalfWeight[mergedRoot].pop();
                continue;
            }
            
            if (valueArray[mergedRoot] < k.halfWeight) break;
            
            priorityQueueByHalfWeight[mergedRoot].pop();

            if (k.combinedWeight <= valueArray[mergedRoot] + valueArray[k.otherPoint]) {
                finalQueue.push({mergedRoot, k.otherPoint, k.index, k.index});
            } else {
                priorityQueueByHalfWeight[k.otherPoint].push({mergedRoot, k.combinedWeight, valueArray[k.otherPoint] + (k.combinedWeight - valueArray[k.otherPoint] - valueArray[mergedRoot] + 1) / 2, k.index});
                priorityQueueByHalfWeight[mergedRoot].push({k.otherPoint, k.combinedWeight, valueArray[mergedRoot] + (k.combinedWeight - valueArray[k.otherPoint] - valueArray[mergedRoot] + 1) / 2, k.index});
            }
        }
    }

    cout << indexQueue.size() << '\n';
    while (!indexQueue.empty()) {
        cout << indexQueue.front() << ' ';
        indexQueue.pop();
    }
}
