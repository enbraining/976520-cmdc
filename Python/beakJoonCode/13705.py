import sys
from decimal import *
input = sys.stdin.readline

getcontext().prec = 50
getcontext().rounding = ROUND_HALF_UP

coefficient_A, coefficient_B, coefficient_C = map(Decimal, map(int, input().split()))
PI_value = Decimal('3.14159265358979323846264338327950288419716939937510')

def sine_function(angle_radians):
    angle_radians = angle_radians % (2 * PI_value)
    getcontext().prec += 2
    iteration_index, previous_sum, current_sum, factorial_value, numerator_value, sign_value = 1, 0, angle_radians, 1, angle_radians, 1
    while current_sum != previous_sum:
        previous_sum = current_sum
        iteration_index += 2
        factorial_value *= iteration_index * (iteration_index - 1)
        numerator_value *= angle_radians * angle_radians
        sign_value *= -1
        current_sum += numerator_value / factorial_value * sign_value
    getcontext().prec -= 2
    return +current_sum

lower_bound, upper_bound = (coefficient_C - coefficient_B) / coefficient_A, (coefficient_C + coefficient_B) / coefficient_A

while upper_bound - lower_bound > Decimal(1e-21):
    midpoint_value = (lower_bound + upper_bound) / 2
    if coefficient_A * midpoint_value + coefficient_B * sine_function(midpoint_value) < coefficient_C:
        lower_bound = midpoint_value
    else:
        upper_bound = midpoint_value

print(round(upper_bound, 6))
