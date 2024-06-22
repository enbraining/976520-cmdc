import sys
from collections import deque

def calculate_build_times(build_queue, incoming_edges, build_times):
    while build_queue:
        current_building = build_queue.popleft()
        current_time = build_times[current_building]
        
        for next_building in adjacency_list[current_building]:
            incoming_edges[next_building] -= 1
            if incoming_edges[next_building] == 0:
                build_queue.append(next_building)
            build_times[next_building] = max(build_times[next_building], current_time + construction_times[next_building])

    print(build_times[target_building])

num_tests = int(sys.stdin.readline())
for _ in range(num_tests):
    num_buildings, num_rules = map(int, sys.stdin.readline().split())
    construction_times = [-1] + list(map(int, sys.stdin.readline().split()))
    adjacency_list = {i: [] for i in range(1, num_buildings + 1)}
    incoming_edges = {i: 0 for i in range(1, num_buildings + 1)}
    
    for _ in range(num_rules):
        prerequisite, subsequent = map(int, sys.stdin.readline().split())
        adjacency_list[prerequisite].append(subsequent)
        incoming_edges[subsequent] += 1
    
    target_building = int(sys.stdin.readline())
    
    build_queue = deque()
    build_times = [-1] + [0] * num_buildings
    
    for building in range(1, num_buildings + 1):
        if incoming_edges[building] == 0:
            build_queue.append(building)
            build_times[building] = construction_times[building]
    
    calculate_build_times(build_queue, incoming_edges, build_times)
