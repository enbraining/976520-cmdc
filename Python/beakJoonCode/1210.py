import sys
input = sys.stdin.readline
from collections import deque

def BreadthFirstSearch():
    deque_queue = deque([0])
    levels = [0] * total_nodes
    levels[0] = 1
    level_adj_list = [[] for _ in range(total_nodes)]
    
    while deque_queue:
        current_node = deque_queue.popleft()
        for next_node in adjacency_list[current_node]:
            if capacity_graph[current_node][next_node]:
                if not levels[next_node]:
                    levels[next_node] = levels[current_node] + 1
                    deque_queue.append(next_node)
                if levels[next_node] == levels[current_node] + 1:
                    level_adj_list[current_node].append(next_node)
    
    if levels[total_nodes - 1]:
        return level_adj_list

def DepthFirstSearch(current_node, flow):
    if current_node == total_nodes - 1:
        return flow
    while level_adj_list[current_node]:
        next_node = level_adj_list[current_node].pop()
        flow_value = DepthFirstSearch(next_node, min(flow, capacity_graph[current_node][next_node]))
        if flow_value:
            capacity_graph[current_node][next_node] -= flow_value
            capacity_graph[next_node][current_node] += flow_value
            level_adj_list[current_node].append(next_node)
            return flow_value

def find_min_cut_set():
    deque_queue = deque([0])
    visited_nodes = [0] * total_nodes
    
    while deque_queue:
        current_node = deque_queue.popleft()
        for next_node in adjacency_list[current_node]:
            if capacity_graph[current_node][next_node] and not visited_nodes[next_node]:
                visited_nodes[next_node] = 1
                deque_queue.append(next_node)
    
    for i in range(1, num_nodes + 1):
        if visited_nodes[i] and not visited_nodes[i + num_nodes]:
            print(i, end=" ")

num_nodes, num_edges = map(int, input().split())
total_nodes = num_nodes * 2 + 2
capacity_graph = [[0] * total_nodes for _ in range(total_nodes)]
adjacency_list = [[] for _ in range(total_nodes)]

source_node, sink_node = map(int, input().split())
capacity_graph[0][source_node] = capacity_graph[sink_node + num_nodes][total_nodes - 1] = 1e12
adjacency_list[0].append(source_node)
adjacency_list[source_node].append(0)
adjacency_list[sink_node + num_nodes].append(total_nodes - 1)
adjacency_list[total_nodes - 1].append(sink_node + num_nodes)

for i in range(1, num_nodes + 1):
    capacity_graph[i][i + num_nodes] = int(input())
    adjacency_list[i].append(i + num_nodes)
    adjacency_list[i + num_nodes].append(i)

for _ in range(num_edges):
    node_a, node_b = map(int, input().split())
    capacity_graph[node_a + num_nodes][node_b] = capacity_graph[node_b + num_nodes][node_a] = 1e12
    adjacency_list[node_a + num_nodes].append(node_b)
    adjacency_list[node_b].append(node_a + num_nodes)
    adjacency_list[node_b + num_nodes].append(node_a)
    adjacency_list[node_a].append(node_b + num_nodes)

while level_adj_list := BreadthFirstSearch():
    while DepthFirstSearch(0, 1e12):
        pass

find_min_cut_set()
