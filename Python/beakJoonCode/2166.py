from collections import deque
import math


def calculate_cross_product(x1, y1, x2, y2, x3, y3):
    return (x1 * y2 + x2 * y3 + x3 * y1) - (y1 * x2 + y2 * x3 + y3 * x1)


number_of_points = int(input())
starting_x, starting_y = map(int, input().split())

point_positions = deque()
for _ in range(number_of_points-1):
    point_positions.append(list(map(int, input().split())))

total_area = 0
for index in range(number_of_points-2):
    total_area += calculate_cross_product(starting_x, starting_y,
                                          point_positions[index][0], point_positions[index][1],
                                          point_positions[index+1][0], point_positions[index+1][1])

print(round(abs(total_area)/2, 1))
