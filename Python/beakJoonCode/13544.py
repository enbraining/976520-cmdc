import sys
from bisect import bisect_right
input = sys.stdin.readline

segment_tree = [[] for _ in range(2020202)]

def merge_sorted_lists(left_list, right_list):
    left_index = 0
    right_index = 0
    merged_list = []
    while left_index < len(left_list) and right_index < len(right_list):
        if left_list[left_index] < right_list[right_index]:
            merged_list.append(left_list[left_index])
            left_index += 1
        else:
            merged_list.append(right_list[right_index])
            right_index += 1
    if right_index == len(right_list):
        for i in range(left_index, len(left_list)):
            merged_list.append(left_list[i])
    else:
        for i in range(right_index, len(right_list)):
            merged_list.append(right_list[i])
    return merged_list

def initialize_segment_tree(node, start, end):
    if start == end:
        segment_tree[node] = [a[start - 1]]
        return segment_tree[node]
    mid = (start + end) // 2
    segment_tree[node] = merge_sorted_lists(initialize_segment_tree(node * 2, start, mid), initialize_segment_tree(node * 2 + 1, mid + 1, end))
    return segment_tree[node]

def get_answer(node, left, right, start, end, k):
    if left <= start and end <= right:
        return len(segment_tree[node]) - bisect_right(segment_tree[node], k)
    if end < left or right < start:
        return 0
    mid = (start + end) // 2
    return get_answer(node * 2, left, right, start, mid, k) + get_answer(node * 2 + 1, left, right, mid + 1, end, k)

n = int(input())
a = list(map(int, input().split()))
initialize_segment_tree(1, 1, n)

q = int(input())
answer = 0
for _ in range(q):
    i, j, k = map(int, input().split())
    i ^= answer
    j ^= answer
    k ^= answer
    answer = get_answer(1, i, j, 1, n, k)
    print(answer)
