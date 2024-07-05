#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<double> cpx;

vector<int> primes;
bool is_prime[101010];

void sieve(int n = 100000) {
    memset(is_prime, 1, sizeof is_prime);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
        for (auto j : primes) {
            if (i * j > n) break;
            is_prime[i * j] = false;
            if (i % j == 0) break;
        }
    }
}

void fft(vector<cpx> &a, bool inverse) {
    int n = a.size(), j = 0;
    vector<cpx> roots(n / 2);
    for (int i = 1; i < n; i++) {
        int bit = (n >> 1);
        while (j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    double angle = 2 * acos(-1) / n * (inverse ? -1 : 1);
    for (int i = 0; i < n / 2; i++) roots[i] = cpx(cos(angle * i), sin(angle * i));
    for (int i = 2; i <= n; i <<= 1) {
        int step = n / i;
        for (int j = 0; j < n; j += i) {
            for (int k = 0; k < i / 2; k++) {
                cpx u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
                a[j + k] = u + v;
                a[j + k + i / 2] = u - v;
            }
        }
    }
    if (inverse) for (int i = 0; i < n; i++) a[i] /= n;
}

vector<ll> polynomial_multiply(vector<ll> &v, vector<ll> &w) {
    vector<cpx> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 2; 
    while (n < v.size() + w.size()) n <<= 1;
    fv.resize(n); 
    fw.resize(n);
    fft(fv, false); 
    fft(fw, false);
    for (int i = 0; i < n; i++) fv[i] *= fw[i];
    fft(fv, true);
    vector<ll> result(n);
    for (int i = 0; i < n; i++) result[i] = (ll)round(fv[i].real());
    return result;
}

ll nodes;
vector<int> adj[101010];
int subtree_size[101010], used[101010];
ll count_subtree[101010];

int get_subtree_size(int v, int parent) {
    subtree_size[v] = 1;
    for (auto i : adj[v]) {
        if (i != parent && !used[i]) {
            subtree_size[v] += get_subtree_size(i, v);
        }
    }
    return subtree_size[v];
}

int get_centroid(int v, int parent, int total_size) {
    for (auto i : adj[v]) {
        if (i != parent && !used[i]) {
            if (subtree_size[i] > total_size / 2) {
                return get_centroid(i, v, total_size);
            }
        }
    }
    return v;
}

vector<ll> current_subtree, accumulated;
int subtree_depth;

void update_subtree(int v, int parent, int depth) {
    subtree_depth = max(subtree_depth, depth);
    current_subtree[depth]++;
    for (auto i : adj[v]) {
        if (i != parent && !used[i]) {
            update_subtree(i, v, depth + 1);
        }
    }
}

void calculate_polynomial() {
    auto product = polynomial_multiply(current_subtree, accumulated);
    for (int i = 1; i < product.size(); i++) {
        count_subtree[i] += product[i];
    }
}

void decompose_tree(int v) {
    int centroid = get_centroid(v, -1, get_subtree_size(v, -1));
    get_subtree_size(centroid, -1);
    used[centroid] = 1;
    accumulated.resize(1);
    accumulated.reserve(subtree_size[centroid] + 1);
    accumulated[0] = 1;
    sort(adj[centroid].begin(), adj[centroid].end(), [&](int a, int b) {
        return subtree_size[a] < subtree_size[b];
    });

    for (auto i : adj[centroid]) {
        if (!used[i]) {
            subtree_depth = 0; 
            current_subtree.clear(); 
            current_subtree.resize(subtree_size[i] + 1);
            update_subtree(i, centroid, 1);
            calculate_polynomial();
            if (accumulated.size() <= subtree_depth) accumulated.resize(subtree_depth + 1);
            for (int j = 0; j <= subtree_depth; j++) accumulated[j] += current_subtree[j];
        }
    }

    for (auto i : adj[centroid]) {
        if (!used[i]) decompose_tree(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    cin >> nodes;
    for (int i = 1; i < nodes; i++) {
        int start, end; 
        cin >> start >> end;
        adj[start].push_back(end);
        adj[end].push_back(start);
    }
    decompose_tree(1);
    sieve();
    ll total_sum = 0;
    for (auto i : primes) total_sum += count_subtree[i];
    cout << fixed; 
    cout.precision(10);
    cout << 1.0 * total_sum / (nodes * (nodes - 1) / 2);
    return 0;
}
