import sys

def find_maximum_bishops(diagonal_index, count):
    global max_count
    if diagonal_index >= total_diagonals:
        max_count = max(max_count, count)
        return
    
    for ci, cj in bishop_positions[diagonal_index]:
        if not visited[ci - cj]:
            visited[ci - cj] = 1
            find_maximum_bishops(diagonal_index + 2, count + 1)
            visited[ci - cj] = 0

    find_maximum_bishops(diagonal_index + 2, count)

n = int(input())
chessboard = [[*map(int, input().split())] for _ in range(n)]

bishop_positions = [[] for _ in range(2 * n - 1)]

for i in range(n):
    for j in range(n):
        if chessboard[i][j] == 1:
            bishop_positions[i + j].append((i, j))

total_diagonals = 2 * n - 1
visited = [0] * total_diagonals

max_count = 0
find_maximum_bishops(0, 0)
first_result = max_count

max_count = 0
find_maximum_bishops(1, 0)
second_result = max_count

print(first_result + second_result)
