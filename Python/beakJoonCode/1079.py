import sys
input = sys.stdin.readline
def initialize_game_state():
    global num_people, guiltiness_matrix, guiltiness_list, target_person, is_dead
    num_people = int(input())
    guiltiness_list = list(map(int, input().split()))
    guiltiness_matrix = [list(map(int, input().split())) for _ in range(num_people)]
    target_person = int(input())

    is_dead = [False] * num_people
def depth_first_search(remaining_people, current_depth):
    if remaining_people == 2:
        return current_depth + 1
    if remaining_people == 1:
        return current_depth

    if remaining_people % 2 == 0:
        max_result = current_depth + 1

        for i in range(num_people):
            if is_dead[i] or i == target_person:
                continue
            max_guiltiness, max_guiltiness_index = -float('inf'), -1
            for j in range(num_people):
                if is_dead[j] or i == j:
                    continue
                guiltiness_list[j] += guiltiness_matrix[i][j]
                if guiltiness_list[j] > max_guiltiness:
                    max_guiltiness, max_guiltiness_index = guiltiness_list[j], j

            if max_guiltiness_index != target_person:
                is_dead[i] = True
                is_dead[max_guiltiness_index] = True
                max_result = max(max_result, depth_first_search(remaining_people - 2, current_depth + 1))
                is_dead[i] = False
                is_dead[max_guiltiness_index] = False

            for j in range(num_people):
                if is_dead[j] or i == j:
                    continue
                guiltiness_list[j] -= guiltiness_matrix[i][j]

    else:
        max_guiltiness, max_guiltiness_index = -float('inf'), -1
        for i in range(num_people):
            if is_dead[i]:
                continue

            if guiltiness_list[i] > max_guiltiness:
                max_guiltiness, max_guiltiness_index = guiltiness_list[i], i

        if max_guiltiness_index == target_person:
            return current_depth
        else:
            is_dead[max_guiltiness_index] = True
            max_result = depth_first_search(remaining_people - 1, current_depth)
            is_dead[max_guiltiness_index] = False

    return max_result
def solve_game():
    initialize_game_state()
    result = depth_first_search(num_people, 0)
    print(result)
solve_game()
