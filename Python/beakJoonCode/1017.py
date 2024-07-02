import sys
import math

def depth_first_search(start_element):
    global available_set_Y
    global element_pairings
    global element_visited
    if element_visited[available_set_Y.index(start_element)]:
        return False
    element_visited[available_set_Y.index(start_element)] = True
    for y_element in available_set_Y:
        if start_element + y_element in prime_numbers_set:
            if y_element not in element_pairings or depth_first_search(element_pairings[y_element]):
                element_pairings[y_element] = start_element
                return True
    return False

number_of_elements = int(sys.stdin.readline())
initial_elements_set_X = list(map(int, sys.stdin.readline().split()))

prime_numbers_set = []
for candidate_number in range(2, 2000):
    is_prime = True
    for divisor in range(2, candidate_number):
        if candidate_number % divisor == 0:
            is_prime = False
            break
    if is_prime:
        prime_numbers_set.append(candidate_number)
    else:
        continue

valid_pairs = []
for element in initial_elements_set_X:
    element_pairings = {}
    if element == initial_elements_set_X[0]:
        continue
    if initial_elements_set_X[0] + element in prime_numbers_set:
        if number_of_elements == 2:
            valid_pairs.append(element)
            break
        available_set_Y = [x for x in initial_elements_set_X]
        del available_set_Y[0]
        del available_set_Y[available_set_Y.index(element)]
        element_pairings = {}
        for y_element in available_set_Y:
            element_visited = [False for _ in range(len(available_set_Y))]
            depth_first_search(y_element)

    if number_of_elements != 2 and len(element_pairings) == number_of_elements - 2:
        valid_pairs.append(element)

if not valid_pairs:
    valid_pairs.append(-1)

valid_pairs.sort()

print(' '.join(list(map(str, valid_pairs))))
