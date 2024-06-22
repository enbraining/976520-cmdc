from sys import stdin
import math

number_of_elements = int(stdin.readline().strip())
list_of_elements = list(map(int, stdin.readline().split()))
prefix_sum_list = [0]
for index in range(number_of_elements * 2):
    prefix_sum_list.append(prefix_sum_list[-1] + list_of_elements[index % number_of_elements])
total_result = 0
for index in range(number_of_elements - 1):
    for index2 in range(1, number_of_elements + 1):
        if prefix_sum_list[index2 + index] < prefix_sum_list[index2 - 1]:
            total_result += math.ceil(abs(prefix_sum_list[index2 + index] - prefix_sum_list[index2 - 1]) / prefix_sum_list[number_of_elements])
print(total_result)
