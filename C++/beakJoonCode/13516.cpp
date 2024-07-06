/*
Heavy Light Decomposition을 이용해 트리를 chain 단위로 분리
chain을 이차원 배열로 부모 노드쪽으로 압축

더하는게 아니라 최댓값 산출이기 때문에 역원이 없움 -> insert, erase 를 이용해서 max값을 관리

멀티셋 연산이 쿼리 당 O(log n)번 호출이ㅣㅣ 때문에 최종 시간복잡도는 O(n + q * log^2 n)
*/


#include <bits/stdc++.h>
using namespace std;
template<class Func>

struct RecursiveLambda {
    Func func;
    RecursiveLambda(Func&& func_) : func(std::forward<Func>(func_)) {}
    template<class... Args>
    auto operator()(Args&&... args) const {
        return func(*this, std::forward<Args>(args)...);
    }
};

template<typename NodeType, typename FuncMerge>
struct SegmentTree {
public:
    using Node = NodeType;
    SegmentTree() : SegmentTree(0, Node()) {}
    explicit SegmentTree(int n, const Node& e) : n(n), log(Log2(n)), size(1 << log), e(e), tree(size << 1, e) {}
    void Set(int i, const Node& val) { tree[--i | size] = val; }
    void Init() { for (int i = size - 1; i; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]); }
    void Update(int i, const Node& val) {
        tree[--i |= size] = val;
        while (i >>= 1) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
    Node Query(int i) const { return tree[--i | size]; }
    Node Query(int l, int r) const {
        Node L = e, R = e;
        for (--l |= size, --r |= size; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) L = merge(L, tree[l++]);
            if (~r & 1) R = merge(tree[r--], R);
        }
        return merge(L, R);
    }
private:
    const int n, log, size;
    const Node e;
    vector<Node> tree;
    FuncMerge merge;
    static int Log2(int n) {
        int ret = 0;
        while (n > 1 << ret) ret++;
        return ret;
    }
};

struct NodeData {
    int color, flag, max_length, empty;
    int operator() (int x) const { return color == x ? max_length : 0; }
};

struct FunctionMerge {
    NodeData operator() (const NodeData& a, const NodeData& b) const {
        if (a.empty) return b;
        if (b.empty) return a;
        return NodeData{ a.color, a.flag && a.color == b.color && b.flag, a.flag && a.color == b.color ? max(a.max_length, b.max_length) : a.max_length, 0 };
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int number_of_nodes;
    cin >> number_of_nodes;
    vector<vector<int>> adj(number_of_nodes + 1, vector<int>(0));
    for (int i = 1; i < number_of_nodes; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> subtree_size(number_of_nodes + 1, 0), depth(number_of_nodes + 1, 0), parent(number_of_nodes + 1, 0);
    vector<int> in_order(number_of_nodes + 1, 0), reverse_in_order(number_of_nodes + 1, 0), top(number_of_nodes + 1, 0), bottom(number_of_nodes + 1, 0);
    {
        RecursiveLambda([&](const auto& self, int current, int previous) -> void {
            for (int next : adj[current]) {
                adj[next].erase(find(adj[next].begin(), adj[next].end(), current));
                self(next, current);
            }
            })(1, -1);
            RecursiveLambda([&](const auto& self, int current) -> int {
                for (int i = 0; i < adj[current].size(); i++) {
                    int& next = adj[current][i];
                    depth[next] = depth[current] + 1;
                    parent[next] = current;
                    subtree_size[current] += self(next);
                    if (subtree_size[adj[current][0]] < subtree_size[next]) swap(adj[current][0], next);
                }
                return ++subtree_size[current];
                })(1);
                RecursiveLambda([&](const auto& self, int current) -> void {
                    static int order = 0;
                    reverse_in_order[in_order[current] = ++order] = current;
                    for (int next : adj[current]) {
                        top[next] = (next == adj[current][0] ? top[current] : next);
                        self(next);
                    }
                    bottom[current] = adj[current].size() ? bottom[adj[current][0]] : current;
                    })(top[1] = 1);
    }

    SegmentTree<int, plus<int>> updater(number_of_nodes, 0);
    vector<int> color(number_of_nodes + 1, 0);
    auto update_up = [&](int i) {
        const int c = color[in_order[i]];
        while (top[i] != 1 && updater.Query(in_order[top[i]], in_order[i]) == (depth[i] - depth[top[i]] + 1) * c && color[in_order[parent[top[i]]]] == c) i = parent[top[i]];
        int lo = 0, hi = depth[i] - depth[top[i]] + 1;
        while (lo + 1 < hi) {
            const int mid = lo + hi >> 1;
            const int j = reverse_in_order[in_order[i] - mid];
            if (updater.Query(in_order[j], in_order[i]) == (depth[i] - depth[j] + 1) * c) lo = mid;
            else hi = mid;
        }
        return reverse_in_order[in_order[i] - lo];
        };

    SegmentTree<NodeData, FunctionMerge> segment_tree(number_of_nodes, NodeData{ 0, 0, 0, 1 });
    vector<int> attribute(number_of_nodes + 1, 0);
    vector<vector<multiset<int>>> light_edge(number_of_nodes + 1, vector<multiset<int>>(2, multiset<int>{}));
    auto set_up = [&](int i) { segment_tree.Update(i, NodeData{ color[i], 1, *prev(light_edge[i][color[i]].end()), 0 }); };
    auto erase_element = [](auto& S, auto x) { S.erase(S.find(x)); };
    auto insert_element = [](auto& S, auto x) { S.insert(x); };
    for (int i = 1; i <= number_of_nodes; i++) cin >> color[in_order[i]], updater.Update(in_order[i], color[in_order[i]]);
    for (int i = 1; i <= number_of_nodes; i++) cin >> attribute[in_order[i]];
    for (int i = number_of_nodes; i >= 1; i--) {
        const int j = reverse_in_order[i];
        insert_element(light_edge[in_order[j]][color[in_order[j]]], attribute[i]);
        set_up(in_order[j]);
        if (j == top[j] && j != 1) insert_element(light_edge[in_order[parent[j]]][color[in_order[j]]], segment_tree.Query(in_order[j], in_order[bottom[j]]).max_length);
    }

    auto update_data = [&](int i, int x) {
        bool flag = 1;
        auto perform_update = [&]() {
            erase_element(light_edge[in_order[i]][color[in_order[i]]], attribute[in_order[i]]);
            x == -1 ? updater.Update(in_order[i], color[in_order[i]] ^= 1), 1 : attribute[in_order[i]] = x;
            insert_element(light_edge[in_order[i]][color[in_order[i]]], attribute[in_order[i]]);
            };
        while (top[i] != 1) {
            erase_element(light_edge[in_order[parent[top[i]]]][color[in_order[top[i]]]], segment_tree.Query(in_order[top[i]], in_order[bottom[i]]).max_length);
            if (flag) perform_update(), flag = 0; set_up(in_order[i]);
            insert_element(light_edge[in_order[parent[top[i]]]][color[in_order[top[i]]]], segment_tree.Query(in_order[top[i]], in_order[bottom[i]]).max_length);
            i = parent[top[i]];
        }
        if (flag) perform_update(), flag = 0; set_up(in_order[i]);
        };

    auto query_data = [&](int i) {
        i = update_up(i);
        return segment_tree.Query(in_order[i], in_order[bottom[i]]).max_length;
        };

    int queries;
    cin >> queries;
    while (queries--) {
        int type, a, b = -1;
        cin >> type >> a;
        if (type == 3) cin >> b;
        if (type & 1) update_data(a, b);
        else cout << query_data(a) << '\n';
    }
}
