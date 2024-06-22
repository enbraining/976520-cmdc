import sys
import math

sys.setrecursionlimit(10 ** 8)
input = lambda: sys.stdin.readline().rstrip()

def sum_of_special_series(x):
    if x <= 0:
        return 0

    seung = int(math.log2(x))
    floor_power_of_2 = 2 ** seung 
    if floor_power_of_2 == x:
        return seung * x // 2 + 1

    difference = x - floor_power_of_2
    return sum_of_special_series(floor_power_of_2) + difference + sum_of_special_series(difference)

start, end = map(int, input().split())
print(sum_of_special_series(end) - sum_of_special_series(start - 1))
