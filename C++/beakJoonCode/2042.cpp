#define MAXIMUM_ARRAY_SIZE 1000001
#include <iostream>
using namespace std;
 
int number_of_elements, number_of_updates, number_of_queries;
long long array_of_numbers[MAXIMUM_ARRAY_SIZE];
 
long long segment_tree[4000004];
 
long long initialize_segment_tree(int segment_start, int segment_end, int node_index) {
    if (segment_start == segment_end) {
        return segment_tree[node_index] = array_of_numbers[segment_start];
    }
    int segment_mid = (segment_start + segment_end) / 2;
    return segment_tree[node_index] = initialize_segment_tree(segment_start, segment_mid, node_index * 2) + initialize_segment_tree(segment_mid + 1, segment_end, node_index * 2 + 1);
}
 
long long query_sum(int segment_start, int segment_end, int node_index, int query_start, int query_end) {
    if (query_start > segment_end || query_end < segment_start) {
        return 0;
    }
    if (query_start <= segment_start && segment_end <= query_end) {
        return segment_tree[node_index];
    }
    int segment_mid = (segment_start + segment_end) / 2;
    return query_sum(segment_start, segment_mid, node_index * 2, query_start, query_end) + query_sum(segment_mid + 1, segment_end, node_index * 2 + 1, query_start, query_end);
}
 
void update_segment_tree(int segment_start, int segment_end, int node_index, int update_index, long long difference) {
    if (update_index < segment_start || segment_end < update_index) {
        return;
    }
    segment_tree[node_index] += difference;
    if (segment_start == segment_end) {
        return;
    }
    int segment_mid = (segment_start + segment_end) / 2;
    update_segment_tree(segment_start, segment_mid, node_index * 2, update_index, difference);
    update_segment_tree(segment_mid + 1, segment_end, node_index * 2 + 1, update_index, difference);
}
 
int main() {
    cin >> number_of_elements >> number_of_updates >> number_of_queries;
 
    for (int i = 0; i < number_of_elements; i++) {
        cin >> array_of_numbers[i];
    }
 
    initialize_segment_tree(0, number_of_elements - 1, 1);
 
    long long operation_type, query_start, query_end;
    for (int i = 0; i < number_of_updates + number_of_queries; i++) {
        cin >> operation_type >> query_start >> query_end;
        if (operation_type == 1) {
            long long difference = query_end - array_of_numbers[query_start - 1];
            array_of_numbers[query_start - 1] = query_end;
            update_segment_tree(0, number_of_elements - 1, 1, query_start - 1, difference);
        } else if (operation_type == 2) {
            cout << query_sum(0, number_of_elements - 1, 1, query_start - 1, query_end - 1) << "\n";
        }
    }
    return 0;
}
