import sys,collections
def user_input(): return map(int,sys.stdin.readline().split())

def breadth_first_search():
  deque_queue = collections.deque([0])
  parent_node = [-1]*number_of_nodes
  while deque_queue:
    current_node = deque_queue.popleft()
    for next_node in adjacent_list[current_node]:
      if graph_matrix[current_node][next_node]-flow_matrix[current_node][next_node] and parent_node[next_node]<0:
        parent_node[next_node] = current_node
        deque_queue.append(next_node)
        if next_node==number_of_nodes-1:
          return parent_node

def solve_maximum_flow_problem():
  while parent_path:=breadth_first_search():
    current_node = number_of_nodes-1; minimum_flow = 3**number_of_edges
    while current_node:
      previous_node = parent_path[current_node]
      minimum_flow = min(minimum_flow,graph_matrix[previous_node][current_node]-flow_matrix[previous_node][current_node])
      current_node = previous_node
    current_node = number_of_nodes-1
    while current_node:
      previous_node = parent_path[current_node]
      flow_matrix[previous_node][current_node] += minimum_flow; flow_matrix[current_node][previous_node] -= minimum_flow
      current_node = previous_node

number_of_nodes,number_of_edges = user_input()
graph_matrix = [[0]*number_of_nodes for i in range(number_of_nodes)]; adjacent_list = [[] for i in range(number_of_nodes)]
for i in range(number_of_edges):
  start_node,end_node = user_input()
  adjacent_list[start_node].append(end_node); adjacent_list[end_node].append(start_node)
  graph_matrix[start_node][end_node] = graph_matrix[end_node][start_node] = 3**i
flow_matrix = [[0]*number_of_nodes for i in range(number_of_nodes)]
solve_maximum_flow_problem()
print(sum(flow_matrix[i][-1] for i in range(number_of_nodes))%(10**9+7))
