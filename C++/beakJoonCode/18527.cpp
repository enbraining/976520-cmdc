#include <bits/stdc++.h>
using namespace std;

const long long MODULUS = 998244353; //모듈로 연산 상수
long long numberOfElements, initialValue; 

long long modularExponentiation(long long base, long long exponent) {
    long long result = 1;
    while (exponent) {
        if (exponent & 1) {
            result = result * base % MODULUS;
        }
        exponent >>= 1;
        base = base * base % MODULUS;
    }
    return result;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> numberOfElements >> initialValue;
    initialValue++;  

    vector<long long> elementValues(numberOfElements);
    for (long long& value : elementValues) {
        cin >> value;
    }

    long long result = 1;
    for (int index = numberOfElements - 1; index >= 0; --index) {
        initialValue -= elementValues[index] - 1;
        result *= initialValue;
        result %= MODULUS;
    }

    result *= initialValue - numberOfElements;
    result %= MODULUS;
    result *= modularExponentiation(initialValue, MODULUS - 2);
    result %= MODULUS;

    cout << result << '\n';
    return 0;
}
