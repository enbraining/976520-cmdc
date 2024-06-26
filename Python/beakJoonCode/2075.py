import heapq

min_heap = []
total_numbers = int(input())

for _ in range(total_numbers):
    input_numbers = map(int, input().split())
    for num in input_numbers:
        if len(min_heap) < total_numbers: 
            heapq.heappush(min_heap, num)
        else:
            if min_heap[0] < num:
                heapq.heappop(min_heap)
                heapq.heappush(min_heap, num)
print(min_heap[0])
