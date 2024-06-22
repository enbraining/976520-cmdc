import sys

num_lines = int(sys.stdin.readline())
points = [[] for _ in range(2 * num_lines)]
roots = [i for i in range(2 * num_lines)]
group_sizes = [1 for _ in range(2 * num_lines)]
visited = [False for _ in range(2 * num_lines)]

def find_root(node):
    if roots[node] != node:
        roots[node] = find_root(roots[node])
    return roots[node]

def union_nodes(a, b):
    root_a = find_root(a)
    root_b = find_root(b)
    if root_a == root_b:
        return True
    if root_a < root_b:
        root_a, root_b = root_b, root_a
    roots[root_a] = root_b
    group_sizes[root_b] += group_sizes[root_a]
    return False

def ccw(a1, b1, a2, b2, a3, b3):
    return a1 * b2 + a2 * b3 + a3 * b1 - b1 * a2 - b2 * a3 - b3 * a1

def check_intersection(a, b):
    l1 = ccw(a[0], a[1], a[2], a[3], b[0], b[1]) * ccw(a[0], a[1], a[2], a[3], b[2], b[3])
    l2 = ccw(b[0], b[1], b[2], b[3], a[0], a[1]) * ccw(b[0], b[1], b[2], b[3], a[2], a[3])
    if l1 <= 0 and l2 <= 0:
        if l1 == 0 and l2 == 0:
            d1 = max(a[0], a[2]) >= min(b[0], b[2]) and max(b[0], b[2]) >= min(a[0], a[2])
            d2 = max(a[1], a[3]) >= min(b[1], b[3]) and max(b[1], b[3]) >= min(a[1], a[3])
            if d1 and d2:
                return True
            return False
        else:
            return True
    return False

for i in range(num_lines):
    x1, y1, x2, y2 = list(map(int, sys.stdin.readline().split()))
    points[2 * i] = (x1, y1)
    points[2 * i + 1] = (x2, y2)
    union_nodes(2 * i, 2 * i + 1)

    for j in range(i):
        line_a = (x1, y1, x2, y2)
        line_b = (points[2 * j][0], points[2 * j][1], points[2 * j + 1][0], points[2 * j + 1][1])
        if check_intersection(line_a, line_b):
            union_nodes(2 * i, 2 * j)

distinct_groups = []
for i in range(2 * num_lines):
    if visited[i]:
        continue
    root = find_root(i)
    distinct_groups.append(root)
    for j in range(2 * num_lines):
        if root == find_root(j):
            visited[j] = True

max_group_size = 0
for root in distinct_groups:
    max_group_size = max(max_group_size, group_sizes[root])

print(len(distinct_groups))
print(max_group_size // 2)
