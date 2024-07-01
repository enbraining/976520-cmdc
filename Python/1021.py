from collections import deque
import sys

def read_input():
    return sys.stdin.readline().strip()

def main():
    n, m = map(int, read_input().split())
    target_indices = list(map(int, read_input().split()))
    queue = deque(range(1, n + 1))

    operation_count = 0
    for target in target_indices:
        while True:
            if queue[0] == target:
                queue.popleft()
                break
            else:
                if queue.index(target) < len(queue) / 2:
                    while queue[0] != target:
                        queue.append(queue.popleft())
                        operation_count += 1
                else:
                    while queue[0] != target:
                        queue.appendleft(queue.pop())
                        operation_count += 1

    print(operation_count)

if __name__ == "__main__":
    main()
