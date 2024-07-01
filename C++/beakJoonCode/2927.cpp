#include <bits/stdc++.h>
#define X first
#define Y second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ini(x, y) memset(x, y, sizeof(x))
#define endl '\n'
using namespace std;

const int MOD = 1e9 + 7;
const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

int parent[30000];
const int SIZE = 1 << 15;
int segment_tree[SIZE << 1];
vector<int> adjacency_list[30000];
int parent_node[30000], subtree_size[30000], depth[30000];
int node_index[30000], heavy_light_decomposition[30000], node_count;
 
int find_set(int node) {
    if (parent[node] < 0) return node;
    return parent[node] = find_set(parent[node]);
}

void union_sets(int a, int b) {
    a = find_set(a), b = find_set(b);
    if (a != b) parent[b] = a;
}

void update_segment_tree(int index, int value) {
    for (segment_tree[index += SIZE] = value; index >>= 1; )
        segment_tree[index] = segment_tree[index << 1] + segment_tree[index << 1 | 1];
}

int query_segment_tree(int left, int right) {
    int result = 0;
    for (left += SIZE, right += SIZE; left <= right; left >>= 1, right >>= 1) {
        if (left & 1) result += segment_tree[left++];
        if (~right & 1) result += segment_tree[right--];
    }
    return result;
}

void first_dfs(int current_node) {
    subtree_size[current_node] = 1;
    for (int next_node : adjacency_list[current_node]) {
        if (!subtree_size[next_node]) {
            parent_node[next_node] = current_node;
            depth[next_node] = depth[current_node] + 1;
            first_dfs(next_node);
            subtree_size[current_node] += subtree_size[next_node];
        }
    }
}

void second_dfs(int current_node, int previous_node = -1) {
    node_index[current_node] = node_count++;
    for (int next_node : adjacency_list[current_node]) {
        if (previous_node != next_node && subtree_size[next_node] << 1 >= subtree_size[current_node]) {
            heavy_light_decomposition[next_node] = heavy_light_decomposition[current_node];
            second_dfs(next_node, current_node);
        }
    }
    for (int next_node : adjacency_list[current_node]) {
        if (previous_node != next_node && subtree_size[next_node] << 1 < subtree_size[current_node]) {
            heavy_light_decomposition[next_node] = next_node;
            second_dfs(next_node, current_node);
        }
    }
}

int heavy_light_decomposition_query(int a, int b) {
    int result = 0;
    while (heavy_light_decomposition[a] != heavy_light_decomposition[b]) {
        if (depth[heavy_light_decomposition[a]] < depth[heavy_light_decomposition[b]]) 
            swap(a, b);
        result += query_segment_tree(node_index[heavy_light_decomposition[a]], node_index[a]);
        a = parent_node[heavy_light_decomposition[a]];
    }
    if (depth[a] < depth[b]) 
        swap(a, b);
    return result + query_segment_tree(node_index[b], node_index[a]);
}
 
int main() {
    cin.sync_with_stdio(false); cin.tie(nullptr); 
    ini(parent, -1);
    int N;
    cin >> N;
 
    int penguins[30000];
    for (int i = 0; i < N; ++i) 
        cin >> penguins[i];
 
    int Q;
    cin >> Q;
 
    string command;
    vector<tuple<int, int, int>> queries(Q);
    for (int a, b, i = 0; i < Q; ++i) {
        cin >> command >> a >> b;
        queries[i] = { command[0] == 'e' ? 2 : command[0] == 'p', a, b };
    }
 
    int answers[300000]; 
    ini(answers, -1);
    for (int i = 0; i < Q; ++i) {
        auto[operation, a, b] = queries[i];
 
        switch (operation) {
        case 0:
            if (find_set(--a) != find_set(--b)) {
                union_sets(a, b);
                adjacency_list[a].push_back(b);
                adjacency_list[b].push_back(a);
                answers[i] = 1;
            } else {
                answers[i] = 0;
            }
            break;
        case 2:
            if (find_set(--a) != find_set(--b)) 
                answers[i] = -2;
            break;
        }
    }
 
    for (int i = 0; i < N; ++i) 
        if (subtree_size[i] == 0) {
            first_dfs(i);
            second_dfs(i);
        }

    for (int i = 0; i < N; ++i) 
        update_segment_tree(node_index[i], penguins[i]);
 
    for (int i = 0; i < Q; ++i) {
        auto[operation, a, b] = queries[i];
 
        switch (operation) {
        case 1:
            update_segment_tree(node_index[a - 1], b);
            break;
        case 2:
            if (answers[i] != -2) 
                answers[i] = heavy_light_decomposition_query(a - 1, b - 1);
            break;
        }
    }
 
    for (int i = 0; i < Q; ++i) {
        auto[operation, a, b] = queries[i];
 
        switch (operation) {
        case 0:
            if (answers[i]) 
                cout << "yes\n";
            else 
                cout << "no\n";
            break;
        case 2:
            if (answers[i] == -2) 
                cout << "impossible\n";
            else 
                cout << answers[i] << endl;
        }
    }
    return 0;
}
