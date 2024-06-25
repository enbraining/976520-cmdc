import sys
user_input = sys.stdin.readline
number_of_elements = int(user_input())
number_list = list(map(int, user_input().split()))
class MergeSortTreeDataStructure:
    def __init__(self):
        self.merge_sort_tree = [list() for _ in range(4 * number_of_elements)]

        def initialize_merge_sort_tree(start_index, end_index, current_node_index):
            if start_index == end_index:
                self.merge_sort_tree[current_node_index] = [number_list[start_index]]
                return
            middle_index = (start_index + end_index) // 2
            initialize_merge_sort_tree(start_index, middle_index, current_node_index * 2)
            initialize_merge_sort_tree(middle_index + 1, end_index, current_node_index * 2 + 1)

            left_index, right_index = 0, 0
            while left_index < middle_index - start_index + 1 and right_index < end_index - middle_index:
                if self.merge_sort_tree[current_node_index * 2][left_index] > self.merge_sort_tree[current_node_index * 2 + 1][right_index]:
                    self.merge_sort_tree[current_node_index].append(self.merge_sort_tree[current_node_index * 2 + 1][right_index])
                    right_index += 1
                else:
                    self.merge_sort_tree[current_node_index].append(self.merge_sort_tree[current_node_index * 2][left_index])
                    left_index += 1
            while right_index < end_index - middle_index:
                self.merge_sort_tree[current_node_index].append(self.merge_sort_tree[current_node_index * 2 + 1][right_index])
                right_index += 1
            while left_index < middle_index - start_index + 1:
                self.merge_sort_tree[current_node_index].append(self.merge_sort_tree[current_node_index * 2][left_index])
                left_index += 1

        initialize_merge_sort_tree(0, number_of_elements - 1, 1)

    def search_in_merge_sort_tree(self, left_query_index, right_query_index, target_value):
        left_query_index -= 1
        right_query_index -= 1

        def upper_bound_in_merge_sort_tree(start_index, end_index, current_node_index):
            while start_index < end_index:
                middle_index = (start_index + end_index) // 2
                if self.merge_sort_tree[current_node_index][middle_index] <= target_value:
                    start_index = middle_index + 1
                else:
                    end_index = middle_index
            return len(self.merge_sort_tree[current_node_index]) - end_index

        def search_in_merge_sort_tree_recursive(start_index, end_index, current_node_index):
            if right_query_index < start_index or left_query_index > end_index:
                return 0
            if left_query_index <= start_index <= end_index <= right_query_index:
                return upper_bound_in_merge_sort_tree(0, end_index - start_index + 1, current_node_index)
            middle_index = (start_index + end_index) // 2
            left_value = search_in_merge_sort_tree_recursive(start_index, middle_index, current_node_index * 2)
            right_value = search_in_merge_sort_tree_recursive(middle_index + 1, end_index, current_node_index * 2 + 1)
            return (left_value + right_value)

        print(search_in_merge_sort_tree_recursive(0, number_of_elements - 1, 1))

merge_sort_tree_data_structure = MergeSortTreeDataStructure()
for _ in range(int(user_input())):
    left_query_index, right_query_index, target_value = map(int, user_input().split())
    merge_sort_tree_data_structure.search_in_merge_sort_tree(left_query_index, right_query_index, target_value)
