import sys
input = sys.stdin.readline
sys.setrecursionlimit(10**7)
directions = [1, 0, -1, 0]

def depth_first_search(current_node):
  global current_id, component_count
  node_id[current_node] = current_node_id = current_id
  stack.append(current_node)
  for next_node in adjacency_list[current_node]:
    if strongly_connected_component[next_node]:
      continue
    if not node_id[next_node]:
      current_id += 1
      depth_first_search(next_node)
    node_id[current_node] = min(node_id[current_node], node_id[next_node])
  if node_id[current_node] == current_node_id:
    component_count += 1
    while True:
      node = stack.pop()
      strongly_connected_component[node] = component_count
      if node == current_node:
        return

def validate_board():
  if sum(row.count("W") for row in board) != black_count * 2:
    return True
  for b in range(black_count):
    for i in range(4):
      if strongly_connected_component[b * 8 + i] == strongly_connected_component[b * 8 + i + 4]:
        return True

for _ in range(int(input())):
  num_rows, num_cols = map(int, input().split())
  board = [list(input().strip()) for _ in range(num_rows)]
  black_count = 0
  black_positions = []

  for row in range(num_rows):
    for col in range(num_cols):
      if board[row][col] == "B":
        board[row][col] = black_count
        black_positions.append((row, col, black_count))
        black_count += 1

  adjacency_list = [[] for _ in range(black_count * 8)]

  for row, col, black_index in black_positions:
    for i in range(4):
      adjacency_list[black_index * 8 + i + 4].append(black_index * 8 + (i - 2) % 4)
      adjacency_list[black_index * 8 + i].append(black_index * 8 + (i - 2) % 4 + 4)
      if num_rows > (next_row := row + directions[i]) >= 0 and num_cols > (next_col := col + directions[i - 1]) >= 0 and board[next_row][next_col] == "W":
        for j in range(4):
          if i == (j - 2) % 4:
            continue
          if num_rows > (next_row_2 := next_row + directions[j]) >= 0 and num_cols > (next_col_2 := next_col + directions[j - 1]) >= 0 and type(board[next_row_2][next_col_2]) == int:
            adjacent_black_index = board[next_row_2][next_col_2]
            adjacency_list[black_index * 8 + i].append(adjacent_black_index * 8 + (j - 2) % 4 + 4)
      else:
        adjacency_list[black_index * 8 + i].append(black_index * 8 + i + 4)

  node_id = [0] * black_count * 8
  stack = []
  strongly_connected_component = [0] * black_count * 8
  component_count = 0

  for i in range(black_count * 8):
    if not strongly_connected_component[i]:
      current_id = 1
      depth_first_search(i)

  print("NO" if validate_board() else "YES")
