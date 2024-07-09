import sys
import random

sys.setrecursionlimit(10**6)
input_number = int(input())

def modular_exponentiation(base, exponent, modulus):
    result = 1
    base = base % modulus
    while exponent > 0:
        if exponent & 1:
            result = (result * base) % modulus
        exponent >>= 1
        base = (base * base) % modulus
    return result

def calculate_gcd(value1, value2):
    while value2 != 0:
        value1, value2 = value2, value1 % value2
    return value1

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
    prime_bases = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]
    if number < 2:
        return False
    if number in prime_bases:
        return True
    if any(number % base == 0 for base in prime_bases):
        return False
    return all(miller_rabin_primality_test(number, base) for base in prime_bases)

def pollards_rho_algorithm(composite_number):
    if is_probable_prime(composite_number):
        return composite_number
    if composite_number % 2 == 0:
        return 2

    x = random.randrange(2, composite_number)
    y, constant_addition, divisor = x, random.randrange(1, composite_number), 1

    while divisor == 1:
        x = (x * x + constant_addition) % composite_number
        y = (y * y + constant_addition) % composite_number
        y = (y * y + constant_addition) % composite_number
        divisor = calculate_gcd(abs(x - y), composite_number)
        if divisor == composite_number:
            return pollards_rho_algorithm(composite_number)
    
    return pollards_rho_algorithm(divisor) if not is_probable_prime(divisor) else divisor

factors = []
while input_number > 1:
    factor = pollards_rho_algorithm(input_number)
    factors.append(factor)
    input_number //= factor

if factors:
    factors.sort()
    total_divisors, current_factor_count = 1, 1
    previous_factor = factors[0]

    for factor in factors[1:]:
        if factor == previous_factor:
            current_factor_count += 1
        else:
            total_divisors *= (current_factor_count + 1)
            current_factor_count = 1
            previous_factor = factor

    total_divisors *= (current_factor_count + 1)
    print(total_divisors)
else:
    print(1)
