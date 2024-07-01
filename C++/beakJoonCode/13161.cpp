#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 555;
int capacity[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];
vector<int> graph[MAX_N];
int level[MAX_N], work[MAX_N], visited[MAX_N];
int n, source = 501, sink = 502;

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(source);
    level[source] = 0;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (auto next : graph[current]) {
            if (level[next] == -1 && capacity[current][next] - flow[current][next] > 0) {
                level[next] = level[current] + 1;
                q.push(next);
            }
        }
    }
    return level[sink] != -1;
}

int dfs(int current, int current_flow) {
    if (current == sink) return current_flow;
    for (int &i = work[current]; i < graph[current].size(); i++) {
        int next = graph[current][i];
        if (level[next] == level[current] + 1 && capacity[current][next] - flow[current][next] > 0) {
            int flow_through_edge = dfs(next, min(current_flow, capacity[current][next] - flow[current][next]));
            if (flow_through_edge > 0) {
                flow[current][next] += flow_through_edge;
                flow[next][current] -= flow_through_edge;
                return flow_through_edge;
            }
        }
    }
    return 0;
}

void decompose() {
    queue<int> q;
    q.push(source);
    visited[source] = 1;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (auto next : graph[current]) {
            if (!visited[next] && capacity[current][next] - flow[current][next] > 0) {
                visited[next] = 1;
                q.push(next);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x == 1) {
            capacity[source][i] = 1e9 + 7;
            graph[source].push_back(i);
            graph[i].push_back(source);
        }
        if (x == 2) {
            capacity[i][sink] = 1e9 + 7;
            graph[i].push_back(sink);
            graph[sink].push_back(i);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> capacity[i][j];
            if (i != j) {
                graph[i].push_back(j);
            }
        }
    }

    int max_flow = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (1) {
            int flow_added = dfs(source, 1e9 + 7);
            if (!flow_added) break;
            max_flow += flow_added;
        }
    }
    
    cout << max_flow << "\n";

    decompose();
    vector<int> set_a, set_b;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            set_a.push_back(i);
        } else {
            set_b.push_back(i);
        }
    }
    
    for (auto i : set_a) {
        cout << i << " ";
    }
    cout << "\n";
    
    for (auto i : set_b) {
        cout << i << " ";
    }
    cout << "\n";

    return 0;
}
