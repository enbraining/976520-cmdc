import sys

def modular_exponentiation(base, exponent, modulus):
    result = 1
    while exponent > 0:
        if exponent % 2 != 0:
            result = (result * base) % modulus
        exponent //= 2
        base = (base * base) % modulus

    return result

def miller_rabin_primality_test(candidate, base):
    exponent_of_two = 0
    odd_part = candidate - 1
    while odd_part % 2 == 0:
        exponent_of_two += 1
        odd_part //= 2
    test_result = modular_exponentiation(base, odd_part, candidate)
    if test_result == 1 or test_result == candidate - 1:
        return True
    for _ in range(exponent_of_two - 1):
        test_result = modular_exponentiation(test_result, 2, candidate)
        if test_result == candidate - 1:
            return True
    return False

def is_probable_prime(number):
    if number <= 71:
        return number in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]
    else:
        for base in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]:
            if not miller_rabin_primality_test(number, base):
                return False
        return True

def calculate_greatest_common_divisor(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def polynomial_function(x, modulus):
    return ((x * x) + 1) % modulus

def pollards_rho_algorithm(n, x):
    initial_x = x
    if is_probable_prime(n):
        return n
    else:
        for prime in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]:
            if n % prime == 0:
                return prime
        y = x
        gcd_value = 1
        while gcd_value == 1:
            x = polynomial_function(x, n)
            y = polynomial_function(polynomial_function(y, n), n)
            gcd_value = calculate_greatest_common_divisor(abs(x - y), n)
        if gcd_value == n:
            return pollards_rho_algorithm(n, initial_x + 1)
        else:
            if is_probable_prime(gcd_value):
                return gcd_value
            else:
                return pollards_rho_algorithm(gcd_value, 2)

input_number = int(sys.stdin.readline())
original_number = input_number

factors = []
while input_number != 1:
    factor = pollards_rho_algorithm(input_number, 2)
    factors.append(int(factor))
    input_number //= factor

from itertools import combinations

totient_sum = original_number
unique_factors = list(set(factors))
for i in range(1, len(unique_factors) + 1):
    for factor_combination in combinations(unique_factors, i):
        product_of_factors = 1
        for factor in factor_combination:
            product_of_factors *= factor
        if i % 2 == 1:
            totient_sum -= (original_number // product_of_factors)
        else:
            totient_sum += (original_number // product_of_factors)

if original_number == 1:
    print(1)
else:
    print(totient_sum)
