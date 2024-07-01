#include <bits/stdc++.h>
using namespace std;

#define MAXN 100005

int lengthOfString;
char inputString[MAXN];

vector<int> computeZFunction(const string &str) {
    int strLength = str.length();
    vector<int> z(strLength, 0);
    for (int i = 1, left = 0, right = 0; i < strLength; i++) {
        if (i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < strLength && str[i + z[i]] == str[z[i]]) {
            z[i]++;
        }
        if (right < i + z[i] - 1) {
            right = i + z[i] - 1;
            left = i;
        }
    }
    return z;
}

int main() {
    scanf("%s", inputString);
    lengthOfString = strlen(inputString);

    auto zFunctionValues = computeZFunction(inputString);
    zFunctionValues[0] = lengthOfString;

    auto sortedZValues = zFunctionValues;
    sort(sortedZValues.begin(), sortedZValues.end());

    vector<pair<int, int>> results;
    for (int i = lengthOfString; i--;) {
        if (i + zFunctionValues[i] == lengthOfString) {
            int occurrences = sortedZValues.end() - lower_bound(sortedZValues.begin(), sortedZValues.end(), zFunctionValues[i]);
            results.push_back({zFunctionValues[i], occurrences});
        }
    }

    printf("%d\n", (int)results.size());
    for (auto [length, count] : results) {
        printf("%d %d\n", length, count);
    }
}
