#include <iostream>
#include <algorithm>
using namespace std;

int numberOfSections, maxWeight;
int sectionWeights[2][10004];
int minMovesWithSingleWeight[10004], minMovesWithWeightPair[10004], minMovesWithoutWeightPair[10004];

void calculateMinMoves() {
    if (sectionWeights[0][0] + sectionWeights[1][0] <= maxWeight) {
        minMovesWithSingleWeight[0] = minMovesWithWeightPair[0] = minMovesWithoutWeightPair[0] = 1;
    }
    else {
        minMovesWithSingleWeight[0] = 2;
        minMovesWithWeightPair[0] = minMovesWithoutWeightPair[0] = 1;
    }

    for (int sectionIndex = 1; sectionIndex < numberOfSections; sectionIndex++) {
        minMovesWithSingleWeight[sectionIndex] = minMovesWithSingleWeight[sectionIndex - 1] + 2;
        minMovesWithWeightPair[sectionIndex] = minMovesWithoutWeightPair[sectionIndex] = minMovesWithSingleWeight[sectionIndex - 1] + 1;

        if (sectionWeights[0][sectionIndex] + sectionWeights[0][sectionIndex - 1] <= maxWeight) {
            minMovesWithWeightPair[sectionIndex] = min(minMovesWithWeightPair[sectionIndex], minMovesWithoutWeightPair[sectionIndex - 1] + 1);
        }
        if (sectionWeights[1][sectionIndex] + sectionWeights[1][sectionIndex - 1] <= maxWeight) {
            minMovesWithoutWeightPair[sectionIndex] = min(minMovesWithoutWeightPair[sectionIndex], minMovesWithWeightPair[sectionIndex - 1] + 1);
        }
        minMovesWithSingleWeight[sectionIndex] = min(minMovesWithSingleWeight[sectionIndex], minMovesWithWeightPair[sectionIndex] + 1);
        minMovesWithSingleWeight[sectionIndex] = min(minMovesWithSingleWeight[sectionIndex], minMovesWithoutWeightPair[sectionIndex] + 1);

        if (sectionWeights[0][sectionIndex] + sectionWeights[1][sectionIndex] <= maxWeight) {
            minMovesWithSingleWeight[sectionIndex] = min(minMovesWithSingleWeight[sectionIndex], minMovesWithSingleWeight[sectionIndex - 1] + 1);
        }
        if (sectionWeights[0][sectionIndex] + sectionWeights[0][sectionIndex - 1] <= maxWeight && sectionWeights[1][sectionIndex] + sectionWeights[1][sectionIndex - 1] <= maxWeight) {
            if (sectionIndex >= 2) {
                minMovesWithSingleWeight[sectionIndex] = min(minMovesWithSingleWeight[sectionIndex], minMovesWithSingleWeight[sectionIndex - 2] + 2);
            }
            else {
                minMovesWithSingleWeight[sectionIndex] = min(minMovesWithSingleWeight[sectionIndex], 2);
            }
        }
    }
}

void processTestCases() {
    cin >> numberOfSections >> maxWeight;
    for (int rowIndex = 0; rowIndex < 2; rowIndex++) {
        for (int colIndex = 0; colIndex < numberOfSections; colIndex++) {
            cin >> sectionWeights[rowIndex][colIndex];
        }
    }
    int minimumMovesRequired;

    calculateMinMoves();
    minimumMovesRequired = minMovesWithSingleWeight[numberOfSections - 1];

    if (numberOfSections > 1) {
        if (sectionWeights[1][0] + sectionWeights[1][numberOfSections - 1] <= maxWeight) {
            int tempFirst = sectionWeights[1][0];
            int tempLast = sectionWeights[1][numberOfSections - 1];
            sectionWeights[1][0] = sectionWeights[1][numberOfSections - 1] = maxWeight;
            calculateMinMoves();
            minimumMovesRequired = min(minimumMovesRequired, minMovesWithWeightPair[numberOfSections - 1]);
            sectionWeights[1][0] = tempFirst;
            sectionWeights[1][numberOfSections - 1] = tempLast;
        }
        if (sectionWeights[0][0] + sectionWeights[0][numberOfSections - 1] <= maxWeight) {
            int tempFirst = sectionWeights[0][0];
            int tempLast = sectionWeights[0][numberOfSections - 1];
            sectionWeights[0][0] = sectionWeights[0][numberOfSections - 1] = maxWeight;
            calculateMinMoves();
            minimumMovesRequired = min(minimumMovesRequired, minMovesWithoutWeightPair[numberOfSections - 1]);
            sectionWeights[0][0] = tempFirst;
            sectionWeights[0][numberOfSections - 1] = tempLast;
        }
        if (sectionWeights[0][0] + sectionWeights[0][numberOfSections - 1] <= maxWeight && sectionWeights[1][0] + sectionWeights[1][numberOfSections - 1] <= maxWeight) {
            int tempFirst0 = sectionWeights[0][0];
            int tempLast0 = sectionWeights[0][numberOfSections - 1];
            int tempFirst1 = sectionWeights[1][0];
            int tempLast1 = sectionWeights[1][numberOfSections - 1];
            sectionWeights[1][0] = sectionWeights[1][numberOfSections - 1] = maxWeight;
            sectionWeights[0][0] = sectionWeights[0][numberOfSections - 1] = maxWeight;
            calculateMinMoves();
            minimumMovesRequired = min(minimumMovesRequired, minMovesWithSingleWeight[numberOfSections - 2]);
            sectionWeights[0][0] = tempFirst0;
            sectionWeights[0][numberOfSections - 1] = tempLast0;
            sectionWeights[1][0] = tempFirst1;
            sectionWeights[1][numberOfSections - 1] = tempLast1;
        }
    }
    cout << minimumMovesRequired << endl;
}

int main() {
    int numberOfTestCases;
    cin >> numberOfTestCases;
    while (numberOfTestCases--) {
        processTestCases();
    }
}
