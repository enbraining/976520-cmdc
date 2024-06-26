import sys
input = sys.stdin.readline
from collections import defaultdict

num_elements = int(input())
sqrt_num_elements = num_elements ** 0.5
elements = list(map(int, input().split()))
num_queries = int(input())
query_results = [0] * num_queries

queries = [[query_index] + list(map(int, input().split())) for query_index in range(num_queries)]
queries.sort(key=lambda x: (x[1] // sqrt_num_elements, x[2]))

element_frequency = defaultdict(int)
unique_count = 0
prev_start_index = 0
prev_end_index = -1

for query in queries:
    query_index, start_index, end_index = query
    start_index -= 1
    end_index -= 1

    while prev_end_index < end_index:
        prev_end_index += 1
        if element_frequency[elements[prev_end_index]] == 0:
            unique_count += 1
        element_frequency[elements[prev_end_index]] += 1
    
    while prev_end_index > end_index:
        element_frequency[elements[prev_end_index]] -= 1
        if element_frequency[elements[prev_end_index]] == 0:
            unique_count -= 1
        prev_end_index -= 1

    while prev_start_index < start_index:
        element_frequency[elements[prev_start_index]] -= 1
        if element_frequency[elements[prev_start_index]] == 0:
            unique_count -= 1
        prev_start_index += 1

    while prev_start_index > start_index:
        prev_start_index -= 1
        if element_frequency[elements[prev_start_index]] == 0:
            unique_count += 1
        element_frequency[elements[prev_start_index]] += 1

    query_results[query_index] = unique_count

print(*query_results, sep='\n')
