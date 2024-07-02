import heapq

priority_queue, modified_values = [], []
number_of_elements = int(input())
input_values = list(map(int, input().split()))

for index in range(number_of_elements):
    for _ in range(2):
        heapq.heappush(priority_queue, -(input_values[index] - index))
    heapq.heappop(priority_queue)
    modified_values.append(-heapq.heappop(priority_queue))
    heapq.heappush(priority_queue, -modified_values[index])

for index in range(number_of_elements - 2, -1, -1):
    if modified_values[index] > modified_values[index + 1]:
        modified_values[index] = modified_values[index + 1]

total_difference = sum(abs(input_values[index] - modified_values[index] - index) for index in range(number_of_elements))
print(total_difference)
