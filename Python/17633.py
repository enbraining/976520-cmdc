from random import randrange
prime_list = [2,3,5,7,11,13,17,19,23,29,31,37,41,43]

def modular_exponentiation(base, exponent, modulus):
    if exponent < 2:
        return (base ** exponent) % modulus
    else:
        exponent_divided_by_two = exponent // 2
        if exponent % 2 == 0:
            return (modular_exponentiation(base, exponent_divided_by_two, modulus) ** 2) % modulus 
        else:
            return (base * (modular_exponentiation(base, exponent_divided_by_two, modulus) ** 2)) % modulus

def miller_rabin_test(composite_number, base):
    exponent, divisor = 0, composite_number - 1
    while divisor % 2 == 0:
        exponent += 1
        divisor //= 2
    base_power_divisor = modular_exponentiation(base, divisor, composite_number)
    if base_power_divisor == 1 or base_power_divisor + 1 == composite_number:
        return True
    for _ in range(0, exponent - 1):
        base_power_divisor = modular_exponentiation(base_power_divisor, 2, composite_number)
        if base_power_divisor + 1 == composite_number:
            return True
    return False

def is_prime_number(candidate_number):
    if candidate_number in prime_list:
        return True
    if candidate_number == 1 or candidate_number % 2 == 0:
        return False
    for prime in prime_list:
        if not miller_rabin_test(candidate_number, prime):
            return False
    return True

def greatest_common_divisor(number_one, number_two):
    if number_one < number_two:
        number_one, number_two = number_two, number_one
    while number_two != 0:
        number_one, number_two = number_two, number_one % number_two
    return number_one

def pollard_rho_algorithm(composite_number):
    if is_prime_number(composite_number):
        return composite_number
    if composite_number == 1:
        return 1
    if composite_number % 2 == 0:
        return 2
    x_variable, constant, divisor = randrange(2, composite_number), randrange(1, composite_number), 1
    y_variable = x_variable
    while divisor == 1:
        x_variable = ((x_variable ** 2 % composite_number) + constant) % composite_number
        y_variable = ((y_variable ** 2 % composite_number) + constant) % composite_number
        y_variable = ((y_variable ** 2 % composite_number) + constant) % composite_number
        divisor = greatest_common_divisor(composite_number, abs(x_variable - y_variable))
        if divisor == composite_number:
            return pollard_rho_algorithm(composite_number)
    if is_prime_number(divisor):
        return divisor
    else:
        return pollard_rho_algorithm(divisor)

def is_four_square_sum(examined_number):
    while True:
        if examined_number % 4 == 0:
            examined_number //= 4
        else:
            return True if examined_number % 8 == 7 else False

def is_perfect_square(perfect_square_candidate):
    return True if perfect_square_candidate == int(perfect_square_candidate ** .5) ** 2 else False

input_number = int(input())
if is_perfect_square(input_number):
    print(1)
elif is_four_square_sum(input_number):
    print(4)
else:
    prime_factor_count = {}
    while input_number != 1:
        factor = pollard_rho_algorithm(input_number)
        try:
            prime_factor_count[factor] += 1
        except:
            prime_factor_count[factor] = 1
        input_number //= factor
    for prime_factor, count in prime_factor_count.items():
        if prime_factor % 4 == 3 and count % 2 == 1:
            print(3)
            quit()
    print(2)
