#include <bits/stdc++.h>
using namespace std;

string firstString, secondString, longestCommonSubsequence;

void findLongestCommonSubsequence(int startFirstString, int endFirstString, int startSecondString, int endSecondString) {
    if (startFirstString > endFirstString) {
        return;
    }
    if (startFirstString == endFirstString) {
        for (int index = startSecondString; index <= endSecondString; index++) {
            if (secondString[index] == firstString[startFirstString]) {
                longestCommonSubsequence.push_back(secondString[index]);
                break;
            }
        }
        return;
    }

    int middleFirstString = (startFirstString + endFirstString) >> 1;
    vector<int> leftSubsequenceLengths(endSecondString - startSecondString + 3);
    vector<int> rightSubsequenceLengths(endSecondString - startSecondString + 3);
    vector<int> previousLengths(endSecondString - startSecondString + 3);

    for (int firstStringIndex = startFirstString; firstStringIndex <= middleFirstString; firstStringIndex++) {
        for (int secondStringIndex = startSecondString; secondStringIndex <= endSecondString; secondStringIndex++) {
            if (firstString[firstStringIndex] == secondString[secondStringIndex]) {
                leftSubsequenceLengths[secondStringIndex - startSecondString + 1] = previousLengths[secondStringIndex - startSecondString] + 1;
            } else {
                leftSubsequenceLengths[secondStringIndex - startSecondString + 1] = max(leftSubsequenceLengths[secondStringIndex - startSecondString], previousLengths[secondStringIndex - startSecondString + 1]);
            }
        }
        previousLengths = leftSubsequenceLengths;
    }

    fill(previousLengths.begin(), previousLengths.end(), 0);

    for (int firstStringIndex = endFirstString; firstStringIndex > middleFirstString; firstStringIndex--) {
        for (int secondStringIndex = endSecondString; secondStringIndex >= startSecondString; secondStringIndex--) {
            if (firstString[firstStringIndex] == secondString[secondStringIndex]) {
                rightSubsequenceLengths[secondStringIndex - startSecondString + 1] = previousLengths[secondStringIndex - startSecondString + 2] + 1;
            } else {
                rightSubsequenceLengths[secondStringIndex - startSecondString + 1] = max(rightSubsequenceLengths[secondStringIndex - startSecondString + 2], previousLengths[secondStringIndex - startSecondString + 1]);
            }
        }
        previousLengths = rightSubsequenceLengths;
    }

    int maxLength = -1;
    int bestIndex = 0;
    for (int secondStringIndex = startSecondString; secondStringIndex <= endSecondString + 1; secondStringIndex++) {
        if (maxLength < leftSubsequenceLengths[secondStringIndex - startSecondString] + rightSubsequenceLengths[secondStringIndex - startSecondString + 1]) {
            maxLength = leftSubsequenceLengths[secondStringIndex - startSecondString] + rightSubsequenceLengths[secondStringIndex - startSecondString + 1];
            bestIndex = secondStringIndex;
        }
    }

    findLongestCommonSubsequence(startFirstString, middleFirstString, startSecondString, bestIndex - 1);
    findLongestCommonSubsequence(middleFirstString + 1, endFirstString, bestIndex, endSecondString);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> firstString >> secondString;
    findLongestCommonSubsequence(0, firstString.size() - 1, 0, secondString.size() - 1);
    cout << longestCommonSubsequence.size() << '\n' << longestCommonSubsequence << '\n';
}
