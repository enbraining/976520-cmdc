#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

const int directionI[] = { 1, -1, 0, 0 };
const int directionJ[] = { 0, 0, 1, -1 };

int numRows, numCols, startI, startJ;
char grid[55][55];
vector<pair<int, int>> stars;
int moveTo[3030][2];

inline int getId(int i, int j) {
    return i * 50 + j;
}

struct Graph {
    vector<int> adj[6060], reverseAdj[6060], dfsOrder;
    int visited[6060], componentCounter;

    int invert(int x) {
        return x < 3030 ? x + 3030 : x - 3030;
    }

    void addEdge(int from, int to) {
        adj[from].push_back(to);
        reverseAdj[to].push_back(from);
    }

    void addCNF(int x, int y) {
        addEdge(invert(x), y);
        addEdge(invert(y), x);
    }

    void dfs(int node) {
        visited[node] = 1;
        for (auto neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
        dfsOrder.push_back(node);
    }

    void reverseDfs(int node, int color) {
        visited[node] = color;
        for (auto neighbor : reverseAdj[node]) {
            if (!visited[neighbor]) {
                reverseDfs(neighbor, color);
            }
        }
    }

    int getStronglyConnectedComponents(const vector<int>& vertices) {
        for (auto vertex : vertices) {
            if (!visited[vertex]) {
                dfs(vertex);
            }
        }

        reverse(all(dfsOrder));
        memset(visited, 0, sizeof(visited));

        for (auto vertex : dfsOrder) {
            if (!visited[vertex]) {
                reverseDfs(vertex, ++componentCounter);
            }
        }
        return componentCounter;
    }

    vector<pair<int, int>> getDAG() {
        vector<pair<int, int>> edges;
        for (int i = 1; i <= numRows; i++) {
            for (int j = 1; j <= numCols; j++) {
                if (grid[i][j] != '#') {
                    int currentNode = getId(i, j);
                    for (auto neighbor : adj[currentNode]) {
                        if (visited[currentNode] != visited[neighbor]) {
                            edges.emplace_back(visited[currentNode], visited[neighbor]);
                        }
                    }
                }
            }
        }
        compress(edges);
        return move(edges);
    }

    int solveTwoSAT() {
        for (int i = 1; i < 3030; i++) {
            if (visited[i] && visited[i + 3030]) {
                if (visited[i] == visited[i + 3030]) {
                    return 0;
                }
            }
        }
        return 1;
    }
} graph, dag, twoSAT;

int reachable[6060][6060];

void bfs(int startNode) {
    queue<int> q;
    q.push(startNode);
    reachable[startNode][startNode] = 1;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        for (auto neighbor : dag.adj[currentNode]) {
            if (!reachable[startNode][neighbor]) {
                reachable[startNode][neighbor] = 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> numRows >> numCols;
    vector<int> vertices;

    for (int i = 1; i <= numRows; i++) {
        for (int j = 1; j <= numCols; j++) {
            cin >> grid[i][j];
            if (grid[i][j] != '#') {
                vertices.push_back(getId(i, j));
            }
            if (grid[i][j] == 'O') {
                startI = i;
                startJ = j;
            }
            if (grid[i][j] == '*') {
                stars.emplace_back(i, j);
            }
        }
    }

    for (int i = 1; i <= numRows; i++) {
        for (int j = 1; j <= numCols; j++) {
            if (grid[i][j] != '#') {
                int currentNode = getId(i, j);
                for (int k = 0; k < 4; k++) {
                    int ii = i, jj = j;
                    while (1 <= ii && ii <= numRows && 1 <= jj && jj <= numCols && grid[ii][jj] != '#') {
                        ii += directionI[k];
                        jj += directionJ[k];
                    }
                    int nextNode = getId(ii - directionI[k], jj - directionJ[k]);
                    graph.addEdge(currentNode, nextNode);
                    moveTo[currentNode][k / 2] = nextNode;
                }
            }
        }
    }

    int sccCount = graph.getStronglyConnectedComponents(vertices);
    auto compressedEdges = graph.getDAG();
    for (auto edge : compressedEdges) {
        dag.addEdge(edge.x, edge.y);
    }

    for (int i = 1; i <= sccCount; i++) {
        bfs(i);
    }

    int startComponent = graph.visited[getId(startI, startJ)];
    twoSAT.addCNF(startComponent, startComponent);

    for (int i = 1; i <= sccCount; i++) {
        if (!reachable[startComponent][i]) {
            twoSAT.addCNF(i + 3030, i + 3030);
            continue;
        }
        for (int j = 1; j <= sccCount; j++) {
            if (!reachable[i][j] && !reachable[j][i]) {
                twoSAT.addCNF(i + 3030, j + 3030);
            }
        }
    }

    for (auto star : stars) {
        int verticalMove = moveTo[getId(star.x, star.y)][0];
        int horizontalMove = moveTo[getId(star.x, star.y)][1];
        twoSAT.addCNF(graph.visited[verticalMove], graph.visited[horizontalMove]);
    }

    vertices.clear();
    for (int i = 1; i <= sccCount; i++) {
        vertices.push_back(i);
        vertices.push_back(i + 3030);
    }

    twoSAT.getStronglyConnectedComponents(vertices);
    if (twoSAT.solveTwoSAT()) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
