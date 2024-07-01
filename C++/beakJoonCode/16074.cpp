#include <bits/stdc++.h>
using namespace std;

int getIdentifier(int row, int col) {
    return 1000 * row + col;
}

int unionFindArray[501501];

int findRoot(int node) {
    return unionFindArray[node] = (unionFindArray[node] == node ? node : findRoot(unionFindArray[node]));
}

void unionMerge(int node1, int node2) {
    int root1 = findRoot(node1);
    int root2 = findRoot(node2);

    if (root1 != root2) {
        unionFindArray[root1] = root2;
    }
}

struct Query {
    int x1, y1, x2, y2;
    int leftBound, rightBound;
};

int matrix[501][501];
vector<Query> queries;
vector<vector<pair<int, int>>> gridByValue;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int numRows, numCols, numQueries, maxValue = 0;
    cin >> numRows >> numCols >> numQueries;

    for (int row = 1; row <= numRows; row++) {
        for (int col = 1; col <= numCols; col++) {
            cin >> matrix[row][col];
            maxValue = max(maxValue, matrix[row][col]);
        }
    }

    gridByValue.resize(maxValue + 1);
    for (int row = 1; row <= numRows; row++) {
        for (int col = 1; col <= numCols; col++) {
            gridByValue[matrix[row][col]].emplace_back(row, col);
        }
    }

    for (int i = 0; i < numQueries; i++) {
        Query query{};
        cin >> query.x1 >> query.y1 >> query.x2 >> query.y2;
        query.leftBound = 1;
        query.rightBound = maxValue + 1;
        queries.push_back(query);
    }

    while (true) {
        bool anyUpdate = false;
        vector<vector<int>> midPoints(maxValue + 1);

        for (int i = 0; i < numQueries; i++) {
            if (queries[i].leftBound != queries[i].rightBound) {
                anyUpdate = true;
                midPoints[(queries[i].leftBound + queries[i].rightBound) >> 1].push_back(i);
            }
        }

        if (!anyUpdate) break;

        for (int i = 1; i < 501501; i++) {
            unionFindArray[i] = i;
        }

        for (int value = 1; value <= maxValue; value++) {
            for (const auto &cell : gridByValue[value]) {
                int row = cell.first, col = cell.second;
                if (matrix[row][col] == value) {
                    if (row > 1 && matrix[row - 1][col] <= value) {
                        unionMerge(getIdentifier(row, col), getIdentifier(row - 1, col));
                    }
                    if (col > 1 && matrix[row][col - 1] <= value) {
                        unionMerge(getIdentifier(row, col), getIdentifier(row, col - 1));
                    }
                    if (row < numRows && matrix[row + 1][col] <= value) {
                        unionMerge(getIdentifier(row, col), getIdentifier(row + 1, col));
                    }
                    if (col < numCols && matrix[row][col + 1] <= value) {
                        unionMerge(getIdentifier(row, col), getIdentifier(row, col + 1));
                    }
                }
            }

            for (const auto &queryIndex : midPoints[value]) {
                Query &query = queries[queryIndex];
                if (matrix[query.x1][query.y1] <= value && findRoot(getIdentifier(query.x1, query.y1)) == findRoot(getIdentifier(query.x2, query.y2))) {
                    query.rightBound = value;
                } else {
                    query.leftBound = value + 1;
                }
            }
        }
    }

    for (const auto &query : queries) {
        cout << ((query.leftBound + query.rightBound) >> 1) << "\n";
    }
}
