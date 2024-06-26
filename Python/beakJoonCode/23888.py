import sys
input = sys.stdin.readline

def greatest_common_divisor(number_one, number_two): 
    if number_two == 0:
        return number_one
    while number_one % number_two != 0:
        number_one, number_two  = number_two, number_one % number_two
    return number_two

initial_value_a, common_difference_d = map(int, input().split()) 
number_of_queries_q = int(input())
for query_index in range(number_of_queries_q):
    query_type, range_start_l, range_end_r = map(int, input().split()) 
    if query_type == 1: 
        sum_up_to_r = (range_end_r * ((2 * initial_value_a) + (range_end_r - 1) * common_difference_d)) // 2
        sum_up_to_l_minus_1 = ((range_start_l - 1) * ((2 * initial_value_a) + (range_start_l - 2) * common_difference_d)) // 2
        print(sum_up_to_r - sum_up_to_l_minus_1)
    elif query_type == 2: 
        if range_start_l == range_end_r:
            print(initial_value_a + (range_start_l - 1) * common_difference_d)
        else:
            print(greatest_common_divisor(initial_value_a, common_difference_d))
