#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_SIZE = 200000;
int numPoles, numFlags, position = MAX_SIZE, result;
pair<int, int> polesAndFlags[MAX_SIZE];
vector<pair<int, int>> levelVectors[MAX_SIZE * 2];

int main() {
    scanf("%d%d", &numPoles, &numFlags);

    for (int i = 0; i < numPoles; i++) {
        scanf("%d", &polesAndFlags[i].first);
        polesAndFlags[i].second = 0;
    }

    for (int i = numPoles; i < numPoles + numFlags; i++) {
        scanf("%d", &polesAndFlags[i].first);
        polesAndFlags[i].second = 1;
    }

    sort(polesAndFlags, polesAndFlags + numPoles + numFlags);

    for (int i = 0; i < numPoles + numFlags; i++) {
        if (polesAndFlags[i].second) {
            levelVectors[--position].push_back(polesAndFlags[i]);
        } else {
            levelVectors[position++].push_back(polesAndFlags[i]);
        }
    }

    for (int i = 0; i < MAX_SIZE * 2; i++) {
        int sum = 0, minimumDifference;

        for (int j = 1; j < levelVectors[i].size(); j += 2) {
            sum += levelVectors[i][j].first - levelVectors[i][j - 1].first;
        }

        minimumDifference = sum;

        if (levelVectors[i].size() % 2 == 1) {
            for (int j = levelVectors[i].size() - 1; j > 1; j -= 2) {
                minimumDifference = min(minimumDifference, sum += levelVectors[i][j].first - 2 * levelVectors[i][j - 1].first + levelVectors[i][j - 2].first);
            }
        }

        result += minimumDifference;
    }

    printf("%d", result);
    return 0;
}
