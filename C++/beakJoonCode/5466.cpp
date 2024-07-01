#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500009;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> vpi;

vpi market[MAXN];
int n, up_cost, down_cost, start_point;
int up_tree[2 * MAXN], down_tree[2 * MAXN];

int query(int *tree, int left, int right) {
    int answer = -INF;
    for (left += MAXN, right += MAXN; left <= right; left >>= 1, right >>= 1) {
        if (left & 1) {
            answer = max(answer, tree[left++]);
        }
        if (~right & 1) {
            answer = max(answer, tree[right--]);
        }
    }
    return answer;
}

void update(int *tree, int position, int value) {
    position += MAXN;
    tree[position] = max(tree[position], value);
    for (; position > 1; position >>= 1) {
        tree[position >> 1] = max(tree[position], tree[position ^ 1]);
    }
}

void updatePosition(int position, int value) {
    update(up_tree, position, value - up_cost * position);
    update(down_tree, position, value + down_cost * position);
}

int getMaxValue(int position) {
    return max(query(down_tree, 0, position) - down_cost * position, 
               query(up_tree, position, MAXN - 1) + up_cost * position);
}

void processMarket(vpi &market_data) {
    if (market_data.empty()) {
        return;
    }

    sort(market_data.begin(), market_data.end());
    vector<int> U, D;
    int size = market_data.size();

    for (int i = 0; i < size; i++) {
        int temp = getMaxValue(market_data[i].first);
        U.push_back(temp);
        D.push_back(temp);
    }

    for (int i = 0; i < size; i++) {
        if (i != 0) {
            D[i] = max(D[i], D[i - 1] - down_cost * (market_data[i].first - market_data[i - 1].first));
        }
        D[i] += market_data[i].second;
    }

    for (int i = size - 1; i >= 0; i--) {
        if (i != size - 1) {
            U[i] = max(U[i], U[i + 1] - up_cost * (market_data[i + 1].first - market_data[i].first));
        }
        U[i] += market_data[i].second;
    }

    for (int i = 0; i < size; i++) {
        updatePosition(market_data[i].first, max(U[i], D[i]));
    }
}

int main() {
    scanf("%d %d %d %d", &n, &up_cost, &down_cost, &start_point);
    
    for (int i = 0, x, y, z; i < n; i++) {
        scanf("%d %d %d", &x, &y, &z);
        market[x].emplace_back(y, z);
    }

    memset(up_tree, 0xc0, sizeof(up_tree));
    memset(down_tree, 0xc0, sizeof(down_tree));
    updatePosition(start_point, 0);

    for (int i = 1; i <= 500001; i++) {
        processMarket(market[i]);
    }

    printf("%d\n", getMaxValue(start_point));
    return 0;
}
