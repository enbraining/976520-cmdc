import sys, copy

number_of_tiles = int(input())
game_board = []
maximum_value = 0

for _ in range(number_of_tiles):
    game_board.append([int(x) for x in sys.stdin.readline().rstrip().split()])

def move_left(board):
    for row in range(number_of_tiles):
        cursor_position = 0
        for column in range(1, number_of_tiles):
            if board[row][column] != 0: 
                temporary_value = board[row][column]
                board[row][column] = 0 

                if board[row][cursor_position] == 0:
                    board[row][cursor_position] = temporary_value 

                elif board[row][cursor_position] == temporary_value: 
                    board[row][cursor_position] *= 2 
                    cursor_position += 1
                else: 
                    cursor_position += 1 
                    board[row][cursor_position] = temporary_value 

    return board

def move_right(board):
    for row in range(number_of_tiles):
        cursor_position = number_of_tiles - 1
        for column in range(number_of_tiles - 1, -1, -1):
            if board[row][column] != 0:
                temporary_value = board[row][column]
                board[row][column] = 0

                if board[row][cursor_position] == 0:
                    board[row][cursor_position] = temporary_value

                elif board[row][cursor_position] == temporary_value:
                    board[row][cursor_position] *= 2
                    cursor_position -= 1
                else:
                    cursor_position -= 1
                    board[row][cursor_position] = temporary_value
    return board

def move_up(board):
    for column in range(number_of_tiles):
        cursor_position = 0
        for row in range(number_of_tiles):
            if board[row][column] != 0:
                temporary_value = board[row][column]
                board[row][column] = 0

                if board[cursor_position][column] == 0:
                    board[cursor_position][column] = temporary_value

                elif board[cursor_position][column] == temporary_value:
                    board[cursor_position][column] *= 2
                    cursor_position += 1

                else:
                    cursor_position += 1
                    board[cursor_position][column] = temporary_value
    return board

def move_down(board):
    for column in range(number_of_tiles):
        cursor_position = number_of_tiles - 1
        for row in range(number_of_tiles - 1, -1, -1):
            if board[row][column] != 0:
                temporary_value = board[row][column]
                board[row][column] = 0

                if board[cursor_position][column] == 0:
                    board[cursor_position][column] = temporary_value

                elif board[cursor_position][column] == temporary_value:
                    board[cursor_position][column] *= 2
                    cursor_position -= 1

                else:
                    cursor_position -= 1
                    board[cursor_position][column] = temporary_value
    return board

def depth_first_search(depth, game_board):
    global maximum_value
    if depth == 5:
        for row in range(number_of_tiles):
            for column in range(number_of_tiles):
                if game_board[row][column] > maximum_value:
                    maximum_value = game_board[row][column]
        return

    for direction in range(4):
        copied_game_board = copy.deepcopy(game_board)
        if direction == 0:
            depth_first_search(depth + 1, move_left(copied_game_board))
        elif direction == 1:
            depth_first_search(depth + 1, move_right(copied_game_board))
        elif direction == 2:
            depth_first_search(depth + 1, move_up(copied_game_board))
        else:
            depth_first_search(depth + 1, move_down(copied_game_board))

depth_first_search(0, game_board)
print(maximum_value)
