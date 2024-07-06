#include <bits/stdc++.h>
using namespace std;

const int MAX = 4000000;

pair<long long, long long> arr1[MAX];
pair<long long, long long> arr2[MAX];
long long bit1[MAX];
long long size1[MAX];
long long bit2[MAX];
long long size2[MAX];

string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    long long n;
    cin >> n;

    long long n1 = n / 2;
    long long n2 = n - n1;

    for (long long i = 0; i < n1; ++i) {
        cin >> s;
        long long mul = 1LL << 40;
        bool all_same = true;
        for (long long j = 0; j < s.size(); ++j) {
            if (j > 0 && s[j] != s[j - 1]) all_same = false;
            if (!all_same) mul /= 2;
            if (s[j] == 'B') bit1[i] += mul;
            else bit1[i] -= mul;
        }
        size1[i] = s.size();
    }

    for (long long i = 0; i < n2; ++i) {
        cin >> s;
        long long mul = 1LL << 40;
        bool all_same = true;
        for (long long j = 0; j < s.size(); ++j) {
            if (j > 0 && s[j] != s[j - 1]) all_same = false;
            if (!all_same) mul /= 2;
            if (s[j] == 'B') bit2[i] += mul;
            else bit2[i] -= mul;
        }
        size2[i] = s.size();
    }

    long long bn1 = (1LL << n1);
    for (long long i = 1; i <= bn1; ++i) {
        long long sum = 0;
        long long length = 0;
        for (long long j = 0; j < n1; ++j) {
            if ((1LL << j) & i) {
                sum += bit1[j];
                length += size1[j];
            }
        }
        arr1[i] = { sum, length };
    }

    long long bn2 = (1LL << n2);
    for (long long i = 1; i <= bn2; ++i) {
        long long sum = 0;
        long long length = 0;
        for (long long j = 0; j < n2; ++j) {
            if ((1LL << j) & i) {
                sum += bit2[j];
                length += size2[j];
            }
        }
        arr2[i] = { sum, length };
    }

    sort(arr1 + 1, arr1 + 1 + bn1);
    sort(arr2 + 1, arr2 + 1 + bn2);

    long long answer = 0;
    for (long long i = 1; i <= bn1; ++i) {
        if (i != bn1 && arr1[i].first == arr1[i + 1].first) continue;
        pair<long long, long long> key = { -arr1[i].first + 1, -1e18 };
        long long idx = lower_bound(arr2 + 1, arr2 + 1 + bn2, key) - arr2 - 1;
        if ((arr1[i].first + arr2[idx].first) == 0) {
            answer = max(answer, arr1[i].second + arr2[idx].second);
        }
    }
    
    cout << answer << "\n";

    return 0;
}
