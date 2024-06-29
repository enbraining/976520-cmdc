import sys, bisect

number_of_elements = int(sys.stdin.readline())
input_array = list(map(int, sys.stdin.readline().split()))

smallest_end_elements_of_subsequences = [sys.maxsize] * number_of_elements

for element in input_array:
    #이진탐색
    insert_position = bisect.bisect_left(smallest_end_elements_of_subsequences, element)
    smallest_end_elements_of_subsequences[insert_position] = element

print(bisect.bisect_left(smallest_end_elements_of_subsequences, sys.maxsize))
