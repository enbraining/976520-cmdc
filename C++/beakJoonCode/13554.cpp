#include<bits/stdc++.h>
#define SIZE 100010
using namespace std;

struct QueryStructure {
    int StartIndex, EndIndex, KValue, QueryIndex;
};

QueryStructure queries[SIZE];
int numberOfElements, numberOfQueries, elementsArray[2][SIZE], sqrtOfN;
long long segmentTree[2][SIZE], resultArray[SIZE];

bool compareQueries(QueryStructure firstQuery, QueryStructure secondQuery) {
    if(firstQuery.StartIndex / sqrtOfN == secondQuery.StartIndex / sqrtOfN) 
        return firstQuery.EndIndex < secondQuery.EndIndex;
    return firstQuery.StartIndex < secondQuery.StartIndex;
}

void updateSegmentTree(int index, long long weight, int arrayIndex) {
    index = elementsArray[arrayIndex][index];
    while(index <= SIZE) {
        segmentTree[arrayIndex][index] += weight;
        index += (index & -index);
    }
}

long long sumSegmentTree(int index, int arrayIndex) {
    long long sumResult = 0;
    while(index > 0) {
        sumResult += segmentTree[arrayIndex][index];
        index -= (index & -index);
    }
    return sumResult;
}

long long querySegmentTree(int startIndex, int endIndex, int arrayIndex) {
    return sumSegmentTree(endIndex, arrayIndex) - sumSegmentTree(startIndex - 1, arrayIndex);
}

int main() {
    cin >> numberOfElements;
    sqrtOfN = sqrt(numberOfElements);

    for(int i = 0; i < 2; i++)
        for(int j = 1; j <= numberOfElements; j++)
            scanf("%d", &elementsArray[i][j]);

    cin >> numberOfQueries;

    for(int i = 0; i < numberOfQueries; i++) {
        scanf("%d %d %d", &queries[i].StartIndex, &queries[i].EndIndex, &queries[i].KValue);
        queries[i].QueryIndex = i;
    }

    sort(queries, queries + numberOfQueries, compareQueries);

    int currentStartIndex = queries[0].StartIndex;
    int currentEndIndex = queries[0].EndIndex;
    int currentKValue = queries[0].KValue;
    int currentQueryIndex = queries[0].QueryIndex;

    for(int i = currentStartIndex; i <= currentEndIndex; i++) {
        updateSegmentTree(i, 1, 0);
        updateSegmentTree(i, 1, 1);
    }

    for(int i = 1; i <= sqrt(currentKValue); i++) {
        resultArray[currentQueryIndex] += querySegmentTree(i, i, 0) * querySegmentTree(1, currentKValue / i, 1) + querySegmentTree(i, i, 1) * querySegmentTree(sqrt(currentKValue) + 1, currentKValue / i, 0);
    }

    for(int i = 1; i < numberOfQueries; i++) {
        currentKValue = queries[i].KValue;
        currentQueryIndex = queries[i].QueryIndex;

        while(currentStartIndex < queries[i].StartIndex) {
            updateSegmentTree(currentStartIndex, -1, 0);
            updateSegmentTree(currentStartIndex, -1, 1);
            currentStartIndex++;
        }

        while(currentStartIndex > queries[i].StartIndex) {
            currentStartIndex--;
            updateSegmentTree(currentStartIndex, 1, 0);
            updateSegmentTree(currentStartIndex, 1, 1);
        }

        while(currentEndIndex < queries[i].EndIndex) {
            currentEndIndex++;
            updateSegmentTree(currentEndIndex, 1, 0);
            updateSegmentTree(currentEndIndex, 1, 1);
        }

        while(currentEndIndex > queries[i].EndIndex) {
            updateSegmentTree(currentEndIndex, -1, 0);
            updateSegmentTree(currentEndIndex, -1, 1);
            currentEndIndex--;
        }

        for(int i = 1; i <= sqrt(currentKValue); i++) {
            resultArray[currentQueryIndex] += querySegmentTree(i, i, 0) * querySegmentTree(1, currentKValue / i, 1) + querySegmentTree(i, i, 1) * querySegmentTree(sqrt(currentKValue) + 1, currentKValue / i, 0);
        }
    }

    for(int i = 0; i < numberOfQueries; i++) {
        printf("%lld\n", resultArray[i]);
    }
}
