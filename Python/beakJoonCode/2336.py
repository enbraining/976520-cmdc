import sys
input_from_standard_input = sys.stdin.readline

class StudentInformation:
    def __init__(self, subject_a_rank=0, subject_b_rank=0, subject_c_rank=0):
        self.subject_a_rank = subject_a_rank
        self.subject_b_rank = subject_b_rank
        self.subject_c_rank = subject_c_rank

def compare_students_by_subject_a_rank(student_information):
    return student_information.subject_a_rank

MAXIMUM_ARRAY_SIZE = 500000 + 10
student_information_list = [StudentInformation() for _ in range(MAXIMUM_ARRAY_SIZE)]
segment_tree_for_subject_c_ranks = [0] * (4 * MAXIMUM_ARRAY_SIZE)

def update_segment_tree(node, start, end, index, value):
    if index < start or end < index:
        return segment_tree_for_subject_c_ranks[node]

    if start == end:
        segment_tree_for_subject_c_ranks[node] = value
        return segment_tree_for_subject_c_ranks[node]

    middle_index = (start + end) // 2
    segment_tree_for_subject_c_ranks[node] = min(
        update_segment_tree(node * 2, start, middle_index, index, value),
        update_segment_tree(node * 2 + 1, middle_index + 1, end, index, value)
    )
    return segment_tree_for_subject_c_ranks[node]

def query_segment_tree(node, start, end, left, right):
    if right < start or end < left:
        return float('inf')

    if left <= start and end <= right:
        return segment_tree_for_subject_c_ranks[node]

    middle_index = (start + end) // 2
    return min(
        query_segment_tree(node * 2, start, middle_index, left, right),
        query_segment_tree(node * 2 + 1, middle_index + 1, end, left, right)
    )

number_of_students = int(input_from_standard_input().strip())

subject_a_ranks = list(map(int, input_from_standard_input().strip().split()))
subject_b_ranks = list(map(int, input_from_standard_input().strip().split()))
subject_c_ranks = list(map(int, input_from_standard_input().strip().split()))

for i in range(1, number_of_students + 1):
    student_information_list[subject_a_ranks[i - 1]].subject_a_rank = i

for i in range(1, number_of_students + 1):
    student_information_list[subject_b_ranks[i - 1]].subject_b_rank = i

for i in range(1, number_of_students + 1):
    student_information_list[subject_c_ranks[i - 1]].subject_c_rank = i

student_information_list = sorted(student_information_list[1:number_of_students+1], key=compare_students_by_subject_a_rank)

for i in range(1, number_of_students + 1):
    update_segment_tree(1, 1, number_of_students, i, float('inf'))

count_of_students_with_better_subject_c_rank = 0
for i in range(1, number_of_students + 1):
    if query_segment_tree(1, 1, number_of_students, 1, student_information_list[i - 1].subject_b_rank) > student_information_list[i - 1].subject_c_rank:
        count_of_students_with_better_subject_c_rank += 1
    update_segment_tree(1, 1, number_of_students, student_information_list[i - 1].subject_b_rank, student_information_list[i - 1].subject_c_rank)

print(count_of_students_with_better_subject_c_rank)
