#include <bits/stdc++.h>
using namespace std;

const int blockSize = 300;

struct Query {
    int start, end, index;
    bool operator < (const Query& otherQuery) const {
        if (start / blockSize != otherQuery.start / blockSize) {
            return start < otherQuery.start;
        }
        return end < otherQuery.end;
    }
};

int arraySize, xorTarget, queryCount;
int prefixXorArray[101010];
long long queryResults[101010];
vector<Query> queries;
long long currentAnswer;
long long xorCount[1 << 21];

int currentStart, currentEnd;

void insertAtLeft(int position) {
    xorCount[prefixXorArray[position]]++;
    currentAnswer += xorCount[xorTarget ^ prefixXorArray[position - 1]];
}

void insertAtRight(int position) {
    currentAnswer += xorCount[xorTarget ^ prefixXorArray[position]];
    currentAnswer += prefixXorArray[currentStart - 1] == (xorTarget ^ prefixXorArray[position]);
    xorCount[prefixXorArray[position]]++;
}

void eraseAtLeft(int position) {
    currentAnswer -= xorCount[xorTarget ^ prefixXorArray[position - 1]];
    xorCount[prefixXorArray[position]]--;
}

void eraseAtRight(int position) {
    currentAnswer -= xorCount[xorTarget ^ prefixXorArray[position]];
    currentAnswer -= prefixXorArray[currentStart - 1] == (xorTarget ^ prefixXorArray[position]);
    xorCount[prefixXorArray[position]]--;
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    cin >> arraySize >> xorTarget;
    for (int i = 1; i <= arraySize; i++) {
        cin >> prefixXorArray[i];
    }

    for (int i = 1; i <= arraySize; i++) {
        prefixXorArray[i] ^= prefixXorArray[i - 1];
    }

    cin >> queryCount;
    for (int i = 0; i < queryCount; i++) {
        int start, end;
        cin >> start >> end;
        queries.push_back({ start, end, i });
    }

    sort(queries.begin(), queries.end());

    currentStart = currentEnd = queries[0].start;
    xorCount[prefixXorArray[currentStart]] = 1;
    if ((prefixXorArray[currentStart] ^ prefixXorArray[currentStart - 1]) == xorTarget) {
        currentAnswer++;
    }

    while (currentEnd < queries[0].end) {
        insertAtRight(++currentEnd);
    }
    queryResults[queries[0].index] = currentAnswer;

    for (int i = 1; i < queryCount; i++) {
        while (queries[i].start < currentStart) {
            insertAtLeft(--currentStart);
        }
        while (queries[i].end > currentEnd) {
            insertAtRight(++currentEnd);
        }
        while (queries[i].start > currentStart) {
            eraseAtLeft(currentStart++);
        }
        while (queries[i].end < currentEnd) {
            eraseAtRight(currentEnd--);
        }
        queryResults[queries[i].index] = currentAnswer;
        if (currentAnswer < 0) {
            return -1;
        }
    }

    for (int i = 0; i < queryCount; i++) {
        cout << queryResults[i] << "\n";
    }

    return 0;
}
