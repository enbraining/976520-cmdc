#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int left_boundaries[1000000];
int right_boundaries[1000000];

int depth_first_search(int start_index, int end_index) {
    if (start_index >= end_index) {
        return 1;
    }
    int i;
    for (i = 0; start_index + i <= end_index - i; i++) {
        if (left_boundaries[start_index + i] <= start_index && right_boundaries[start_index + i] >= end_index) {
            return depth_first_search(start_index, start_index + i - 1) && depth_first_search(start_index + i + 1, end_index);
        }
        if (left_boundaries[end_index - i] <= start_index && right_boundaries[end_index - i] >= end_index) {
            return depth_first_search(start_index, end_index - i - 1) && depth_first_search(end_index - i + 1, end_index);
        }
    }
    return 0;
}

int main() {
    int test_cases;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> test_cases;

    while (test_cases--) {
        int num_elements;
        cin >> num_elements;
        vector<pair<int, int>> elements;

        for (int i = 0; i < num_elements; i++) {
            int element_value;
            cin >> element_value;
            elements.push_back({ element_value, i });
            left_boundaries[i] = 0;
            right_boundaries[i] = num_elements - 1;
        }

        sort(elements.begin(), elements.end());

        for (int i = 1; i < num_elements; i++) {
            if (elements[i].first == elements[i - 1].first) {
                left_boundaries[elements[i].second] = elements[i - 1].second + 1;
                right_boundaries[elements[i - 1].second] = elements[i].second - 1;
            }
        }

        int result = depth_first_search(0, num_elements - 1);
        if (result) {
            cout << "non-boring";
        } else {
            cout << "boring";
        }
        cout << '\n';
    }

    return 0;
}
