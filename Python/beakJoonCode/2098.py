import sys

number_of_cities = int(input())
travel_cost_matrix = []

for _ in range(number_of_cities):
    travel_cost_matrix.append(list(map(int, sys.stdin.readline().split())))

memoization_dict = {}

def depth_first_search(current_city, visited_cities_mask):
    if visited_cities_mask == (1 << number_of_cities) - 1:
        if travel_cost_matrix[current_city][0]:
            return travel_cost_matrix[current_city][0]
        else:
            return int(1e9)

    if (current_city, visited_cities_mask) in memoization_dict:
        return memoization_dict[(current_city, visited_cities_mask)]  # 현재 도시까지 방문한 최소 비용 반환

    minimum_cost = int(1e9)
    for next_city in range(1, number_of_cities):
        if travel_cost_matrix[current_city][next_city] == 0 or visited_cities_mask & (1 << next_city):
            continue
        travel_cost = depth_first_search(next_city, visited_cities_mask | (1 << next_city)) + travel_cost_matrix[current_city][next_city]
        minimum_cost = min(travel_cost, minimum_cost)
    memoization_dict[(current_city, visited_cities_mask)] = minimum_cost
    return minimum_cost 

print(depth_first_search(0, 1))
