#include<bits/stdc++.h>
#define r ll n, ll s, ll e
#define ll long long
#define N 100001
using namespace std;

struct T { ll ls, rs, ps, ms; }seg[1 << 18];
vector <int> Gr[N], G[N];
int top[N], in[N], lz[1 << 18];
int P[N], D[N], S[N], C[N];
ll n, q, i, j, M(-1e9);

T f(T x, T y) { return { max(x.ls, x.ps + y.ls), max(y.rs, y.ps + x.rs), x.ps + y.ps, max({x.ms, y.ms, x.rs + y.ls}) }; }

void 입력() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    fill(lz, lz + (1 << 18), M); seg[n] = { M, M, 0, M };
    for (cin >> n; ++i <= n; cin >> C[i]);
    for (int o{}; o++ < n - 1;)
        cin >> i >> j, Gr[i].push_back(j), Gr[j].push_back(i);
}

void hld_트리_초기화_dfs(int p)  
{
    S[p] = 1;
    for (int& i : Gr[p])
        if (!S[i])
        {
            D[i] = D[p] + 1;
            P[i] = p;
            hld_트리_초기화_dfs(i);
            S[p] += S[i];
            G[p].push_back(i);
            if (S[i] > S[G[p][0]]) swap(G[p][0], G[p].back());
        }
}

void hld_트리_초기화_dfs2(int p) {
    in[p] = ++q;
    for (int& i : G[p])
        top[i] = i == G[p][0] ? top[p] : i, hld_트리_초기화_dfs2(i);
}

void lazy_업데이트(r) {
    if (lz[n] == M) return;
    if (s ^ e) lz[n << 1] = lz[n << 1 | 1] = lz[n];
    seg[n].ps = lz[n] * (e - s + 1);
    seg[n].ls = seg[n].rs = seg[n].ms = max(0LL, seg[n].ps);
    lz[n] = M;
}

T seg_업데이트(r, ll p, ll q, ll k) {
    lazy_업데이트(n, s, e);
    if (s > q || e < p) return seg[n];
    if (s >= p && e <= q) return (lz[n] = k, lazy_업데이트(n, s, e)), seg[n];
    T L(seg_업데이트(n << 1, s, (s + e) >> 1, p, q, k)), R(seg_업데이트(n << 1 | 1, ((s + e) >> 1) + 1, e, p, q, k));
    return seg[n] = f(L, R);
}

T seg_쿼리(r, ll p, ll q) {
    lazy_업데이트(n, s, e);
    if (s > q || e < p) return seg[0];
    if (s >= p && e <= q) return seg[n];
    T L(seg_쿼리(n << 1, s, (s + e) >> 1, p, q)), R(seg_쿼리(n << 1 | 1, ((s + e) >> 1) + 1, e, p, q));
    return f(L, R);
}

void hld_업데이트_쿼리(ll x, ll y, ll w) {
    while (top[x] ^ top[y]) {
        if (D[top[x]] < D[top[y]]) swap(x, y);
        seg_업데이트(1, 1, n, in[top[x]], in[x], w);
        x = P[top[x]];
    }
    if (D[x] > D[y]) swap(x, y);
    seg_업데이트(1, 1, n, in[x], in[y], w);
}

ll hld_가져오기_쿼리(ll x, ll y) {
    T p(seg[0]), q(seg[0]);
    while (top[x] ^ top[y])
        D[top[x]] > D[top[y]] ? p = f(seg_쿼리(1, 1, n, in[top[x]], in[x]), p), x = P[top[x]] : (q = f(seg_쿼리(1, 1, n, in[top[y]], in[y]), q), y = P[top[y]]);
    if (D[x] > D[y]) swap(x, y), swap(p, q);
    swap(p.ls, p.rs);
    return f(p, f(seg_쿼리(1, 1, n, in[x], in[y]), q)).ms;
}

void sv() {
    for (cin >> q, i = 1; i <= n; i++) hld_업데이트_쿼리(i, i, C[i]);
    for (ll o, w; q--;)
        if (cin >> o >> i >> j; o & 1) cout << hld_가져오기_쿼리(i, j) << '\n';
        else cin >> w, hld_업데이트_쿼리(i, j, w);
}

int main() {
    입력();
    hld_트리_초기화_dfs(1); hld_트리_초기화_dfs2(1);
    sv();
}
