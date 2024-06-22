import sys
input = sys.stdin.readline
from heapq import heappush, heappop

def find_root(node):
    if parents[node] == node:
        return node
    parents[node] = find_root(parents[node])
    return parents[node]

num_vertices, num_edges = map(int, input().split())

min_heap = []
for _ in range(num_edges):
    vertex1, vertex2, weight = map(int, input().split())
    heappush(min_heap, (weight, vertex1, vertex2))

parents = {i: i for i in range(1, num_vertices + 1)}

total_weight = 0
while min_heap:
    weight, vertex1, vertex2 = heappop(min_heap)
    root1 = find_root(vertex1)
    root2 = find_root(vertex2)
    if root1 == root2:
        continue
    parents[root1] = root2
    total_weight += weight

print(total_weight)
