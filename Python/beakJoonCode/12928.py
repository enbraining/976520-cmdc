numberOfElements, targetSum = map(int, input().split())
combinations = [i * (i + 1) // 2 for i in range(numberOfElements)]
dynamicProgramming = [set() for _ in range(targetSum + 1)]
dynamicProgramming[0] = {(i, i) for i in range(numberOfElements + 1)}

for currentIndex in range(numberOfElements):
    currentCombination = combinations[currentIndex]
    for currentSum in range(1, targetSum + 1):
        if currentSum - currentCombination < 0:
            continue
        for elementCount, totalIndex in dynamicProgramming[currentSum - currentCombination]:
            if elementCount + 1 <= numberOfElements and totalIndex + currentIndex + 1 <= 2 * numberOfElements - 2:
                dynamicProgramming[currentSum].add((elementCount + 1, totalIndex + currentIndex + 1))

print(int((numberOfElements, 2 * numberOfElements - 2) in dynamicProgramming[targetSum]))
