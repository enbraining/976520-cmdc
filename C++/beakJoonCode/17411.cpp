#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MOD 1000000007

int number_of_elements, length_of_LIS;
int input_array[1000001], dp_LIS_length[1000001], LIS_array[1000001];
vector<long long> elements_in_LIS_length[1000001], cumulative_sum[1000001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> number_of_elements;
    for (int i = 0; i < number_of_elements; i++) {
        cin >> input_array[i];
    }

    for (int i = 0; i < number_of_elements; i++) {
        int insert_position = lower_bound(LIS_array, LIS_array + length_of_LIS, input_array[i]) - LIS_array;
        LIS_array[insert_position] = input_array[i];
        dp_LIS_length[i] = insert_position + 1;
        length_of_LIS = max(length_of_LIS, dp_LIS_length[i]);
    }

    cout << length_of_LIS << " ";

    for (int i = 1; i <= length_of_LIS; i++) {
        cumulative_sum[i].push_back(0); 
    }

    for (int i = number_of_elements - 1; i >= 0; i--) {
        int current_LIS_contribution = 1;
        int current_LIS_length = dp_LIS_length[i];

        if (current_LIS_length < length_of_LIS) {
            int index_in_next_LIS_length = upper_bound(elements_in_LIS_length[current_LIS_length + 1].begin(), elements_in_LIS_length[current_LIS_length + 1].end(), input_array[i]) - elements_in_LIS_length[current_LIS_length + 1].begin();
            current_LIS_contribution = cumulative_sum[current_LIS_length + 1].back() - cumulative_sum[current_LIS_length + 1][index_in_next_LIS_length];
        }
        elements_in_LIS_length[current_LIS_length].push_back(input_array[i]);
        cumulative_sum[current_LIS_length].push_back((current_LIS_contribution + cumulative_sum[current_LIS_length].back()) % MOD);
    }
    
    cout << (cumulative_sum[1].back() + MOD) % MOD << '\n';
}
