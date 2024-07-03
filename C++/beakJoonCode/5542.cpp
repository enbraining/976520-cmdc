#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

int numberOfNodes, numberOfEdges, numberOfFestivals, numberOfQueries;
vector<pair<int, int>> adjacencyList[200000];
vector<int> festivalLocations;
vector<int> shortestDistanceFromFestival(200000, 987654321); 

vector<tuple<int, int, int>> edges;
set<int> nodeParticipantInfo[200000];

int disjointSetParent[200000];
int disjointSetRank[200000];

int travelResult[200000];

void initializeDisjointSet() {
    for (int i = 0; i < 200000; i++) {
        disjointSetParent[i] = i;
        disjointSetRank[i] = 1;
    }
}

int findRoot(int node) {
    if (node == disjointSetParent[node]) {
        return node;
    }
    return disjointSetParent[node] = findRoot(disjointSetParent[node]);
}

void unionNodes(int node1, int node2) {
    node1 = findRoot(node1);
    node2 = findRoot(node2);

    if (node1 == node2) {
        return;
    }

    if (disjointSetRank[node1] < disjointSetRank[node2]) {
        disjointSetParent[node1] = node2;
    } else {
        disjointSetParent[node2] = node1;

        if (disjointSetRank[node1] == disjointSetRank[node2]) {
            disjointSetRank[node1]++;
        }
    }
}

void calculateShortestDistancesFromFestivals() {
    priority_queue<pair<int, int>> priorityQueue;

    for (int i = 0; i < festivalLocations.size(); i++) {
        priorityQueue.push(make_pair(0, festivalLocations[i]));
        shortestDistanceFromFestival[festivalLocations[i]] = 0;
    }

    while (!priorityQueue.empty()) {
        int currentNode = priorityQueue.top().second;
        int currentDistance = -priorityQueue.top().first;
        priorityQueue.pop();

        if (currentDistance > shortestDistanceFromFestival[currentNode]) {
            continue;
        }

        for (int i = 0; i < adjacencyList[currentNode].size(); i++) {
            int adjacentNode = adjacencyList[currentNode][i].second;
            int newDistance = currentDistance + adjacencyList[currentNode][i].first;

            if (newDistance < shortestDistanceFromFestival[adjacentNode]) {
                shortestDistanceFromFestival[adjacentNode] = newDistance;
                priorityQueue.push(make_pair(-newDistance, adjacentNode));
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    initializeDisjointSet();

    cin >> numberOfNodes >> numberOfEdges >> numberOfFestivals >> numberOfQueries;

    vector<pair<int, int>> tempEdges;
    for (int i = 0; i < numberOfEdges; i++) {
        int node1, node2, cost;
        cin >> node1 >> node2 >> cost;

        adjacencyList[node1].push_back(make_pair(cost, node2));
        adjacencyList[node2].push_back(make_pair(cost, node1));

        tempEdges.push_back(make_pair(node1, node2));
    }

    for (int i = 0; i < numberOfFestivals; i++) {
        int festivalLocation;
        cin >> festivalLocation;
        festivalLocations.push_back(festivalLocation);
    }
    calculateShortestDistancesFromFestivals();

    for (int i = 0; i < numberOfEdges; i++) {
        int node1 = tempEdges[i].first;
        int node2 = tempEdges[i].second;
        int festivalDistance = min(shortestDistanceFromFestival[node1], shortestDistanceFromFestival[node2]); // 해당 간선과 가장 가까운 축제와 거리

        edges.push_back(make_tuple(festivalDistance, node1, node2));
    }

    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());

    for (int i = 0; i < numberOfQueries; i++) {
        int startNode, destinationNode;
        cin >> startNode >> destinationNode;

        nodeParticipantInfo[startNode].insert(i);
        nodeParticipantInfo[destinationNode].insert(i);
    }

    for (int i = 0; i < edges.size(); i++) {
        int festivalDistance = get<0>(edges[i]);
        int node1 = get<1>(edges[i]);
        int node2 = get<2>(edges[i]);

        node1 = findRoot(node1);
        node2 = findRoot(node2);

        if (node1 == node2) {
            continue;
        }

        int largerComponentNode, smallerComponentNode; 
        if (disjointSetRank[node1] < disjointSetRank[node2]) {
            largerComponentNode = node2;
            smallerComponentNode = node1;
        } else {
            largerComponentNode = node1;
            smallerComponentNode = node2;
        }

        for (set<int>::iterator it = nodeParticipantInfo[smallerComponentNode].begin(); it != nodeParticipantInfo[smallerComponentNode].end(); it++) {
            int participant = (*it);

            if (nodeParticipantInfo[largerComponentNode].count(participant) != 0) { 
                travelResult[participant] = festivalDistance;
            }

            nodeParticipantInfo[largerComponentNode].insert(participant); 
        }

        unionNodes(node1, node2);
    }

    for (int i = 0; i < numberOfQueries; i++) {
        cout << travelResult[i] << "\n";
    }
    return 0;
}
