#include <bits/stdc++.h>
using namespace std;

#define first_element first
#define second_element second

long long array_of_numbers[9999999];
long long right_index[999999];
long long left_index[999999];
long long prefix_sum[999999];
stack<pair<long long, long long>> decreasing_stack_1;
stack<pair<long long, long long>> decreasing_stack_2;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    long long number_of_elements;
    cin >> number_of_elements;
    
    for (long long iterator = 1; iterator <= number_of_elements; iterator++) {
        cin >> array_of_numbers[iterator];
        prefix_sum[iterator] = prefix_sum[iterator - 1] + array_of_numbers[iterator];
    }

    for (long long iterator = 1; iterator <= number_of_elements; iterator++) {
        while (decreasing_stack_1.size() && decreasing_stack_1.top().first_element > array_of_numbers[iterator]) {
            long long temp_index = decreasing_stack_1.top().second_element;
            right_index[temp_index] = iterator - 1;
            decreasing_stack_1.pop();
        }
        decreasing_stack_1.push({array_of_numbers[iterator], iterator});
    }

    while (decreasing_stack_1.size()) {
        long long temp_index = decreasing_stack_1.top().second_element;
        right_index[temp_index] = number_of_elements;
        decreasing_stack_1.pop();
    }

    for (long long iterator = number_of_elements; iterator >= 1; iterator--) {
        while (decreasing_stack_2.size() && decreasing_stack_2.top().first_element > array_of_numbers[iterator]) {
            long long temp_index = decreasing_stack_2.top().second_element;
            left_index[temp_index] = iterator + 1;
            decreasing_stack_2.pop();
        }
        decreasing_stack_2.push({array_of_numbers[iterator], iterator});
    }

    while (decreasing_stack_2.size()) {
        long long temp_index = decreasing_stack_2.top().second_element;
        left_index[temp_index] = 1;
        decreasing_stack_2.pop();
    }

    long long maximum_result = 0;
    long long left_bound = 1, right_bound = number_of_elements;
    for (long long iterator = 1; iterator <= number_of_elements; iterator++) {
        long long current_result = (prefix_sum[right_index[iterator]] - prefix_sum[left_index[iterator] - 1]) * array_of_numbers[iterator];
        if (maximum_result < current_result) {
            maximum_result = current_result;
            left_bound = left_index[iterator];
            right_bound = right_index[iterator];
        }
    }

    cout << maximum_result << '\n';
    cout << left_bound << ' ' << right_bound;

    return 0;
}
