#include<stdio.h>

int array_of_elements[100000];

class SegmentTreeForSum {
    long long int segment_tree_nodes[1 << 20];

    public:
    void InitializeSegmentTree(int current_node, int range_left, int range_right) {
        if (range_left == range_right) {
            segment_tree_nodes[current_node] = array_of_elements[range_left];
            return;
        }
        int range_mid = (range_left + range_right) / 2;
        InitializeSegmentTree(current_node * 2, range_left, range_mid);
        InitializeSegmentTree(current_node * 2 + 1, range_mid + 1, range_right);
    }

    void UpdateRangeSum(int current_node, int update_left, int update_right, int segment_start, int segment_end, int update_value) {
        if (update_left >= segment_start && update_right <= segment_end) {
            segment_tree_nodes[current_node] += update_value;
            return;
        }
        int segment_mid = (segment_start + segment_end) / 2;
        if (update_left <= segment_mid) {
            UpdateRangeSum(current_node * 2, update_left, update_right, segment_start, segment_mid, update_value);
        }
        if (update_right > segment_mid) {
            UpdateRangeSum(current_node * 2 + 1, update_left, update_right, segment_mid + 1, segment_end, update_value);
        }
    }

    long long int QueryPointValue(int current_node, int query_left, int query_right, int query_index) {
        if (query_left == query_right) {
            return segment_tree_nodes[current_node];
        }
        int query_mid = (query_left + query_right) / 2;
        if (query_index <= query_mid) {
            return QueryPointValue(current_node * 2, query_left, query_mid, query_index) + segment_tree_nodes[current_node];
        }
        if (query_index > query_mid) {
            return QueryPointValue(current_node * 2 + 1, query_mid + 1, query_right, query_index) + segment_tree_nodes[current_node];
        }
    }
};

int main() {
    int number_of_elements;
    scanf("%d", &number_of_elements);
    for (int element_index = 0; element_index < number_of_elements; element_index++) {
        scanf("%d", &array_of_elements[element_index]);
    }
    int number_of_queries;
    scanf("%d", &number_of_queries);
    SegmentTreeForSum *segment_tree = new SegmentTreeForSum();
    segment_tree->InitializeSegmentTree(1, 0, number_of_elements - 1);
    for (int query_index = 0; query_index < number_of_queries; query_index++) {
        int query_type, query_start, query_end, query_value;
        scanf("%d", &query_type);
        if (query_type == 1) {
            scanf("%d %d %d", &query_start, &query_end, &query_value);
            query_start--; query_end--;
            segment_tree->UpdateRangeSum(1, query_start, query_end, 0, number_of_elements - 1, query_value);
        } else {
            scanf("%d", &query_start);
            query_start--;
            printf("%lld\n", segment_tree->QueryPointValue(1, 0, number_of_elements - 1, query_start));
        }
    }
    return 0;
}
