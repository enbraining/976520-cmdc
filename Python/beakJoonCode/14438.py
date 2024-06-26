import sys
input = sys.stdin.readline

def initialize_segment_tree(node_index, segment_start, segment_end):
    if segment_start == segment_end:
        segment_tree[node_index] = input_list[segment_start]
        return

    mid = (segment_start + segment_end) // 2
    initialize_segment_tree(node_index * 2, segment_start, mid)
    initialize_segment_tree(node_index * 2 + 1, mid + 1, segment_end)

    segment_tree[node_index] = min(segment_tree[node_index * 2], segment_tree[node_index * 2 + 1])

def update_segment_tree(node_index, segment_start, segment_end, update_index, update_value):
    if update_index < segment_start or update_index > segment_end:
        return

    if segment_start == segment_end:
        segment_tree[node_index] = update_value
        return

    mid = (segment_start + segment_end) // 2
    update_segment_tree(node_index * 2, segment_start, mid, update_index, update_value)
    update_segment_tree(node_index * 2 + 1, mid + 1, segment_end, update_index, update_value)

    segment_tree[node_index] = min(segment_tree[node_index * 2], segment_tree[node_index * 2 + 1])

def range_minimum_query(node_index, segment_start, segment_end, query_left, query_right):
    if query_left > segment_end or query_right < segment_start:
        return int(1e9)

    if query_left <= segment_start and query_right >= segment_end:
        return segment_tree[node_index]

    mid = (segment_start + segment_end) // 2
    left_query_result = range_minimum_query(node_index * 2, segment_start, mid, query_left, query_right)
    right_query_result = range_minimum_query(node_index * 2 + 1, mid + 1, segment_end, query_left, query_right)

    return min(left_query_result, right_query_result)

number_of_elements = int(input())
input_list = list(map(int, input().split()))
segment_tree = [0] * (4 * number_of_elements)

initialize_segment_tree(1, 0, number_of_elements - 1)

for _ in range(int(input())):
    query_type, query_param_a, query_param_b = map(int, input().split())

    if query_type == 1:
        update_segment_tree(1, 0, number_of_elements - 1, query_param_a - 1, query_param_b)
    else:
        print(range_minimum_query(1, 0, number_of_elements - 1, query_param_a - 1, query_param_b - 1))
