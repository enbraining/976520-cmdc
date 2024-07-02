import sys
input = sys.stdin.readline

def DepthFirstSearch(firstPoliceCarIndex, secondPoliceCarIndex):
    nextCaseIndex = max(firstPoliceCarIndex, secondPoliceCarIndex) + 1
    if nextCaseIndex == numberOfCases + 2:
        return
    if not distanceMemo[nextCaseIndex][secondPoliceCarIndex]:
        DepthFirstSearch(nextCaseIndex, secondPoliceCarIndex)
    if not distanceMemo[firstPoliceCarIndex][nextCaseIndex]:
        DepthFirstSearch(firstPoliceCarIndex, nextCaseIndex)  
    distanceFirstPath = distanceMemo[nextCaseIndex][secondPoliceCarIndex] + manhattanDistance[firstPoliceCarIndex][nextCaseIndex]
    distanceSecondPath = distanceMemo[firstPoliceCarIndex][nextCaseIndex] + manhattanDistance[secondPoliceCarIndex][nextCaseIndex]
    if distanceFirstPath < distanceSecondPath:
        distanceMemo[firstPoliceCarIndex][secondPoliceCarIndex], pathMemo[firstPoliceCarIndex][secondPoliceCarIndex] = distanceFirstPath, 1
    else:
        distanceMemo[firstPoliceCarIndex][secondPoliceCarIndex], pathMemo[firstPoliceCarIndex][secondPoliceCarIndex] = distanceSecondPath, 2

numberOfGridUnits, numberOfCases = int(input()), int(input())

caseCoordinates = [[1, 1], [numberOfGridUnits, numberOfGridUnits]] + [[*map(int, input().split())] for _ in range(numberOfCases)]
manhattanDistance = [[0] * (numberOfCases + 2) for _ in range(numberOfCases + 2)]
for caseIndex1 in range(numberOfCases + 1):
    for caseIndex2 in range(caseIndex1 + 1, numberOfCases + 2):
        manhattanDistance[caseIndex1][caseIndex2] = abs(caseCoordinates[caseIndex1][0] - caseCoordinates[caseIndex2][0]) + abs(caseCoordinates[caseIndex1][1] - caseCoordinates[caseIndex2][1])

distanceMemo, pathMemo = [[0] * (numberOfCases + 2) for _ in range(numberOfCases + 2)], [[0] * (numberOfCases + 2) for _ in range(numberOfCases + 2)]
DepthFirstSearch(0, 1)
print(distanceMemo[0][1])
firstPoliceCarIndex, secondPoliceCarIndex = 0, 1
while max(firstPoliceCarIndex, secondPoliceCarIndex) < numberOfCases + 1:
    print(pathMemo[firstPoliceCarIndex][secondPoliceCarIndex])
    if pathMemo[firstPoliceCarIndex][secondPoliceCarIndex] == 1:
        firstPoliceCarIndex = max(firstPoliceCarIndex, secondPoliceCarIndex) + 1
    else:
        secondPoliceCarIndex = max(firstPoliceCarIndex, secondPoliceCarIndex) + 1
