import sys
input = sys.stdin.readline
def union_sets(node_a, node_b):
    root_a = find_parent(node_a)
    root_b = find_parent(node_b)
    if root_a > root_b:
        disjoint_set[root_a] = root_b
    else:
        disjoint_set[root_b] = root_a
def find_parent(node):
    if node != disjoint_set[node]:
        disjoint_set[node] = find_parent(disjoint_set[node])
    return disjoint_set[node]
def count_nodes_in_same_set(parent_node):
    count = 0
    for node in range(1, total_nodes + 1):
        if find_parent(node) == parent_node:
            count += 1
    return count

total_nodes, total_edges, skipped_edge_index = map(int, input().split())

disjoint_set = [i for i in range(total_nodes + 1)]

skipped_node_u, skipped_node_v = 0, 0

for edge_index in range(total_edges):
    node_u, node_v = map(int, input().split())
    if edge_index != skipped_edge_index - 1:
        union_sets(node_u, node_v)
    else:
        skipped_node_u, skipped_node_v = node_u, node_v

if find_parent(skipped_node_u) == find_parent(skipped_node_v):
    print(0)
else:
    total_connected_nodes = count_nodes_in_same_set(disjoint_set[1])
    print(total_connected_nodes * (total_nodes - total_connected_nodes))
