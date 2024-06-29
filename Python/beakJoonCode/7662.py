import sys
import heapq

def is_heap_empty(number_counts):
    for number, count in number_counts:
        if count > 0:
            return False
    return True

test_cases = int(sys.stdin.readline())

for _ in range(test_cases):
    min_heap = []
    max_heap = []
    number_counts = dict()
    operations_count = int(sys.stdin.readline())
    
    for _ in range(operations_count):
        operation_type, operand = sys.stdin.readline().split()
        number = int(operand)
        
        if operation_type == 'I':
            if number in number_counts:
                number_counts[number] += 1
            else:
                number_counts[number] = 1
                heapq.heappush(min_heap, number)
                heapq.heappush(max_heap, -number)
                
        elif operation_type == 'D':
            if not is_heap_empty(number_counts.items()):
                if number == 1:
                    while -max_heap[0] not in number_counts or number_counts[-max_heap[0]] < 1:
                        temp = -heapq.heappop(max_heap)
                        if temp in number_counts:
                            del number_counts[temp]
                    number_counts[-max_heap[0]] -= 1
                else:
                    while min_heap[0] not in number_counts or number_counts[min_heap[0]] < 1:
                        temp = heapq.heappop(min_heap)
                        if temp in number_counts:
                            del number_counts[temp]
                    number_counts[min_heap[0]] -= 1
        
    if is_heap_empty(number_counts.items()):
        print('EMPTY')
    else:
        while min_heap[0] not in number_counts or number_counts[min_heap[0]] < 1:
            heapq.heappop(min_heap)
        while -max_heap[0] not in number_counts or number_counts[-max_heap[0]] < 1:
            heapq.heappop(max_heap)
        print(-max_heap[0], min_heap[0])
