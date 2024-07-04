#include <bits/stdc++.h>
#define emplace_back emplace_back
#define emplace emplace
#define all(v) v.begin(), v.end()
#define first_element first
#define second_element second

using namespace std;

typedef long long long_long_type;
typedef pair <int, int> pair_of_integers;
typedef pair <long_long_type, long_long_type> pair_of_long_longs;

const int MAXIMUM_NODES = 101010;
const int INF = 1e9;
const long_long_type LONG_INFINITY = 9e18;

pair <pair_of_integers, long_long_type> EdgeList[MAXIMUM_NODES];
vector <pair <int, long_long_type> > adjacency_list[MAXIMUM_NODES];

class SegmentTree {
    struct TreeNode {
        long_long_type left_maximum = -LONG_INFINITY, right_minimum = -LONG_INFINITY, left_contribution = -LONG_INFINITY, right_contribution = -LONG_INFINITY, contribution = -LONG_INFINITY, segment_sum = 0, maximum = -LONG_INFINITY;
        TreeNode operator + (TreeNode right_node) {
            TreeNode result_node;
            result_node.left_maximum = max(left_maximum, segment_sum + right_node.left_maximum);
            result_node.right_minimum = max(right_node.right_minimum, right_minimum - right_node.segment_sum);
            result_node.left_contribution = max({left_contribution, right_node.left_contribution - segment_sum, right_node.left_maximum + contribution});
            result_node.right_contribution = max({right_node.right_contribution, right_contribution + right_node.segment_sum, right_minimum + right_node.contribution});
            result_node.contribution = max(contribution + right_node.segment_sum, right_node.contribution - segment_sum);
            result_node.segment_sum = segment_sum + right_node.segment_sum;
            result_node.maximum = max({maximum, right_node.maximum, right_minimum + right_node.left_contribution, right_contribution + right_node.left_maximum});
            return result_node;
        }
    };
    vector <TreeNode> segment_tree;
    int tree_size;
public: 
    SegmentTree() {}
    void Initialize(int number_of_elements) {
        tree_size = number_of_elements;
        segment_tree.resize(4 * number_of_elements + 10);
    }

    void update_internal(int node_index, int segment_start, int segment_end, int element_index, long_long_type value) {
        if(segment_start == segment_end) {
            segment_tree[node_index].left_maximum = segment_tree[node_index].segment_sum = value;
            segment_tree[node_index].right_minimum = -value;
            segment_tree[node_index].maximum = segment_tree[node_index].left_contribution = segment_tree[node_index].right_contribution = segment_tree[node_index].contribution = abs(value);
            return;
        }
        int mid = (segment_start + segment_end) / 2;
        if(element_index <= mid) update_internal(node_index * 2, segment_start, mid, element_index, value);
        else update_internal(node_index * 2 + 1, mid + 1, segment_end, element_index, value);
        segment_tree[node_index] = segment_tree[node_index * 2] + segment_tree[node_index * 2 + 1];
    }

    void Update(int element_index, long_long_type value) {
        update_internal(1, 1, tree_size, element_index, value);
    }

    long_long_type get_maximum() {
        return segment_tree[1].maximum;
    }
} SegmentTreeInstance;

int in_time[MAXIMUM_NODES], out_time[MAXIMUM_NODES], timestamp;

void depth_first_search(int current_node, int parent_node) {
    in_time[current_node] = out_time[current_node] = timestamp++;
    for(auto neighbor : adjacency_list[current_node]) {
        if(neighbor.first_element == parent_node) continue;
        SegmentTreeInstance.Update(timestamp, neighbor.second_element);
        depth_first_search(neighbor.first_element, current_node);
        out_time[current_node] = timestamp++;
        SegmentTreeInstance.Update(out_time[current_node], -neighbor.second_element);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int number_of_nodes, number_of_queries; long_long_type weight_limit;
    cin >> number_of_nodes >> number_of_queries >> weight_limit;
    SegmentTreeInstance.Initialize(2 * number_of_nodes - 2);
    for(int i = 0; i < number_of_nodes - 1; i++) {
        int node_u, node_v; long_long_type weight;
        cin >> node_u >> node_v >> weight;
        adjacency_list[node_u].emplace_back(node_v, weight);
        adjacency_list[node_v].emplace_back(node_u, weight);
        EdgeList[i] = {{node_u, node_v}, weight};
    }

    depth_first_search(1, 0);
    long_long_type result = 0;
    while(number_of_queries--) {
        long_long_type d, e;
        cin >> d >> e;
        d = (d + result) % (number_of_nodes - 1);
        e = (e + result) % weight_limit;
        int node_u = EdgeList[d].first_element.first_element, node_v = EdgeList[d].first_element.second_element;
        if(in_time[node_u] < in_time[node_v]) swap(node_u, node_v);
        SegmentTreeInstance.Update(in_time[node_u], e);
        SegmentTreeInstance.Update(out_time[node_u] + 1, -e);
        result = SegmentTreeInstance.get_maximum();
        cout << result << '\n';
    }
}
