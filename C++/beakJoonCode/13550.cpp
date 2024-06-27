#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <list>
using namespace std;

long long numberOfElements, squareRootOfN;
bool comparePairs(pair<pair<long long, long long>, long long> firstPair, pair<pair<long long, long long>, long long> secondPair) {
    if (firstPair.first.first / squareRootOfN != secondPair.first.first / squareRootOfN) {
        return firstPair.first.first < secondPair.first.first;
    }
    return firstPair.first.second < secondPair.first.second;
}

list<long long> dequeOfSums[1010101];
long long countOfRanges[101010] = { 0 }, bucketCount[1010] = { 0 };
long long arrayOfElements[101010] = { 0 }, prefixSums[101010] = { 0 };
void addElement(long long index, long long direction) {
    long long currentRange;
    if (dequeOfSums[prefixSums[index]].size()) {
        currentRange = dequeOfSums[prefixSums[index]].back() - dequeOfSums[prefixSums[index]].front();
        countOfRanges[currentRange]--;
        bucketCount[currentRange / squareRootOfN]--;
    }
    if (direction == 1) {
        dequeOfSums[prefixSums[index]].push_back(index);
    } else {
        dequeOfSums[prefixSums[index]].push_front(index);
    }

    currentRange = dequeOfSums[prefixSums[index]].back() - dequeOfSums[prefixSums[index]].front();
    countOfRanges[currentRange]++;
    bucketCount[currentRange / squareRootOfN]++;
}
void removeElement(long long index, long long direction) {
    long long currentRange;

    currentRange = dequeOfSums[prefixSums[index]].back() - dequeOfSums[prefixSums[index]].front();
    countOfRanges[currentRange]--;
    bucketCount[currentRange / squareRootOfN]--;

    if (direction == 1) {
        dequeOfSums[prefixSums[index]].pop_back();
    } else {
        dequeOfSums[prefixSums[index]].pop_front();
    }
    if (dequeOfSums[prefixSums[index]].size()) {
        currentRange = dequeOfSums[prefixSums[index]].back() - dequeOfSums[prefixSums[index]].front();
        countOfRanges[currentRange]++;
        bucketCount[currentRange / squareRootOfN]++;
    }
}

long long findMaxRange() {
    long long i, j;
    for (i = numberOfElements / squareRootOfN; i >= 0; i--) {
        if (bucketCount[i] == 0) {
            continue;
        }
        for (j = (i + 1) * squareRootOfN - 1; j >= i * squareRootOfN; j--) {
            if (countOfRanges[j] == 0) {
                continue;
            }
            return j;
        }
    }
}

long long answer[101010] = { 0 };
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long modulo, i, numberOfQueries, startRange, endRange;
    vector<pair<pair<long long, long long>, long long>> queries;

    cin >> numberOfElements >> modulo;
    squareRootOfN = sqrt(numberOfElements);
    for (i = 1; i <= numberOfElements; i++) {
        cin >> arrayOfElements[i];
        prefixSums[i] = prefixSums[i - 1] + arrayOfElements[i];
        prefixSums[i] %= modulo;
    }

    cin >> numberOfQueries;
    for (i = 1; i <= numberOfQueries; i++) {
        cin >> startRange >> endRange;
        queries.push_back({ {startRange - 1, endRange}, i });
    }
    sort(queries.begin(), queries.end(), comparePairs);

    long long currentStart = 0, currentEnd = 0;
    addElement(0, 1);
    for (i = 0; i < numberOfQueries; i++) {
        pair<long long, long long> currentQuery = queries[i].first;
        while (currentStart > currentQuery.first) addElement(--currentStart, -1);
        while (currentEnd < currentQuery.second) addElement(++currentEnd, 1);
        while (currentStart < currentQuery.first) removeElement(currentStart++, -1);
        while (currentEnd > currentQuery.second) removeElement(currentEnd--, 1);

        answer[queries[i].second] = findMaxRange();
    }

    for (i = 1; i <= numberOfQueries; i++) {
        cout << answer[i] << "\n";
    }
}
