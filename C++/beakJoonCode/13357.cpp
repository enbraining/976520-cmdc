#include<iostream>
#include<algorithm>
using namespace std;

struct ST {
    long long rmax, lmax, total_max, sum;

    ST() {}
    ST(long long _v) {
        rmax = lmax = total_max = _v;
        sum = 0;
    }
}tree[1 << 18];

int N, M, x1, x2, y1, y2, a, tree_size = 1;

void buildST() {
    for (int i = tree_size - 1; i >= 1; --i)
    {
        int l = i << 1;
        int r = l | 1;

        tree[i].lmax = max(tree[l].lmax, tree[l].sum + tree[r].lmax);
        tree[i].rmax = max(tree[r].rmax, tree[l].rmax + tree[r].sum);
        tree[i].total_max = max(tree[l].total_max, max(tree[r].total_max, tree[l].rmax + tree[r].lmax));
        tree[i].sum = tree[l].sum + tree[r].sum;
    }
}

ST getMax(int l, int r) {
    ST sub_l(-1e11), sub_r(-1e11);
    l += tree_size, r += tree_size;

    while (l <= r) {
        if (l & 1) {
            sub_l.total_max = max(sub_l.total_max, max(tree[l].total_max, sub_l.rmax + tree[l].lmax));
            sub_l.lmax = max(sub_l.lmax, sub_l.sum + tree[l].lmax);
            sub_l.rmax = max(tree[l].rmax, sub_l.rmax + tree[l].sum);
            sub_l.sum += tree[l].sum;
            l++;
        }
        if (~r & 1) {
            sub_r.total_max = max(sub_r.total_max, max(tree[r].total_max, tree[r].rmax + sub_r.lmax));
            sub_r.lmax = max(tree[r].lmax, tree[r].sum + sub_r.lmax);
            sub_r.rmax = max(sub_r.rmax, tree[r].rmax + sub_r.sum);
            sub_r.sum += tree[r].sum;
            r--;
        }
        l >>= 1, r >>= 1;
    }

    sub_l.total_max = max(sub_l.total_max, max(sub_r.total_max, sub_l.rmax + sub_r.lmax));
    sub_l.lmax = max(sub_l.lmax, sub_l.sum + sub_r.lmax);
    sub_l.rmax = max(sub_r.rmax, sub_l.rmax + sub_r.sum);
    sub_l.sum += sub_r.sum;

    return sub_l;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    while (tree_size < N) tree_size <<= 1;
    for (int i = tree_size, cnt = 1; i < N + tree_size; ++i, ++cnt) {
        cin >> a;
        tree[i].rmax = tree[i].lmax = tree[i].total_max = tree[i].sum = a;
    }
    buildST();

    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 < x2) {
            ST left = getMax(x1 - 1, y1 - 1);
            ST mid = getMax(y1, x2 - 2);
            ST right = getMax(x2 - 1, y2 - 1);
            cout << left.rmax + mid.sum + right.lmax << "\n";
        }
        else {
            ST left = getMax(x1 - 1, x2 - 2);
            ST mid = getMax(x2 - 1, y1 - 1);
            ST right = getMax(y1, y2 - 1);

            long long ans1 = left.rmax, ans2 = mid.total_max, ans3 = right.lmax, ans4;
            ans1 += mid.lmax;
            ans3 += mid.rmax;
            ans4 = left.rmax + mid.sum + right.lmax;
            cout << max(max(ans1, ans2), max(ans3, ans4)) << "\n";
        }
    }
    return 0;
}
