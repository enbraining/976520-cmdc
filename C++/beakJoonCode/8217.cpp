#include <bits/stdc++.h>
#define push_back_element push_back
#define vector_size(v) ((int)(v).size())
#define sort_all(v) (v).begin(), (v).end()

using namespace std;

typedef long long int64;
const int MODULO = 1e9 + 7;
const int INFINITY_INT = 0x3c3c3c3c;
const long long INFINITY_LONG = 0x3c3c3c3c3c3c3c3c;

struct RangeQuery {
    int left, right, value;
};

int numTerritories, numDays, numQueries;
long long binaryIndexedTree[400000];
int lowIndex[400000], highIndex[400000];
int requiredResources[400000];
RangeQuery queries[400000];
vector<int> queryIndicesPerMidpoint[400000];
vector<int> territoriesPerResource[400000];

void updateBinaryIndexedTree(int position, int value) {
    while (position <= numDays) {
        binaryIndexedTree[position] += value;
        position += position & -position;
    }
}

long long queryBinaryIndexedTree(int position) {
    long long result = 0;
    while (position > 0) {
        result += binaryIndexedTree[position];
        position -= position & -position;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> numTerritories >> numDays;
    for (int day = 1; day <= numDays; day++) {
        int territory;
        cin >> territory;
        territoriesPerResource[territory].push_back_element(day);
    }
    for (int territory = 1; territory <= numTerritories; territory++) {
        cin >> requiredResources[territory];
    }
    cin >> numQueries;
    for (int queryIndex = 1; queryIndex <= numQueries; queryIndex++) {
        int left, right, value;
        cin >> left >> right >> value;
        queries[queryIndex] = {left, right, value};
    }
    for (int territory = 1; territory <= numTerritories; territory++) {
        lowIndex[territory] = 1;
        highIndex[territory] = numQueries + 1;
    }

    while (true) {
        bool isEnd = true;
        for (int territory = 1; territory <= numTerritories; territory++) {
            if (lowIndex[territory] < highIndex[territory]) {
                isEnd = false;
                int mid = (lowIndex[territory] + highIndex[territory]) / 2;
                queryIndicesPerMidpoint[mid].push_back_element(territory);
            }
        }
        if (isEnd) break;
        memset(binaryIndexedTree, 0, sizeof(binaryIndexedTree));
        for (int queryIndex = 1; queryIndex <= numQueries; queryIndex++) {
            auto query = queries[queryIndex];
            if (query.left > query.right) {
                updateBinaryIndexedTree(query.left, query.value);
                updateBinaryIndexedTree(1, query.value);
                updateBinaryIndexedTree(query.right + 1, -query.value);
            } else {
                updateBinaryIndexedTree(query.left, query.value);
                updateBinaryIndexedTree(query.right + 1, -query.value);
            }
            while (vector_size(queryIndicesPerMidpoint[queryIndex])) {
                int territory = queryIndicesPerMidpoint[queryIndex].back();
                queryIndicesPerMidpoint[queryIndex].pop_back();
                long long totalResources = 0;
                for (int resourceDay : territoriesPerResource[territory]) {
                    totalResources += queryBinaryIndexedTree(resourceDay);
                    if (totalResources >= requiredResources[territory]) break;
                }
                if (totalResources >= requiredResources[territory]) {
                    highIndex[territory] = queryIndex;
                } else {
                    lowIndex[territory] = queryIndex + 1;
                }
            }
        }
    }

    for (int territory = 1; territory <= numTerritories; territory++) {
        if (lowIndex[territory] == numQueries + 1) {
            cout << "NIE\n";
        } else {
            cout << lowIndex[territory] << '\n';
        }
    }
    return 0;
}
