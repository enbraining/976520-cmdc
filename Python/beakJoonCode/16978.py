import sys
input = sys.stdin.readline

def update(index, new_value):
    delta = new_value - fenwick_tree_values[index]
    fenwick_tree_values[index] = new_value
    while index < fenwick_tree_size:
        fenwick_tree[index] += delta
        index += index & -index

def calculate_prefix_sum(index):
    total_sum = 0
    while index:
        total_sum += fenwick_tree[index]
        index -= index & -index
    return total_sum

number_of_elements = int(input())
fenwick_tree_size = 1 << 20
sequence = list(map(int, input().split()))
fenwick_tree_values = [0] * fenwick_tree_size
fenwick_tree = [0] * fenwick_tree_size

for i in range(number_of_elements):
    update(i + 1, sequence[i])

queries = [[], []]
for _ in range(int(input())):
    query_type, *args = map(int, input().split())
    queries[query_type - 1].append([*args, len(queries[query_type - 1])])

queries[1].sort()
query_results = [0] * len(queries[1])
current_update_index = 0

for end_index, start_index, end_index_j, query_index in queries[1]:
    while current_update_index < end_index:
        update(*queries[0][current_update_index][:-1])
        current_update_index += 1
    query_results[query_index] = calculate_prefix_sum(end_index_j) - calculate_prefix_sum(start_index - 1)

print(*query_results, sep="\n")
