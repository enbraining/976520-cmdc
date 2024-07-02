count_of_obstacles = x_coordinate = y_coordinate = total_area = 0
positions, slopes = [], []

def recursive_search(current_x, current_y, current_position, current_angle):
    current_position = current_position[:]
    if current_x == -1 or current_x == width or current_y == -1 or current_y == height or grid[current_y][current_x] == '#':
        positions.append(current_position)
        return
    next_x1 = current_x + 1 if current_angle[0] > 0 else current_x - 1
    next_x2 = current_x + 1 if current_angle[0] > 0 else current_x
    next_y1 = current_y + 1 if current_angle[0] * current_angle[1] > 0 else current_y - 1
    next_y2 = current_y + 1 if current_angle[0] * current_angle[1] > 0 else current_y
    y_intercept_next_x = current_position[1] + (current_angle[1]) * (next_x2 - current_position[0])
    x_intercept_next_y = current_position[0] + ((next_y2 - current_position[1]) / (current_angle[1]))
    if current_y + 1e-7 < y_intercept_next_x and y_intercept_next_x < current_y + 1 - 1e-7 and (x_intercept_next_y < current_x - 1e-7 or x_intercept_next_y > current_x + 1 + 1e-7):
        current_position = [next_x2, y_intercept_next_x]
        recursive_search(next_x1, current_y, current_position, current_angle)
    elif current_x + 1e-7 < x_intercept_next_y and x_intercept_next_y < current_x + 1 - 1e-7 and (current_y - 1e-7 > y_intercept_next_x or y_intercept_next_x > current_y + 1 + 1e-7):
        current_position = [x_intercept_next_y, next_y2]
        recursive_search(current_x, next_y1, current_position, current_angle)
    else:
        current_position = [next_x2, next_y2]
        if current_angle[1] > 0 and (next_x1 == -1 or next_x1 == width or grid[current_y][next_x1] == '#'):
            positions.append(current_position)
        if current_angle[1] < 0 and (next_y1 == -1 or next_y1 == height or grid[next_y1][current_x] == '#'):
            positions.append(current_position)
        recursive_search(next_x1, next_y1, current_position, current_angle)
        if current_angle[1] > 0 and (next_y1 == -1 or next_y1 == height or grid[next_y1][current_x] == '#'):
            positions.append(current_position)
        if current_angle[1] < 0 and (next_x1 == -1 or next_x1 == width or grid[current_y][next_x1] == '#'):
            positions.append(current_position)

height, width = map(int, input().split())
grid = [input() for _ in range(height)]
for row_index in range(height):
    for col_index in range(width):
        if grid[row_index][col_index] == '*':
            x_coordinate = col_index
            y_coordinate = row_index
            light_source = [col_index + 0.5, row_index + 0.5]
        elif grid[row_index][col_index] == '#':
            count_of_obstacles += 1

for y_direction in range(2):
    for x_direction in range(2):
        slope = [0, 0]
        x_direction = width * x_direction
        y_direction = height * y_direction
        slope = [1 if x_direction - light_source[0] > 0 else -1, (y_direction - light_source[1]) / (x_direction - light_source[0])]
        slopes.append(slope)

for row_index in range(height + 1):
    for col_index in range(width + 1):
        slope = [1 if col_index - light_source[0] > 0 else -1, (row_index - light_source[1]) / (col_index - light_source[0])]
        if slope not in slopes:
            slopes.append(slope)

for current_slope in sorted(slopes):
    recursive_search(x_coordinate, y_coordinate, light_source, current_slope)

for position_index in range(len(positions)):
    next_position_index = (position_index + 1) % len(positions)
    total_area += abs((light_source[0] * positions[position_index][1] + positions[position_index][0] * positions[next_position_index][1] + positions[next_position_index][0] * light_source[1]) - (positions[position_index][0] * light_source[1] + positions[next_position_index][0] * positions[position_index][1] + light_source[0] * positions[next_position_index][1])) / 2

print(f'{width * height - total_area - count_of_obstacles:.13f}')
