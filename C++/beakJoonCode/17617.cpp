#include <cstdio>
#include <algorithm>
using namespace std;

int numRobots, radius, perimeter;
int robotPositions[1000005];
int adjustedDifferences[2000005];

int currentSum, maxSum;

int main() {
    scanf("%d", &numRobots);
    scanf("%d %d", &radius, &perimeter);

    for (int i = 0; i < numRobots; i++) {
        scanf("%d", &robotPositions[i]);
    }

    sort(robotPositions, robotPositions + numRobots);
    robotPositions[numRobots] = robotPositions[0] + perimeter;

    for (int i = 0; i < numRobots; i++) {
        adjustedDifferences[i] = adjustedDifferences[i + numRobots] = robotPositions[i + 1] - robotPositions[i] - 2 * radius;
    }

    for (int i = 0; i < 2 * numRobots - 1; i++) {
        currentSum += adjustedDifferences[i];

        if (currentSum < 0) {
            currentSum = 0;
        }

        if (maxSum < currentSum) {
            maxSum = currentSum;
        }
    }

    printf("%d", (maxSum + 1) / 2);
    return 0;
}
