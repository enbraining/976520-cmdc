def binary_search(target_x, target_y, left, right):
    best_result = float('inf')
    while abs(right - left) / 2 > 1.1920929e-7:
        mid = (left + right) / 2
        current_result, final_y = calculate_cost(-10, target_x, mid)
        best_result = current_result
        if final_y < target_y:
            left = mid
        else:
            right = mid
    return best_result

def calculate_cost(initial_x, initial_y, slope):
    total_cost = 0
    for _ in range(2000):
        if initial_y > 13 or initial_y < -13:
            return [float('inf'), initial_y]
        total_cost += (y_function(initial_x, initial_y) + 1) * (slope ** 2 + 1) ** 0.5 / 100
        initial_x += 0.01
        initial_y += slope / 100
        slope += euler_lagrange_equation(initial_x, initial_y, slope) / 100
    return [total_cost, initial_y]

def y_function(x, y):
    total = 0
    for island_y in island_positions:
        distance_squared = x ** 2 + (y - island_y) ** 2
        if distance_squared < 1.1920929e-7:
            return float('inf')
        total += distance_squared ** -1
    return total

def euler_lagrange_equation(x, y, slope):
    temp = slope ** 2 + 1
    ret = 1
    p1 = p2 = 0
    for island_y in island_positions:
        distance_squared = x ** 2 + (y - island_y) ** 2
        ret += distance_squared ** -1
        p1 += (y - island_y) / distance_squared ** 2
        p2 += (x + (y - island_y) * slope) / distance_squared ** 2
    return temp * (slope * p2 - temp * p1) * 2 / ret

for case_index in range(int(input())):
    num_islands, start_x, target_y = map(float, input().split())
    island_positions = list(map(float, input().split()))
    possible_slopes = sorted([-2, 2] + [(island_y - start_x) / 10 for island_y in island_positions])
    min_cost = float('inf')
    for slope_index in range(len(possible_slopes) - 1):
        cost = binary_search(start_x, target_y, possible_slopes[slope_index], possible_slopes[slope_index + 1])
        if min_cost > cost:
            min_cost = cost
    print(f'Case #{case_index + 1}: {round(min_cost, 2)}')
