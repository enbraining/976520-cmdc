#include<bits/stdc++.h>
using namespace std;

const int MAXIMUM_NUMBER = 1e6;

int array_of_elements[MAXIMUM_NUMBER + 5];
int start_number[MAXIMUM_NUMBER + 5], end_number[MAXIMUM_NUMBER + 5];
vector<int> unique_elements, segment_tree_roots(MAXIMUM_NUMBER + 5);
int number_of_elements, number_of_queries;

struct SegmentTreeNode {
    int left_child, right_child;
    int count;
    SegmentTreeNode() : count(0) {};
};

vector<SegmentTreeNode> segment_tree(MAXIMUM_NUMBER * 50);
int total_nodes;

void initialize_segment_tree() {
    total_nodes = number_of_elements << 1;
    for(int index = 1; index < number_of_elements; ++index) {
        segment_tree[index].left_child = index << 1;
        segment_tree[index].right_child = index << 1 | 1;
    }
}

void update_segment_tree(int node_index, int start_index, int end_index, int update_index, int value) {
    segment_tree[node_index].count += value;
    if(start_index != end_index) {
        int middle_index = (start_index + end_index) >> 1;
        int left_child_index = segment_tree[node_index].left_child;
        int right_child_index = segment_tree[node_index].right_child;
        if(update_index <= middle_index) {
            segment_tree[node_index].left_child = total_nodes;
            segment_tree[total_nodes++] = segment_tree[left_child_index];
            update_segment_tree(segment_tree[node_index].left_child, start_index, middle_index, update_index, value);
        } else {
            segment_tree[node_index].right_child = total_nodes;
            segment_tree[total_nodes++] = segment_tree[right_child_index];
            update_segment_tree(segment_tree[node_index].right_child, middle_index + 1, end_index, update_index, value);
        }
    }
}

int query_segment_tree(int node_index, int start_index, int end_index, int query_start, int query_end) {
    if(query_start <= start_index && end_index <= query_end) return segment_tree[node_index].count;
    if(end_index < query_start || start_index > query_end) return 0;
    int middle_index = (start_index + end_index) >> 1;
    int left_child_index = segment_tree[node_index].left_child;
    int right_child_index = segment_tree[node_index].right_child;
    return query_segment_tree(left_child_index, start_index, middle_index, query_start, query_end) + 
           query_segment_tree(right_child_index, middle_index + 1, end_index, query_start, query_end);
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> number_of_elements;
    
    for(int index = 1; index <= number_of_elements; ++index) {
        cin >> array_of_elements[index];
        unique_elements.push_back(array_of_elements[index]);
    }
    
    sort(unique_elements.begin(), unique_elements.end());
    unique_elements.erase(unique(unique_elements.begin(), unique_elements.end()), unique_elements.end());
    
    for(int index = 1; index <= number_of_elements; ++index) {
        array_of_elements[index] = lower_bound(unique_elements.begin(), unique_elements.end(), array_of_elements[index]) - unique_elements.begin();
    }
    
    vector<int> previous_index(unique_elements.size(), 0);
    vector<int> previous_occurrence(number_of_elements + 1, -1);
    
    for(int index = 1; index <= number_of_elements; ++index) {
        if(previous_index[array_of_elements[index]] != 0) {
            previous_occurrence[index] = previous_index[array_of_elements[index]];
        }
        previous_index[array_of_elements[index]] = index;
    }
    
    initialize_segment_tree();
    segment_tree_roots[0] = 1;
    int current_root = segment_tree_roots[0];
    
    for(int index = 1; index <= number_of_elements; ++index) {
        segment_tree[total_nodes] = segment_tree[current_root];
        current_root = total_nodes++;
        update_segment_tree(current_root, 1, number_of_elements, index, 1);
        
        if(previous_occurrence[index] != -1) {
            segment_tree[total_nodes] = segment_tree[current_root];
            current_root = total_nodes++;
            update_segment_tree(current_root, 1, number_of_elements, previous_occurrence[index], -1);
        }
        segment_tree_roots[index] = current_root;
    }
    
    cin >> number_of_queries;
    int query_result = 0;
    
    for(int query_index = 0; query_index < number_of_queries; ++query_index) {
        int query_left, query_right; 
        cin >> query_left >> query_right;
        int actual_left = query_left + query_result;
        assert(actual_left <= query_right);
        query_result = query_segment_tree(segment_tree_roots[query_right], 1, number_of_elements, actual_left, query_right);
        cout << query_result << '\n';
    }
    
    return 0;
}
