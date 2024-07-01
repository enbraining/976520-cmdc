#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    unsigned int tree[1 << 20], lazy[1 << 20][2]; 
    unsigned int size = 1 << 19;

    void build() {
        for (unsigned int i = size - 1; i > 0; i--) {
            tree[i] = (tree[i << 1] + tree[i << 1 | 1]);
        }
    }

    void propagate(unsigned int node, unsigned int nodeL, unsigned int nodeR) {
        auto& [mul, add] = lazy[node];
        if (mul == 1 && add == 0) return;
        if (nodeL != nodeR) {
            for (unsigned int i = node * 2; i <= node * 2 + 1; i++) {
                auto& [cmul, cadd] = lazy[i];
                cmul = (1LL * mul * cmul);
                cadd = (1LL * mul * cadd + add);
            }
        }
        tree[node] = (1LL * mul * tree[node] + 1LL * (nodeR - nodeL + 1) * add);
        mul = 1, add = 0;
    }

    void update(unsigned int L, unsigned int R, unsigned int nodeNum, unsigned int nodeL, unsigned int nodeR, unsigned int mul, unsigned int add) {
        propagate(nodeNum, nodeL, nodeR);
        if (R < nodeL || nodeR < L) return;
        if (L <= nodeL && nodeR <= R) {
            auto& [mul_, add_] = lazy[nodeNum];
            mul_ = (1LL * mul_ * mul);
            add_ = (1LL * add_ * mul + add);
            propagate(nodeNum, nodeL, nodeR);
            return;
        }
        unsigned int mid = nodeL + nodeR >> 1;
        update(L, R, nodeNum << 1, nodeL, mid, mul, add);
        update(L, R, nodeNum << 1 | 1, mid + 1, nodeR, mul, add);
        tree[nodeNum] = (tree[nodeNum << 1] + tree[nodeNum << 1 | 1]);
    }

    void update(unsigned int l, unsigned int r, unsigned int mul, unsigned int add) {
        update(l, r, 1, 1, size, mul, add);
    }

    unsigned int query(unsigned int L, unsigned int R, unsigned int nodeNum, unsigned int nodeL, unsigned int nodeR) {
        propagate(nodeNum, nodeL, nodeR);
        if (R < nodeL || nodeR < L) return 0;
        if (L <= nodeL && nodeR <= R) return tree[nodeNum];
        unsigned int mid = nodeL + nodeR >> 1;
        return (query(L, R, nodeNum << 1, nodeL, mid) + query(L, R, nodeNum << 1 | 1, mid + 1, nodeR));
    }

    unsigned int query(unsigned int l, unsigned int r) {
        return query(l, r, 1, 1, size);
    }
};

struct HeavyLightDecomposition {
    unsigned int nodes, queries;
    unsigned int subtree_size[1 << 19], depth[1 << 19], parent[1 << 19];
    unsigned int top_node[1 << 19], in_time[1 << 19], out_time[1 << 19];
    vector<unsigned int> input_edges[1 << 19], adjacency_list[1 << 19];

    bitset<1 << 19> visited;

    void dfs(unsigned int current = 1) {
        visited[current] = true;
        for (auto next : input_edges[current]) {
            if (visited[next]) continue;
            adjacency_list[current].push_back(next);
            dfs(next);
        }
    }

    void dfs_subtree(unsigned int current = 1) {
        subtree_size[current] = 1;
        for (auto& next : adjacency_list[current]) {
            depth[next] = depth[current] + 1; 
            parent[next] = current;
            dfs_subtree(next); 
            subtree_size[current] += subtree_size[next];
            if (subtree_size[next] > subtree_size[adjacency_list[current][0]]) {
                swap(next, adjacency_list[current][0]);
            }
        }
    }

    unsigned int time_stamp;
    void dfs_build_hld(unsigned int current = 1) {
        in_time[current] = ++time_stamp;
        for (auto next : adjacency_list[current]) {
            top_node[next] = (next == adjacency_list[current][0] ? top_node[current] : next);
            dfs_build_hld(next);
        }
        out_time[current] = time_stamp;
    }

    SegmentTree segment_tree;

    void preprocess() {
        cin >> nodes >> queries;
        for (unsigned int i = 0; i < 1 << 20; i++) { 
            segment_tree.lazy[i][0] = 1; 
        }
        for (unsigned int i = 1; i <= nodes - 1; i++) {
            unsigned int a, b; cin >> a >> b;
            input_edges[a].push_back(b);
            input_edges[b].push_back(a);
        }
        top_node[1] = 1;
        dfs(), dfs_subtree(), dfs_build_hld();
    }

    unsigned int find_lca(unsigned int a, unsigned int b) {
        while (top_node[a] != top_node[b]) {
            if (depth[top_node[a]] < depth[top_node[b]]) {
                swap(a, b);
            }
            a = parent[top_node[a]];
        }
        if (depth[a] > depth[b]) swap(a, b);
        return a;
    }
} hld;

void update_subtree(unsigned int node, unsigned int mul, unsigned int add) {
    hld.segment_tree.update(hld.in_time[node], hld.out_time[node], mul, add);
}

void update_path(unsigned int a, unsigned int b, unsigned int mul, unsigned int add) {
    while (hld.top_node[a] != hld.top_node[b]) {
        if (hld.depth[hld.top_node[a]] < hld.depth[hld.top_node[b]]) {
            swap(a, b);
        }
        unsigned int start_node = hld.top_node[a];
        hld.segment_tree.update(hld.in_time[start_node], hld.in_time[a], mul, add);
        a = hld.parent[start_node];
    }
    if (hld.depth[a] > hld.depth[b]) swap(a, b);
    hld.segment_tree.update(hld.in_time[a], hld.in_time[b], mul, add);
}

unsigned int query_subtree(unsigned int node) {
    return hld.segment_tree.query(hld.in_time[node], hld.out_time[node]);
}

unsigned int query_path(unsigned int a, unsigned int b) {
    unsigned int result = 0;
    while (hld.top_node[a] != hld.top_node[b]) {
        if (hld.depth[hld.top_node[a]] < hld.depth[hld.top_node[b]]) {
            swap(a, b);
        }
        unsigned int start_node = hld.top_node[a];
        result = (result + hld.segment_tree.query(hld.in_time[start_node], hld.in_time[a]));
        a = hld.parent[start_node];
    }
    if (hld.depth[a] > hld.depth[b]) { 
        swap(a, b); 
    }
    result = (result + hld.segment_tree.query(hld.in_time[a], hld.in_time[b]));
    return result;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    hld.preprocess();
    while (hld.queries--) {
        unsigned int type, a, b, k; cin >> type;
        if (type == 1) { 
            cin >> a >> k; update_subtree(a, 1, k); 
        } else if (type == 2) { 
            cin >> a >> b >> k; update_path(a, b, 1, k); 
        } else if (type == 3) { 
            cin >> a >> k; update_subtree(a, k, 0); 
        } else if (type == 4) { 
            cin >> a >> b >> k; update_path(a, b, k, 0); 
        } else if (type == 5) { 
            cin >> a; cout << query_subtree(a) << '\n'; 
        } else if (type == 6) { 
            cin >> a >> b; cout << query_path(a, b) << '\n'; 
        }
    }
}
