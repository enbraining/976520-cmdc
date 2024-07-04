#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define IDX(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;

istream& operator >> (istream& input_stream, pair<long long, long long>& point) {
    input_stream >> point.x >> point.y;
    return input_stream;
}

pair<long long, long long> operator + (pair<long long, long long> point1, pair<long long, long long> point2) {
    return { point1.x + point2.x, point1.y + point2.y };
}

pair<long long, long long> operator - (pair<long long, long long> point1, pair<long long, long long> point2) {
    return { point1.x - point2.x, point1.y - point2.y };
}

long long operator * (pair<long long, long long> point1, pair<long long, long long> point2) { // dot product
    return point1.x * point2.x + point1.y * point2.y;
}

long long operator / (pair<long long, long long> point1, pair<long long, long long> point2) { // cross product
    return point1.x * point2.y - point2.x * point1.y;
}

long long compute_cross_product(const pair<long long, long long>& point1, const pair<long long, long long>& point2, const pair<long long, long long>& point3) {
    return (point2 - point1) / (point3 - point2);
}

int compute_ccw(pair<long long, long long> point1, pair<long long, long long> point2, pair<long long, long long> point3) {
    long long result = compute_cross_product(point1, point2, point3);
    return (result > 0) - (result < 0);
}

long long compute_distance_squared(const pair<long long, long long>& point1, const pair<long long, long long>& point2) {
    long long delta_x = point1.x - point2.x, delta_y = point1.y - point2.y;
    return delta_x * delta_x + delta_y * delta_y;
}

inline double compute_hypotenuse(const pair<long long, long long> point) {
    return hypot(point.x, point.y);
}

inline pair<long long, long long> rotate_point(const pair<long long, long long> point) {
    return point.y >= 0 ? pair<long long, long long>(point.y, -point.x) : pair<long long, long long>(-point.y, point.x);
}

int number_of_points, index_array[2020], order_array[2020];
pair<long long, long long> point_array[2020];

struct LineSegment {
    int point1_index, point2_index, rotation_flag; // -1: 90 degree rotation
    pair<long long, long long> start_point, end_point, direction;

    LineSegment(int point1_index, int point2_index, int rotation_flag)
        : point1_index(point1_index), point2_index(point2_index), rotation_flag(rotation_flag),
        start_point(point_array[point1_index]), end_point(point_array[point2_index]) {
        if (start_point > end_point) swap(start_point, end_point);
        if (rotation_flag == 1) direction = end_point - start_point;
        else direction = rotate_point(end_point - start_point);
    }

    bool operator < (const LineSegment& other_line) const {
        long long result = direction / other_line.direction;
        if (result) return result > 0;
        return tie(rotation_flag, start_point, end_point) < tie(other_line.rotation_flag, other_line.start_point, other_line.end_point);
    }
};

inline double compute_triangle_area(const pair<long long, long long>& a, const pair<long long, long long>& b, const pair<long long, long long>& c) {
    return abs(compute_cross_product(a, b, c)) / compute_hypotenuse(a - b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> number_of_points;
    for (int i = 1; i <= number_of_points; i++) cin >> point_array[i];
    sort(point_array + 1, point_array + number_of_points + 1);

    for (int i = 1; i <= number_of_points; i++) order_array[i] = index_array[i] = i;

    vector<LineSegment> line_segments;
    line_segments.reserve(number_of_points * (number_of_points - 1) / 2);
    for (int i = 1; i <= number_of_points; i++) {
        for (int j = i + 1; j <= number_of_points; j++) {
            line_segments.emplace_back(i, j, 1);
            line_segments.emplace_back(i, j, -1);
        }
    }
    sort(all(line_segments));

    double maximum_area = 0;
    for (const auto& line_segment : line_segments) {
        if (line_segment.rotation_flag == 1) {
            int point1 = line_segment.point1_index, point2 = line_segment.point2_index;
            swap(index_array[point1], index_array[point2]);
            swap(order_array[index_array[point1]], order_array[index_array[point2]]);
            point1 = index_array[line_segment.point1_index];
            point2 = index_array[line_segment.point2_index];
            if (point1 > point2) swap(point1, point2);
            if (point1 - 1 >= 1) maximum_area = max(maximum_area, compute_triangle_area(line_segment.start_point, line_segment.end_point, point_array[order_array[point1 - 1]]));
            if (point2 + 1 <= number_of_points) maximum_area = max(maximum_area, compute_triangle_area(line_segment.start_point, line_segment.end_point, point_array[order_array[point2 + 1]]));
        }
        else {
            if (abs(index_array[line_segment.point1_index] - index_array[line_segment.point2_index]) == 1)
                maximum_area = max(maximum_area, compute_hypotenuse(point_array[line_segment.point1_index] - point_array[line_segment.point2_index]));
        }
    }
    cout << fixed << setprecision(10) << maximum_area / 2 << "\n";
}
