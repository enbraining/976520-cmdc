#define private public
#include <bitset>
#undef private

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

#ifdef LOCAL
constexpr bool local = true;
#else
constexpr bool local = false;
#endif


template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw>& A, const _Base_bitset<_Nw>& B) {
	for (int i = 0, c = 0; i < _Nw; i++)
		c = _subborrow_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*) & A._M_w[i]);
}
template<> void _M_do_sub(_Base_bitset<1>& A, const _Base_bitset<1>& B) {
	A._M_w -= B._M_w;
}
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb>& A, const bitset<_Nb>& B) {
	_M_do_sub(A, B);
	return A;
}
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb>& A, const bitset<_Nb>& B) {
	bitset<_Nb> C(A);
	return C -= B;
}

string a, b;
string result;

template<size_t sz>
vector<int> _LCS(string a, string b) {
	bitset<sz> Match[26], x, B;
	for (int i = 0; i < b.length(); i++) {
		Match[b[i] - 65][i] = 1;
	}
	for (int i = 0; i < a.length(); i++) {
		x = Match[a[i] - 65] | B; B <<= 1; B |= 1;
		B = x ^ (x & (x - B));
	}

	vector<int> ans(b.length() + 2);
	for (int i = 0; i < b.length(); i++) {
		ans[i + 1] = ans[i] + B[i];
	}
	return ans;
}

vector<int> LCS(string a, string b) {
	if (b.length() + 5 < 100) return _LCS<200>(a, b);
	if (b.length() + 5 < 500) return _LCS<1000>(a, b);
	if (b.length() + 5 < 1000) return _LCS<2000>(a, b);
	if (b.length() + 5 < 5000) return _LCS<10000>(a, b);
	if (b.length() + 5 < 10000) return _LCS<20000>(a, b);
	return _LCS<50005>(a, b);
}

void solve(int s1, int e1, int s2, int e2) {
	if (s1 == e1) {
		for (int i = s2; i <= e2; i++) {
			if (a[s1] == b[i]) {
				result += a[s1];
				break;
			}
		}
		return;
	}

	int mid = (s1 + e1) / 2;
	string upside = a.substr(s1, mid - s1 + 1);
	string downside = a.substr(mid + 1, e1 - mid);

	string brange = b.substr(s2, e2 - s2 + 1);

	vector<int> upper = LCS(upside, brange);

	reverse(downside.begin(), downside.end());
	reverse(brange.begin(), brange.end());

	vector<int> lower = LCS(downside, brange);
	reverse(lower.begin(), lower.end());


	int mxv = -1; int idx = 0;
	for (int i = s2 - 1; i <= e2; i++) {
		if (mxv <= upper[i - s2 + 1] + lower[i - s2 + 2]) {
			mxv = upper[i - s2 + 1] + lower[i - s2 + 2];
			idx = i;
		}
	}

	solve(s1, mid, s2, idx);
	solve(mid + 1, e1, idx + 1, e2);

}

int main() {
	ios_base::sync_with_stdio;
	cin.tie(nullptr);
	cout.tie(nullptr);;
	cin >> a >> b;

	solve(0, a.length() - 1, 0, b.length() - 1);
	cout << result.length() << '\n' << result;
}
