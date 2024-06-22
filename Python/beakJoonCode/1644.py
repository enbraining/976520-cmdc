import sys
import math

sys.setrecursionlimit(10 ** 8)
input = lambda: sys.stdin.readline().rstrip()

number = int(input())
if number == 1:
    print(0)
    exit()

MAX = 4000000
prime_check_list = [1 for _ in range(number + 1)]
prime_check_list[0], prime_check_list[1] = 0, 0

for current_number in range(2, int(math.sqrt(number)) + 1):
    if prime_check_list[current_number]:
        for multiple in range(2, number // current_number + 1):
            prime_check_list[current_number * multiple] = 0  

prime_numbers = []
for current_number in range(2, number + 1):
    if prime_check_list[current_number]:
        prime_numbers.append(current_number)

prime_sum_count = 0
start_index, end_index = len(prime_numbers) - 1, len(prime_numbers) - 1
current_sum = prime_numbers[-1]

while 0 <= start_index <= end_index and 0 <= end_index < len(prime_numbers):
    if current_sum > number:
        current_sum -= prime_numbers[end_index]
        end_index -= 1
    else:
        if current_sum == number:
            prime_sum_count += 1
        start_index -= 1
        if start_index < 0:
            break
        current_sum += prime_numbers[start_index]
print(prime_sum_count)
