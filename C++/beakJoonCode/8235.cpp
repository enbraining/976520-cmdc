#include <bits/stdc++.h>
using namespace std;

int string_length, longest_palindromic_prefix_suffix_length;
string input_string;

const long long prime_base = 917, modulus_value = 993244853;

struct StringHashing {
    vector<long long> hash_values, base_powers;
    StringHashing() { }
    StringHashing(string& s) {
        int n = s.size();
        hash_values.resize(n + 1);
        base_powers.resize(n + 1);
        base_powers[0] = 1, base_powers[1] = prime_base;
        for (int i = n - 1; i >= 0; i--)
            hash_values[i] = (hash_values[i + 1] * prime_base + s[i]) % modulus_value;
        for (int i = 2; i <= n; i++)
            base_powers[i] = base_powers[i - 1] * prime_base % modulus_value;
    }
    int substringHash(int left, int right) {
        long long result = hash_values[left] - hash_values[right + 1] * base_powers[right - left + 1];
        result %= modulus_value;
        result += modulus_value;
        result %= modulus_value;
        return result;
    }
} hash1;

inline int isSameSubstring(int start1, int end1, int start2, int end2) {
    return hash1.substringHash(start1, end1) == hash1.substringHash(start2, end2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> string_length >> input_string;
    input_string = "#" + input_string;
    hash1 = StringHashing(input_string);

    int current_length = 0;
    for (int i = string_length / 2; i > 0; i--) {
        current_length = min(string_length / 2 - i, current_length + 2);
        if (!isSameSubstring(1, i, string_length - i + 1, string_length))
            continue;
        longest_palindromic_prefix_suffix_length = max(longest_palindromic_prefix_suffix_length, i);
        while (current_length >= 0 && !isSameSubstring(i + 1, i + current_length, string_length - i + 1 - current_length, string_length - i))
            current_length--;
        longest_palindromic_prefix_suffix_length = max(longest_palindromic_prefix_suffix_length, i + current_length);
    }
    cout << longest_palindromic_prefix_suffix_length;
}
