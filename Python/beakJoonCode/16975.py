import sys
input = sys.stdin.readline

class SegmentTreeWithLazyPropagation:
    def __init__(self, array_length, initial_values_list):
        self.segment_tree_array = [0] * (array_length * 4)
        self.lazy_propagation_array = [0] * (array_length * 4)
        self.initial_values_list = initial_values_list
        self.array_length = array_length
        
        start_index, end_index = 1, self.array_length
        self._initialize_segment_tree(1, start_index, end_index)

    def _initialize_segment_tree(self, current_node, start_index, end_index):
        if start_index == end_index:
            self.segment_tree_array[current_node] = self.initial_values_list[start_index]
            return
        middle_index = (start_index + end_index) // 2
        self._initialize_segment_tree(current_node * 2, start_index, middle_index)
        self._initialize_segment_tree(current_node * 2 + 1, middle_index + 1, end_index)

    def _propagate_lazy_values(self, current_node, start_index, end_index):
        if self.lazy_propagation_array[current_node] != 0:
            if start_index != end_index:
                self.lazy_propagation_array[current_node * 2] += self.lazy_propagation_array[current_node]
                self.lazy_propagation_array[current_node * 2 + 1] += self.lazy_propagation_array[current_node]
            else:
                self.segment_tree_array[current_node] += self.lazy_propagation_array[current_node]
            self.lazy_propagation_array[current_node] = 0

    def update_range_with_value(self, update_start_index, update_end_index, update_value):
        start_index, end_index = 1, self.array_length
        self._update_range_internal(1, start_index, end_index, update_start_index, update_end_index, update_value)
    
    def _update_range_internal(self, current_node, start_index, end_index, update_start_index, update_end_index, update_value):
        self._propagate_lazy_values(current_node, start_index, end_index)
        if update_start_index > end_index or update_end_index < start_index:
            return

        if update_start_index <= start_index and end_index <= update_end_index:
            self.lazy_propagation_array[current_node] += update_value
            self._propagate_lazy_values(current_node, start_index, end_index)
            return
        
        if self.lazy_propagation_array[current_node] != 0:
            self.lazy_propagation_array[current_node * 2] += self.lazy_propagation_array[current_node]
            self.lazy_propagation_array[current_node * 2 + 1] += self.lazy_propagation_array[current_node]
            self.lazy_propagation_array[current_node] = 0
        
        middle_index = (start_index + end_index) // 2
        self._update_range_internal(current_node * 2, start_index, middle_index, update_start_index, update_end_index, update_value)
        self._update_range_internal(current_node * 2 + 1, middle_index + 1, end_index, update_start_index, update_end_index, update_value)

    def query_single_value(self, target_index):
        start_index, end_index = 1, self.array_length
        return self._query_single_value_internal(1, start_index, end_index, target_index)
    
    def _query_single_value_internal(self, current_node, start_index, end_index, target_index):
        self._propagate_lazy_values(current_node, start_index, end_index)
        
        if target_index == start_index == end_index:
            return self.segment_tree_array[current_node]
        if target_index < start_index or target_index > end_index:
            return 0

        middle_index = (start_index + end_index) // 2
        if target_index <= middle_index:
            return self._query_single_value_internal(current_node * 2, start_index, middle_index, target_index)
        else:
            return self._query_single_value_internal(current_node * 2 + 1, middle_index + 1, end_index, target_index)

def solve_problem_with_segment_tree():
    number_of_elements = int(input())
    initial_values_list = [0] + list(map(int, input().split()))
    number_of_queries = int(input())
    segment_tree = SegmentTreeWithLazyPropagation(number_of_elements, initial_values_list)

    for _ in range(number_of_queries):
        query_type, *query_parameters = map(int, input().split())
        if query_type == 1:
            update_start_index, update_end_index, update_value = query_parameters
            segment_tree.update_range_with_value(update_start_index, update_end_index, update_value)
        else:
            target_index = query_parameters[0]
            print(segment_tree.query_single_value(target_index))

solve_problem_with_segment_tree()
