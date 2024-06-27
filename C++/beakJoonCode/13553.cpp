#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long fenwickTree[101010] = { 0 }, numElements;
void updateFenwickTree(int index, int value) {
    while (index <= 100000) {
        fenwickTree[index] += value;
        index += index & -index;
    }
}

int getFenwickTreeSum(int index) {
    int sum = 0;
    while (index > 0) {
        sum += fenwickTree[index];
        index -= index & -index;
    }
    return sum;
}

long long elementArray[101010] = { 0 }, currentAnswer = 0, sqrtNumElements, queryRange;

void addElementToRange(long long index) {
    currentAnswer += getFenwickTreeSum(min(elementArray[index] + queryRange, (long long)(100000))) - getFenwickTreeSum(max(elementArray[index] - queryRange - 1, (long long)(0)));
    updateFenwickTree(elementArray[index], 1);
}

void removeElementFromRange(long long index) {
    updateFenwickTree(elementArray[index], -1);
    currentAnswer -= getFenwickTreeSum(min(elementArray[index] + queryRange, (long long)(100000))) - getFenwickTreeSum(max(elementArray[index] - queryRange - 1, (long long)(0)));
}

bool compareQueries(pair<pair<long long, long long>, long long> queryA, pair<pair<long long, long long>, long long> queryB) {
    if (queryA.first.first / sqrtNumElements != queryB.first.first / sqrtNumElements) {
        return queryA.first.first < queryB.first.first;
    }
    return queryA.first.second < queryB.first.second;
}

long long queryResults[101010] = { 0 };

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long numQueries, i, left, right;
    vector<pair<pair<long long, long long>, long long>> queries;

    cin >> numElements >> queryRange;
    sqrtNumElements = sqrt(numElements);
    for (i = 1; i <= numElements; i++) {
        cin >> elementArray[i];
    }

    cin >> numQueries;
    for (i = 1; i <= numQueries; i++) {
        cin >> left >> right;
        queries.push_back({ {left, right}, i });
    }
    sort(queries.begin(), queries.end(), compareQueries);

    long long start = 1, end = 1;
    addElementToRange(1);
    for (i = 0; i < numQueries; i++) {
        pair<long long, long long> currentQuery = queries[i].first;
        while (start > currentQuery.first) addElementToRange(--start);
        while (end < currentQuery.second) addElementToRange(++end);
        while (start < currentQuery.first) removeElementFromRange(start++);
        while (end > currentQuery.second) removeElementFromRange(end--);

        queryResults[queries[i].second] = currentAnswer;
    }

    for (i = 1; i <= numQueries; i++) {
        cout << queryResults[i] << "\n";
    }
}
