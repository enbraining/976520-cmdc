import sys
sys.setrecursionlimit(1000000000) # 반복 제한 억까 방지

numberOfNodes, rootNode, numberOfQueries = map(int, sys.stdin.readline().split(' '))

adjacencyList = [[] for _ in range(numberOfNodes + 1)]
subtreeSizes = [-1 for _ in range(numberOfNodes + 1)]

for _ in range(numberOfNodes - 1):
    nodeA, nodeB = map(int, sys.stdin.readline().split(' '))
    adjacencyList[nodeA].append(nodeB)
    adjacencyList[nodeB].append(nodeA)

def depthFirstSearch(currentNode):
    global subtreeSizes
    subtreeSizes[currentNode] = 1 # 나자신을 추가
    for adjacentNode in adjacencyList[currentNode]:
        if subtreeSizes[adjacentNode] == -1: # 방문할 수 있는데 안한게 있으면
            subtreeSizes[currentNode] += depthFirstSearch(adjacentNode) # 바로찾아가서 섭트리 개수 +
    return subtreeSizes[currentNode]

depthFirstSearch(rootNode)

for _ in range(numberOfQueries):
    queryNode = int(sys.stdin.readline())
    print(subtreeSizes[queryNode])
