#include <bits/stdc++.h>
using namespace std;

struct Info {
    set<pair<int, int>> coordinate_set;
    bool operator < (const pair<int, int>& coordinate_pair) const {
        auto iterator = coordinate_set.lower_bound(coordinate_pair);
        return iterator != coordinate_set.begin() && (--iterator)->second < coordinate_pair.second;
    }
    void add_coordinate_pair(const pair<int, int>& coordinate_pair) {
        auto iterator = ++coordinate_set.insert(coordinate_pair).first;
        while (iterator != coordinate_set.end() && coordinate_pair.second < iterator->second) 
            iterator = coordinate_set.erase(iterator);
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    int dimension_m, dimension_n; 
    cin >> dimension_m >> dimension_n;

    if (dimension_m == 2) {
        vector<pair<int, int>> coordinate_vector(dimension_n);
        for (int index = 0; index < dimension_n; ++index) 
            cin >> coordinate_vector[index].first;
        for (int index = 0; index < dimension_n; ++index) 
            cin >> coordinate_vector[index].second;
        sort(coordinate_vector.begin(), coordinate_vector.end());
        
        vector<int> longest_increasing_subsequence;
        for (auto [coordinate_x, coordinate_y] : coordinate_vector) {
            if (longest_increasing_subsequence.empty() || longest_increasing_subsequence.back() < coordinate_y) 
                longest_increasing_subsequence.push_back(coordinate_y);
            else 
                *lower_bound(longest_increasing_subsequence.begin(), longest_increasing_subsequence.end(), coordinate_y) = coordinate_y;
        }
        cout << longest_increasing_subsequence.size() << '\n';
    } else {
        vector<pair<int, pair<int, int>>> coordinate_vector(dimension_n);
        for (int index = 0; index < dimension_n; ++index) 
            cin >> coordinate_vector[index].first;
        for (int index = 0; index < dimension_n; ++index) 
            cin >> coordinate_vector[index].second.first;
        for (int index = 0; index < dimension_n; ++index) 
            cin >> coordinate_vector[index].second.second;
        sort(coordinate_vector.begin(), coordinate_vector.end());
        
        vector<Info> longest_increasing_subsequence;
        for (auto [coordinate_x, coordinate_yz] : coordinate_vector) {
            if (longest_increasing_subsequence.empty() || longest_increasing_subsequence.back() < coordinate_yz) 
                longest_increasing_subsequence.push_back({{ coordinate_yz }});
            else 
                lower_bound(longest_increasing_subsequence.begin(), longest_increasing_subsequence.end(), coordinate_yz)->add_coordinate_pair(coordinate_yz);
        }
        cout << longest_increasing_subsequence.size() << '\n';
    }
}
