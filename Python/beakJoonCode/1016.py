import sys
input = sys.stdin.readline

def calculate_count_of_distinct_numbers_in_range(minimum_number, maximum_number):
    count_of_distinct_numbers = maximum_number - minimum_number + 1
    is_number_marked_as_composite = [False] * (maximum_number - minimum_number + 1)
    current_prime_number = 2
    while current_prime_number * current_prime_number <= maximum_number:
        square_of_current_prime_number = current_prime_number * current_prime_number
        starting_index_of_multiples = 0 if minimum_number % square_of_current_prime_number == 0 else 1
        index_of_multiple = minimum_number // square_of_current_prime_number + starting_index_of_multiples
        while square_of_current_prime_number * index_of_multiple <= maximum_number:
            if not is_number_marked_as_composite[square_of_current_prime_number * index_of_multiple - minimum_number]:
                is_number_marked_as_composite[square_of_current_prime_number * index_of_multiple - minimum_number] = True
                count_of_distinct_numbers -= 1
            index_of_multiple += 1
        current_prime_number += 1
    print(count_of_distinct_numbers)

minimum_number, maximum_number = map(int, input().split())
calculate_count_of_distinct_numbers_in_range(minimum_number, maximum_number)
