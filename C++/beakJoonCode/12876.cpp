#include <bits/stdc++.h>

using namespace std;

const int MAX = 400000;
const int INF = (int)1e9;
const long long LINF = (long long)9e18;

struct LiChaoSegmentTree {
    struct Node {
        Node* left = nullptr, * right = nullptr;
        pair<long long, long long> line;
        Node(pair<long long, long long> line) : line(line) {}
    } *root = nullptr;

    long long calculate(pair<long long, long long> line, long long x) {
        return line.first * x + line.second;
    }

    void add_line(Node* node, pair<long long, long long> new_line, long long start = -INF, long long end = INF + 1) {
        long long mid = (start + end) >> 1;
        bool left_better = calculate(new_line, start) > calculate(node->line, start); // > if max
        bool mid_better = calculate(new_line, mid) > calculate(node->line, mid); // > if max
        if (mid_better) {
            swap(new_line, node->line);
        }
        if (end == start + 1) {
            return;
        }
        if (left_better != mid_better) {
            if (!node->left) {
                node->left = new Node(new_line);
            }
            else {
                add_line(node->left, new_line, start, mid);
            }
        }
        else {
            if (!node->right) {
                node->right = new Node(new_line);
            }
            else {
                add_line(node->right, new_line, mid, end);
            }
        }
    }

    void add(pair<long long, long long> new_line) {
        if (!root) {
            root = new Node(new_line);
        }
        else {
            add_line(root, new_line);
        }
    }

    long long query(Node* node, long long x, long long start = -INF, long long end = INF + 1) { // 시작과 끝
        if (!node) {
            return -LINF; // linf 최대
        }
        long long mid = (start + end) >> 1;
        if (end == start + 1) {
            return calculate(node->line, x);
        }
        if (x < mid) {
            return max(calculate(node->line, x), query(node->left, x, start, mid));
        }
        else {
            return max(calculate(node->line, x), query(node->right, x, mid, end));
        }
    }

    long long query(long long x) {
        if (!root) { //최!!!!!! 대!!!!!!!
            return -LINF;
        }
        return query(root, x);
    }
};

class SegmentTree {
    vector<LiChaoSegmentTree> segment_trees;
    int size;
public:
    void Init(int N) {
        size = N;
        segment_trees.resize(4 * size);
    }

    void update(int left, int right, pair<int, long long> line, int start, int end, int node = 1) {
        if (start > right || end < left) {
            return;
        }
        if (start >= left && end <= right) {
            segment_trees[node].add(line);
            return;
        }
        int mid = (start + end) / 2;
        update(left, right, line, start, mid, node * 2);
        update(left, right, line, mid + 1, end, node * 2 + 1);
    }

    void Update(int left, int right, pair<int, long long> line) {
        update(left, right, line, 1, size);
    }

    long long calculate_max(int k, int x, int start, int end, int node = 1) {
        if (k == 0) {
            return -LINF;
        }
        if (start == end) {
            return segment_trees[node].query(x);
        }
        int mid = (start + end) / 2;
        if (k <= mid) {
            return max(segment_trees[node].query(x), calculate_max(k, x, start, mid, node * 2));
        }
        else {
            return max(segment_trees[node].query(x), calculate_max(k, x, mid + 1, end, node * 2 + 1));
        }
    }

    long long CalculateMax(int k, int x) {
        return calculate_max(k, x, 1, size);
    }
} segment_tree;

pair<int, long long> lines[MAX];
bool active_lines[MAX];
vector<pair<int, int>> points;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    segment_tree.Init(n);

    for (int i = 1; i <= n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> lines[i].first >> lines[i].second;
            active_lines[i] = true;
        }
        if (type == 2) {
            int x;
            cin >> x;
            segment_tree.Update(x, i, lines[x]);
            active_lines[x] = false;
        }
        if (type == 3) {
            int x;
            cin >> x;
            points.emplace_back(i, x);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (active_lines[i]) {
            segment_tree.Update(i, n, lines[i]);
        }
    }

    for (auto& point : points) {
        long long answer = segment_tree.CalculateMax(point.first, point.second);
        if (answer == -LINF) {
            cout << "EMPTY" << '\n';
        }
        else {
            cout << answer << '\n';
        }
    }

    return 0;
}
