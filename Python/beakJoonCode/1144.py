from sys import stdin

number_of_rows, number_of_columns = map(int, stdin.readline().split())

grid_values = [list(map(int, stdin.readline().split())) for _ in range(number_of_rows)]

memoization_cache = [[{} for _ in range(number_of_columns)] for _ in range(number_of_rows)]

INFINITY_CONSTANT = int(1e9)

def is_valid_state(current_state):
    return len(set(state_element for state_element in current_state if state_element)) <= 1

def normalize_state(current_state):
    state_counter = [0 for _ in range(10)]
    normalized_state = [state_element for state_element in current_state]
    unique_counter = 0
    for column_index in range(number_of_columns):
        if not current_state[column_index]:
            continue
        if not state_counter[current_state[column_index]]:
            unique_counter += 1
            state_counter[current_state[column_index]] = unique_counter
        normalized_state[column_index] = state_counter[current_state[column_index]]
    return normalized_state

def is_state_skippable(current_state):
    if current_state[0] == 0:
        return True
    for column_index in range(1, number_of_columns):
        if current_state[0] == current_state[column_index]:
            return True
    return False

def compute_next_state(y_coordinate, current_state):
    next_state = current_state[1:]
    if not y_coordinate:
        next_state.append(9 if current_state[0] == 0 else current_state[0])
        return normalize_state(next_state)

    if current_state[0] == 0 and current_state[-1] == 0:
        next_state.append(9)
    elif current_state[0] != 0 and current_state[-1] != 0:
        next_state.append(current_state[0])
        for column_index in range(number_of_columns):
            if next_state[column_index] == current_state[-1]:
                next_state[column_index] = current_state[0]
    else:
        next_state.append(current_state[0] if current_state[0] else current_state[-1])
    return normalize_state(next_state)

def find_optimal_solution(x_coordinate, y_coordinate, current_state):
    if x_coordinate == number_of_rows:
        return 0 if is_valid_state(current_state) else INFINITY_CONSTANT
    
    current_state = normalize_state(current_state)
    if tuple(current_state) in memoization_cache[x_coordinate][y_coordinate]:
        return memoization_cache[x_coordinate][y_coordinate][tuple(current_state)]

    minimum_cost = INFINITY_CONSTANT
    next_x_coordinate, next_y_coordinate = x_coordinate, y_coordinate + 1
    if next_y_coordinate == number_of_columns:
        next_x_coordinate, next_y_coordinate = x_coordinate + 1, 0

    if is_state_skippable(current_state):
        next_state = current_state[1:]
        next_state.append(0)
        minimum_cost = min(minimum_cost, find_optimal_solution(next_x_coordinate, next_y_coordinate, next_state))

    next_state = compute_next_state(y_coordinate, current_state)
    minimum_cost = min(minimum_cost, find_optimal_solution(next_x_coordinate, next_y_coordinate, next_state) + grid_values[x_coordinate][y_coordinate])

    if is_valid_state(current_state):
        minimum_cost = min(minimum_cost, 0)

    memoization_cache[x_coordinate][y_coordinate][tuple(current_state)] = minimum_cost
    return minimum_cost

print(find_optimal_solution(0, 0, [0 for _ in range(number_of_columns)]))
