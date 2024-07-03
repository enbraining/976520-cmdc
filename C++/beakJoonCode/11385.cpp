#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define xx first
#define yy second

void fft(vector<complex<long double>> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j >= bit; bit >>= 1) {
            j -= bit;
        }
        j += bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        long double ang = 2 * M_PI / len * (invert ? -1 : 1);
        complex<long double> wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<long double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<long double> u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

void multiplyPolynomials(const vector<ll> &a, const vector<ll> &b, vector<ll> &result) {
    vector<complex<long double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max((int)a.size(), (int)b.size())) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);
    result.resize(n);
    for (int i = 0; i < n; i++) {
        result[i] = ll(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
    }
}

const int MAX_SIZE = 2097152;
int polynomialDegreeA, polynomialDegreeB;
ll finalResult = 0;
vector<ll> coefficientsA, coefficientsB;
vector<ll> lowBitsA, lowBitsB, highBitsA, highBitsB;
vector<ll> result11, result12, result21, result22;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> polynomialDegreeA >> polynomialDegreeB;
    coefficientsA = vector<ll>(MAX_SIZE, 0);
    coefficientsB = vector<ll>(MAX_SIZE, 0);
    for (int i = 0; i <= polynomialDegreeA; ++i) {
        cin >> coefficientsA[i];
    }
    for (int i = 0; i <= polynomialDegreeB; ++i) {
        cin >> coefficientsB[i];
    }

    lowBitsA = coefficientsA;
    lowBitsB = coefficientsB;
    for (auto &val : lowBitsA) {
        val &= ((1 << 10) - 1);
    }
    for (auto &val : lowBitsB) {
        val &= ((1 << 10) - 1);
    }
    multiplyPolynomials(lowBitsA, lowBitsB, result22);

    highBitsA = coefficientsA;
    lowBitsB = coefficientsB;
    for (auto &val : highBitsA) {
        val >>= 10;
    }
    for (auto &val : lowBitsB) {
        val &= ((1 << 10) - 1);
    }
    multiplyPolynomials(highBitsA, lowBitsB, result12);

    lowBitsA = coefficientsA;
    highBitsB = coefficientsB;
    for (auto &val : lowBitsA) {
        val &= ((1 << 10) - 1);
    }
    for (auto &val : highBitsB) {
        val >>= 10;
    }
    multiplyPolynomials(lowBitsA, highBitsB, result21);

    highBitsA = coefficientsA;
    highBitsB = coefficientsB;
    for (auto &val : highBitsA) {
        val >>= 10;
    }
    for (auto &val : highBitsB) {
        val >>= 10;
    }
    multiplyPolynomials(highBitsA, highBitsB, result11);

    for (int i = 0; i <= polynomialDegreeA + polynomialDegreeB; ++i) {
        finalResult ^= (result11[i] << 20) + ((result21[i] + result12[i]) << 10) + result22[i];
    }
    cout << finalResult;

    return 0;
}
