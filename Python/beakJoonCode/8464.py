def squareNoNo(n):
    square_free_count = 0
    for i in range(1, int(n ** 0.5) + 1):
        square_free_count += mobius[i] * (n // (i * i))
    return square_free_count

lower_bound, upper_bound = 0, 100000000000
mobius = [0] * 1000001
kth_square_free_number = int(input())
mobius[1] = 1

for i in range(1, 1000001):
    if mobius[i]:
        for multiple in range(i * 2, 1000001, i):
            mobius[multiple] -= mobius[i]

while lower_bound < upper_bound - 1:
    mid_point = (lower_bound + upper_bound) // 2
    if mid_point - squareNoNo(mid_point) < kth_square_free_number:
        lower_bound = mid_point
    else:
        upper_bound = mid_point

print(upper_bound)
