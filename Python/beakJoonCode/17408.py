import sys
input = sys.stdin.readline

segment_tree = [[0, 0] for _ in range(404040)]

def initialize_segment_tree(node, start, end):
    if start == end:
        segment_tree[node] = [a[start - 1], 0]
        return segment_tree[node]
    mid = (start + end) // 2
    temporary_list = initialize_segment_tree(node * 2, start, mid) + initialize_segment_tree(node * 2 + 1, mid + 1, end)
    temporary_list.sort(reverse=True)
    segment_tree[node] = temporary_list[:2]
    return segment_tree[node]

def update_segment_tree(node, start, end, index, value):
    if end < index or index < start:
        return segment_tree[node]
    if start == end:
        if start == index:
            segment_tree[node] = [value, 0]
        return segment_tree[node]

    mid = (start + end) // 2
    temporary_list = update_segment_tree(node * 2, start, mid, index, value) + update_segment_tree(node * 2 + 1, mid + 1, end, index, value)
    temporary_list.sort(reverse=True)
    segment_tree[node] = temporary_list[:2]
    return segment_tree[node]

def get_answer(node, left, right, start, end):
    if end < left or right < start:
        return [0, 0]
    if left <= start and end <= right:
        return segment_tree[node]
    mid = (start + end) // 2
    temporary_list = get_answer(node * 2, left, right, start, mid) + get_answer(node * 2 + 1, left, right, mid + 1, end)
    temporary_list.sort(reverse=True)
    return temporary_list[:2]

n = int(input())
a = list(map(int, input().split()))

initialize_segment_tree(1, 1, n)

m = int(input())
for query in range(m):
    query_type, i, j = map(int, input().split())
    if query_type == 1:
        update_segment_tree(1, 1, n, i, j)
    else:
        result = get_answer(1, i, j, 1, n)
        print(result[0] + result[1])
