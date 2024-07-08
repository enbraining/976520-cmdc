#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int, int> Point;
typedef pair<int64, int64> PointLL;

const int MAX_POINTS = 1010;
const int INF = 1e9;
const int64 INF_LL = 9e18;

class RangeMaximumSegmentTree {
    struct Node {
        int left_max = 0, right_max = 0, overall_max = 0;
        bool is_full = false;
        Node operator + (const Node &other) {
            Node result;
            if (is_full)
                result.left_max = left_max + other.left_max;
            else
                result.left_max = left_max;
            if (other.is_full)
                result.right_max = right_max + other.right_max;
            else
                result.right_max = other.right_max;
            if (is_full && other.is_full)
                result.is_full = true;
            result.overall_max = max({overall_max, other.overall_max, right_max + other.left_max});
            return result;
        }
    };
    
    vector<Node> tree;
    int size;

public:
    void Initialize(int n) {
        tree.resize(4 * n + 10);
        size = n;
    }

    void Update(int index, bool is_full) {
        UpdateTree(1, 0, size - 1, index, is_full);
    }

    void UpdateTree(int node, int start, int end, int index, bool is_full) {
        if (start == end) {
            if (is_full)
                tree[node].is_full = true, tree[node].left_max = tree[node].right_max = tree[node].overall_max = 1;
            else
                tree[node].is_full = false, tree[node].left_max = tree[node].right_max = tree[node].overall_max = 0;
            return;
        }
        int mid = start + (end - start) / 2;
        if (index <= mid)
            UpdateTree(node << 1, start, mid, index, is_full);
        else
            UpdateTree(node << 1 | 1, mid + 1, end, index, is_full);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    int GetMaximum() {
        return tree[1].overall_max;
    }
};

struct Coordinate {
    int x, y;
    bool is_red = false;
    bool operator < (const Coordinate &other) const {
        return Point(x, y) < Point(other.x, other.y);
    }
};

struct Event {
    int delta_x, delta_y, index1, index2;
    Event(int dx, int dy, int idx1, int idx2) : delta_x(dx), delta_y(dy), index1(idx1), index2(idx2) {}
    bool operator < (const Event &other) const {
        int64 determinant = 1LL * delta_x * other.delta_y - 1LL * delta_y * other.delta_x;
        if (determinant != 0)
            return determinant > 0;
        return Point(index1, index2) < Point(other.index1, other.index2);
    }
};

int64 ComputeCCW(Event a, Event b) {
    return (int64)a.delta_x * b.delta_y - (int64)b.delta_x * a.delta_y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_points;
    cin >> num_points;

    vector<Coordinate> points(num_points);
    vector<int> position(num_points);

    for (int i = 0; i < num_points; ++i) {
        cin >> points[i].x >> points[i].y;
        string color;
        cin >> color;
        if (color == "R")
            points[i].is_red = true;
    }

    if (num_points == 1) {
        if (points[0].is_red)
            cout << 1 << endl;
        else
            cout << 0 << endl;
        return 0;
    }

    sort(points.begin(), points.end());

    for (int i = 0; i < num_points; ++i) {
        position[i] = i;
    }

    vector<Event> events;
    for (int i = 0; i < num_points; ++i) {
        for (int j = i + 1; j < num_points; ++j) {
            events.emplace_back(points[j].x - points[i].x, points[j].y - points[i].y, i, j);
        }
    }

    sort(events.begin(), events.end());

    int answer = 0;
    RangeMaximumSegmentTree segment_tree;
    segment_tree.Initialize(num_points);

    for (int i = 0; i < num_points; ++i) {
        segment_tree.Update(i, points[i].is_red);
    }

    answer = segment_tree.GetMaximum();

    for (int i = 0; i < events.size(); ++i) {
        int pos1 = position[events[i].index1];
        int pos2 = position[events[i].index2];
        
        swap(points[pos1], points[pos2]);
        swap(position[events[i].index1], position[events[i].index2]);

        segment_tree.Update(pos1, points[pos1].is_red);
        segment_tree.Update(pos2, points[pos2].is_red);

        if (i + 1 < events.size() && ComputeCCW(events[i], events[i + 1]) == 0)
            continue;

        answer = max(answer, segment_tree.GetMaximum());
    }

    cout << answer << endl;

    return 0;
}
