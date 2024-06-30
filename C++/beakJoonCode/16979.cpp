#include <bits/stdc++.h>
using namespace std;

struct Query {
	long long query_index, start_index, end_index, hilbert_value;
	bool operator < (const Query& other_query) const { return hilbert_value < other_query.hilbert_value; }
};

long long convertToHilbertCurve(int x, int y, int pow, int rotation) {
	if (!pow) return 0;
	int half_power = 1 << (pow - 1);
	int segment = (x < half_power) ? ((y < half_power) ? 0 : 3) : ((y < half_power) ? 1 : 2);
	segment = (segment + rotation) & 3;
	const int rotation_delta[4] = { 3, 0, 0, 1 };
	int new_x = x & (x ^ half_power), new_y = y & (y ^ half_power);
	int new_rotation = (rotation + rotation_delta[segment]) & 3;
	long long sub_square_size = (long long)1 << (2 * pow - 2);
	long long result = segment * sub_square_size;
	long long addition = convertToHilbertCurve(new_x, new_y, pow - 1, new_rotation);
	result += (segment == 1 || segment == 2) ? addition : (sub_square_size - addition - 1);
	return result;
}

template<size_t size>
struct FenwickTree {
	vector<int> tree;
	FenwickTree() : tree(size + 1) {}
	void update(int index, int value) {
		for (; index <= size; index += index & -index) tree[index] += value;
	}
	int query(int index) {
		int result = 0;
		for (; index; index -= index & -index) result += tree[index];
		return result;
	}
};

FenwickTree<100000> fenwick_tree;

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);;
	int number_of_elements, number_of_queries; 
	cin >> number_of_elements >> number_of_queries;

	vector<int> elements(number_of_elements);
	for (int i = 0; i < number_of_elements; i++) cin >> elements[i];
	
	auto sorted_elements = elements;
	sort(sorted_elements.begin(), sorted_elements.end());
	sorted_elements.erase(unique(sorted_elements.begin(), sorted_elements.end()), sorted_elements.end());
	
	for (auto& element : elements) 
		element = lower_bound(sorted_elements.begin(), sorted_elements.end(), element) - sorted_elements.begin() + 1;

	vector<Query> queries(number_of_queries);
	for (int i = 0; i < number_of_queries; i++) {
		int start_index, end_index; 
		cin >> start_index >> end_index; 
		--start_index, --end_index;
		queries[i] = { i, start_index, end_index, convertToHilbertCurve(start_index, end_index, 17, 0) };
	}
	sort(queries.begin(), queries.end());

	vector<long long> results(number_of_queries);
	long long current_result = 0;
	int current_start = queries[0].start_index, current_end = current_start - 1;
	
	for (int i = 0; i < number_of_queries; i++) {
		while (queries[i].start_index < current_start) {
			current_result += fenwick_tree.query(elements[--current_start] - 1);
			fenwick_tree.update(elements[current_start], 1);
		}
		while (queries[i].start_index > current_start) {
			fenwick_tree.update(elements[current_start], -1);
			current_result -= fenwick_tree.query(elements[current_start++] - 1);
		}
		while (queries[i].end_index > current_end) {
			current_result += fenwick_tree.query(100000) - fenwick_tree.query(elements[++current_end]);
			fenwick_tree.update(elements[current_end], 1);
		}
		while (queries[i].end_index < current_end) {
			fenwick_tree.update(elements[current_end], -1);
			current_result -= fenwick_tree.query(100000) - fenwick_tree.query(elements[current_end--]);
		}
		results[queries[i].query_index] = current_result;
	}
	for (auto result : results) cout << result << '\n';
}
