import sys
input = sys.stdin.readline
from math import inf

def get_slope(point_x, point_y):
    return (point_x[1] - point_y[1]) // (point_y[0] - point_x[0])

def insert_point(point):
    while len(convex_hull) > 1 and get_slope(convex_hull[-2], convex_hull[-1]) > get_slope(convex_hull[-1], point):
        convex_hull.pop()
    convex_hull.append(point)

def compute_hull_tangent(query_point):
    start = 0
    end = len(convex_hull) - 1
    while start != end:
        mid = (start + end) // 2
        if get_slope(convex_hull[mid], convex_hull[mid + 1]) <= query_point:
            start = mid + 1
        else:
            end = mid
    return convex_hull[start][0] * query_point + convex_hull[start][1]

num_items = int(input())
item_weights_heights = sorted(list(map(int, input().split())) for _ in range(num_items))
item_weights = [item_weights_heights[0][0]]
item_heights = [item_weights_heights[0][1]]
for i in range(1, num_items):
    while item_heights and item_heights[-1] <= item_weights_heights[i][1]:
        item_weights.pop()
        item_heights.pop()
    item_weights.append(item_weights_heights[i][0])
    item_heights.append(item_weights_heights[i][1])
num_unique_items = len(item_weights)
convex_hull = [[item_heights[0], 0]]
for i in range(num_unique_items - 1):
    insert_point([item_heights[i + 1], compute_hull_tangent(item_weights[i])])
print(compute_hull_tangent(item_weights[num_unique_items - 1]))
