number_of_elements = int(input())
list_of_numbers = list(map(int, input().split()))

cumulative_sum_list = [0]
for index in range(number_of_elements):
    cumulative_sum_list.append(cumulative_sum_list[-1] + list_of_numbers[index])

stack, maximum_area = [], 0

for index in range(number_of_elements):
    starting_index = index
    while stack and stack[-1][0] >= list_of_numbers[index]:
        height, starting_index = stack.pop()
        maximum_area = max(maximum_area, (cumulative_sum_list[index] - cumulative_sum_list[starting_index]) * height)
    stack.append((list_of_numbers[index], starting_index))

while stack:
    height, starting_index = stack.pop()
    maximum_area = max(maximum_area, (cumulative_sum_list[-1] - cumulative_sum_list[starting_index]) * height)

print(maximum_area)
