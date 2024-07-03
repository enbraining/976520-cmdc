#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())

int parent[404040], component_id[404040];
int segment_left[404040], segment_right[404040];
int dual_left[404040], dual_right[404040];

int findSet(int vertex) { 
    return vertex == parent[vertex] ? vertex : parent[vertex] = findSet(parent[vertex]); 
}

void unionSets(int vertex_u, int vertex_v) {
    vertex_u = findSet(vertex_u), vertex_v = findSet(vertex_v);
    if (vertex_u != vertex_v) {
        parent[vertex_u] = vertex_v;
        segment_left[vertex_v] = min(segment_left[vertex_v], segment_left[vertex_u]);
        segment_right[vertex_v] = max(segment_right[vertex_v], segment_right[vertex_u]);
    }
}

long long ccw(const pair<long long, long long>& point_a, const pair<long long, long long>& point_b, const pair<long long, long long>& point_c) {
    long long delta_x1 = point_b.x - point_a.x, delta_y1 = point_b.y - point_a.y;
    long long delta_x2 = point_c.x - point_b.x, delta_y2 = point_c.y - point_b.y;
    long long cross_product = delta_x1 * delta_y2 - delta_x2 * delta_y1;
    if (cross_product > 0) return 1;
    if (cross_product < 0) return -1;
    return 0;
}

int num_points, num_edges, num_queries;
pair<long long, long long> points[101010];
vector<pair<long long, long long>> graph[404040];
vector<int> dual_points;

pair<long long, long long> base_point;
bool compareAngle(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    pair<long long, long long> point_a = points[a.x], point_b = points[b.x];
    if ((point_a > base_point) != (point_b > base_point)) return point_a > point_b;
    return ccw(point_a, base_point, point_b) > 0;
}

int outside_component;
void calculateDualGraph() {
    iota(parent, parent + 404040, 0);
    for (int i = 1; i <= num_points; i++) {
        base_point = points[i];
        sort(all(graph[i]), compareAngle);
        for (int j = 0; j < graph[i].size(); j++) {
            int k = j ? j - 1 : graph[i].size() - 1;
            int u = graph[i][k].y << 1 | 1, v = graph[i][j].y << 1;
            pair<long long, long long> point1 = points[graph[i][k].x], point2 = points[graph[i][j].x];
            if (point1 > base_point) u ^= 1;
            if (point2 > base_point) v ^= 1;
            unionSets(u, v);
        }
    }
    for (int i = 1; i <= num_edges; i++) {
        component_id[i << 1] = findSet(i << 1);
        component_id[i << 1 | 1] = findSet(i << 1 | 1);
    }
    int min_index = min_element(points + 1, points + num_points + 1) - points;
    outside_component = component_id[graph[min_index][0].y << 1 | 1];
    for (int i = 1; i <= num_edges; i++) {
        dual_points.push_back(component_id[i << 1]);
        dual_points.push_back(component_id[i << 1 | 1]);
    }
    compress(dual_points);
    for (int i = 0; i < dual_points.size(); i++) {
        dual_left[i] = segment_left[dual_points[i]];
        dual_right[i] = segment_right[dual_points[i]];
    }
    for (int i = 1; i <= num_edges; i++) {
        component_id[i << 1] = lower_bound(all(dual_points), i << 1) - dual_points.begin();
        component_id[i << 1 | 1] = lower_bound(all(dual_points), i << 1 | 1) - dual_points.begin();
    }
    outside_component = lower_bound(all(dual_points), outside_component) - dual_points.begin();
}

vector<int> compressed_points;
vector<int> segment_tree[1 << 20];
int tree_size = 1 << 19;

void addToSegmentTree(int index, int value) { 
    segment_tree[index | tree_size].push_back(value); 
}

int querySegmentTree(int left, int right, int query_left, int query_right) {
    left |= tree_size; right |= tree_size; 
    int result = 0;
    while (left <= right) {
        if (left & 1) {
            result += upper_bound(all(segment_tree[left]), query_right) - lower_bound(all(segment_tree[left]), query_left); 
            left++;
        }
        if (~right & 1) {
            result += upper_bound(all(segment_tree[right]), query_right) - lower_bound(all(segment_tree[right]), query_left); 
            right--;
        }
        left >>= 1, right >>= 1;
    }
    return result;
}

void buildSegmentTree() {
    for (int i = tree_size; i < tree_size + tree_size; i++) {
        if (segment_tree[i].size() >= 2) sort(all(segment_tree[i]));
    }
    for (int i = tree_size - 1; i; i--) {
        merge(all(segment_tree[i << 1]), all(segment_tree[i << 1 | 1]), back_inserter(segment_tree[i]));
    }
}

int prefix_sum[303030];
void preProcess() {
    for (int i = 1; i <= num_points; i++) {
        for (int j = -1; j <= 1; j++) compressed_points.push_back(points[i].x + j);
    }
    compress(compressed_points);
    for (int i = 1; i <= num_points; i++) {
        for (auto j : graph[i]) {
            if (points[i] > points[j.x]) continue;
            int a = lower_bound(all(compressed_points), points[i].x) - compressed_points.begin() + 1;
            int b = lower_bound(all(compressed_points), points[j.x].x) - compressed_points.begin() + 1;
            prefix_sum[a]++;
            prefix_sum[b]--;
        }
    }
    for (int i = 0; i < dual_points.size(); i++) {
        if (i == outside_component) continue;
        dual_left[i] = lower_bound(all(compressed_points), dual_left[i]) - compressed_points.begin() + 1;
        dual_right[i] = lower_bound(all(compressed_points), dual_right[i]) - compressed_points.begin() + 1;
        addToSegmentTree(dual_left[i], dual_right[i]);
    }
    buildSegmentTree();
    for (int i = 1; i < 303030; i++) {
        prefix_sum[i] += prefix_sum[i - 1];
    }
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cin >> num_points >> num_edges >> num_queries;
    for (int i = 1; i <= num_points; i++) {
        cin >> points[i].x >> points[i].y;
    }
    for (int i = 1; i <= num_edges; i++) {
        int start, end; 
        cin >> start >> end;
        graph[start].emplace_back(end, i);
        graph[end].emplace_back(start, i);
        segment_left[i << 1] = segment_left[i << 1 | 1] = min(points[start].x, points[end].x);
        segment_right[i << 1] = segment_right[i << 1 | 1] = max(points[start].x, points[end].x);
    }
    calculateDualGraph();
    preProcess();

    for (int i = 1; i <= num_queries; i++) {
        int query_left, query_right; 
        cin >> query_left >> query_right;
        query_left = lower_bound(all(compressed_points), query_left) - compressed_points.begin() + 1;
        query_right = lower_bound(all(compressed_points), query_right) - compressed_points.begin() + 1;
        int e = prefix_sum[query_left] + prefix_sum[query_right];
        int f = querySegmentTree(1, query_left, query_left, 303000) + querySegmentTree(1, query_right, query_right, 303000) - querySegmentTree(1, query_left, query_right, 303000);
        cout << e - f + 1 << "\n";
    }
}
