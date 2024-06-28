import sys
from collections import deque

def process_operations(pattern, initial_size, initial_queue):
    rev_count = 0
    front_index = 0
    back_index = len(initial_queue) - 1
    error_flag = 0
    queue = deque(initial_queue)

    if initial_size == 0:
        queue = deque()
        front_index = 0
        back_index = 0

    for operation in pattern:
        if operation == 'R':
            rev_count += 1
        elif operation == 'D':
            if len(queue) < 1:
                error_flag = 1
                print("error")
                break
            else:
                if rev_count % 2 == 0:
                    queue.popleft()
                else:
                    queue.pop()

    if error_flag == 0:
        if rev_count % 2 == 0:
            print("[" + ",".join(queue) + "]")
        else:
            queue.reverse()
            print("[" + ",".join(queue) + "]")

if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        pattern = sys.stdin.readline().rstrip()
        n = int(input())
        arr = sys.stdin.readline().rstrip()[1:-1].split(",")
        process_operations(pattern, n, arr)
