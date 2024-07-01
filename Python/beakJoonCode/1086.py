import sys
import math

input_stream = sys.stdin.readline

def calculate_ways_to_divide_into_subsets(current_remainder, current_bitmask, current_length_index):
    DP[current_remainder][current_bitmask] = 0
    if current_bitmask == (1 << N) - 1:
        DP[current_remainder][current_bitmask] = int(not current_remainder)
        return
    for num_index in range(N):
        if current_bitmask & (1 << num_index):
            continue
        updated_remainder = (current_remainder + remainders[num_index] * remainders_mod_10[current_length_index]) % K
        if DP[updated_remainder][current_bitmask | (1 << num_index)] == -1:
            calculate_ways_to_divide_into_subsets(updated_remainder, current_bitmask | (1 << num_index), current_length_index + lengths[num_index])
        DP[current_remainder][current_bitmask] += DP[updated_remainder][current_bitmask | (1 << num_index)]

N = int(input_stream())
numbers = [int(input_stream()) for i in range(N)]
K = int(input_stream())
remainders = [n % K for n in numbers]
lengths = [len(str(n)) for n in numbers]
remainders_mod_10 = [10 ** i % K for i in range(750)]

DP = [[-1] * (1 << N) for i in range(K + 1)]
calculate_ways_to_divide_into_subsets(0, 0, 0)

numerator, denominator = DP[0][0], math.factorial(N)
if not numerator:
    denominator = 1
else:
    for p in range(2, int(math.sqrt(numerator)) + 1):
        while numerator % p == denominator % p == 0:
            numerator //= p
            denominator //= p
    if numerator != 1:
        if not denominator % numerator:
            denominator //= numerator
            numerator = 1

print(str(numerator) + "/" + str(denominator))
