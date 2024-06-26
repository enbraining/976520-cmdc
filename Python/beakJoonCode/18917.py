import sys
input = sys.stdin.readline

cumulative_xor_value = 0
cumulative_sum_value = 0
number_of_operations = int(input())

for operation_index in range(number_of_operations):
    query_list = list(map(int, input().split()))
    if query_list[0] == 1:
        cumulative_sum_value += query_list[1]
        cumulative_xor_value ^= query_list[1]
    elif query_list[0] == 2:
        cumulative_sum_value -= query_list[1]
        cumulative_xor_value ^= query_list[1]
    elif query_list[0] == 3:
        print(cumulative_sum_value)
    else:
        print(cumulative_xor_value)
