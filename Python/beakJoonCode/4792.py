import sys
import heapq

def union_of_two_nodes(first_node, second_node):
    root_of_first_node = find_representative_node(first_node)
    root_of_second_node = find_representative_node(second_node)
    if root_of_first_node == root_of_second_node:
        return False
    else:
        parent_nodes[root_of_second_node] = root_of_first_node
        return True
    
def find_representative_node(current_node):
    if parent_nodes[current_node] == current_node:
        return current_node
    else:
        parent_nodes[current_node] = find_representative_node(parent_nodes[current_node])
        return parent_nodes[current_node]
    


def kruskal_minimum_spanning_tree(priority_queue):
    edge_count_in_mst, blue_edge_count_in_mst = 0, 0
    while priority_queue:
        edge_cost, start_node, end_node, edge_color = heapq.heappop(priority_queue)
        if union_of_two_nodes(start_node, end_node):
            if edge_color == 'B':
                blue_edge_count_in_mst += 1
            edge_count_in_mst += 1
            if edge_count_in_mst == total_number_of_nodes - 1:
                return blue_edge_count_in_mst
while True:
    total_number_of_nodes, total_number_of_edges, required_number_of_blue_edges = map(int, sys.stdin.readline().rstrip().split())
    if total_number_of_nodes == 0 and total_number_of_edges == 0 and required_number_of_blue_edges == 0:
        break
    red_edge_priority_queue, blue_edge_priority_queue = [], []
    for _ in range(total_number_of_edges):
        edge_color, start_node, end_node = sys.stdin.readline().rstrip().split()
        start_node, end_node = int(start_node), int(end_node)
        if edge_color == 'R':
            heapq.heappush(red_edge_priority_queue, [0, start_node, end_node, edge_color])
            heapq.heappush(blue_edge_priority_queue, [1, start_node, end_node, edge_color])
        else:
            heapq.heappush(red_edge_priority_queue, [1, start_node, end_node, edge_color])
            heapq.heappush(blue_edge_priority_queue, [0, start_node, end_node, edge_color])

    parent_nodes = [i for i in range(total_number_of_nodes + 1)]
    minimum_blue_edge_count = kruskal_minimum_spanning_tree(red_edge_priority_queue)

    parent_nodes = [i for i in range(total_number_of_nodes + 1)]
    maximum_blue_edge_count = kruskal_minimum_spanning_tree(blue_edge_priority_queue)

    if minimum_blue_edge_count <= required_number_of_blue_edges and required_number_of_blue_edges <= maximum_blue_edge_count:
        print(1)
    else:
        print(0)
