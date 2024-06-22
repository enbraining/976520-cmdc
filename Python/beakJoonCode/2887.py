import sys
input = sys.stdin.readline

def find_parent(node):
    if parent[node] != node:
        parent[node] = find_parent(parent[node])
    return parent[node]

def union_nodes(node_a, node_b):
    root_a = find_parent(node_a)
    root_b = find_parent(node_b)
    if root_a > root_b:
        parent[root_b] = root_a
    else:
        parent[root_a] = root_b

number_of_stars = int(input())
stars = [tuple([i] + list(map(int, input().rstrip().split()))) for i in range(number_of_stars)]

edges = []
for dim_index in [1, 2, 3]:
    sorted_stars = sorted(stars, key=lambda x: x[dim_index]) 
    edges += [(abs(star1[dim_index] - star2[dim_index]), star1[0], star2[0]) for star1, star2 in zip(sorted_stars[:-1], sorted_stars[1:])]

edges.sort()

total_distance = 0
parent = list(range(number_of_stars + 1))
for distance, star1_index, star2_index in edges:
    if find_parent(star1_index) != find_parent(star2_index):
        union_nodes(star1_index, star2_index)
        total_distance += distance

print(total_distance)
