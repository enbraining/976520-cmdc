import sys

def miller_rabin_test(number_to_test, witness):
    power_of_two = 0
    reduced_number = number_to_test - 1
    while reduced_number % 2 == 0:
        power_of_two += 1
        reduced_number //= 2
    current_value = power_modulo(witness, reduced_number, number_to_test)
    if current_value == 1 or current_value == number_to_test - 1:
        return True
    for _ in range(power_of_two - 1):
        current_value = power_modulo(current_value, 2, number_to_test)
        if current_value == number_to_test - 1:
            return True
    return False

def power_modulo(base, exponent, modulo):
    result_value = 1
    while exponent > 0:
        if exponent % 2 != 0:
            result_value = (result_value * base) % modulo
        exponent //= 2
        base = (base * base) % modulo

    return result_value

def is_prime_number(candidate_number):
    number_of_successful_tests = 0
    if candidate_number <= 71:
        if candidate_number in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]:
            return True
        else:
            return False
    else:
        for prime_witness in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]:
            if not miller_rabin_test(candidate_number, prime_witness):
                break
            else:
                number_of_successful_tests += 1
        if number_of_successful_tests == 12:
            return True
        else:
            return False

input_number = int(sys.stdin.readline())

def polynomial_function(input_value, modulo_value):
    return ((input_value * input_value) + 1) % modulo_value

def greatest_common_divisor(first_number, second_number):
    if second_number > first_number:
        temp_value = first_number
        first_number = second_number
        second_number = temp_value
    while second_number != 0:
        remainder_value = first_number % second_number
        first_number = second_number
        second_number = remainder_value
    return first_number

def pollard_rho_algorithm(composite_number, starting_value):
    polynomial_input_value = starting_value
    if is_prime_number(composite_number):
        return composite_number
    else:
        for small_prime in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]:
            if composite_number % small_prime == 0:
                return small_prime
        second_input_value = starting_value
        greatest_common_divisor_value = 1
        while greatest_common_divisor_value == 1:
            starting_value = polynomial_function(starting_value, composite_number)
            second_input_value = polynomial_function(polynomial_function(second_input_value, composite_number), composite_number)
            greatest_common_divisor_value = greatest_common_divisor(abs(starting_value - second_input_value), composite_number)
        if greatest_common_divisor_value == composite_number:
            return pollard_rho_algorithm(composite_number, polynomial_input_value + 1)
        else:
            if is_prime_number(greatest_common_divisor_value):
                return greatest_common_divisor_value
            else:
                return pollard_rho_algorithm(greatest_common_divisor_value, 2)

prime_factors = []
while input_number != 1:
    smallest_prime_factor = pollard_rho_algorithm(input_number, 2)
    prime_factors.append(int(smallest_prime_factor))
    input_number = input_number // smallest_prime_factor

prime_factors.sort()
for prime_factor in prime_factors:
    print(prime_factor)
