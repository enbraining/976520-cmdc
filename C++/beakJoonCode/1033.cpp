#include <iostream>
#include <vector>

using namespace std;

struct 매트릭스 {
    int 값 = 1;
    vector<int> 연결;
} 배열[11];

int 방문 = 0;

int 최대공약수(int a, int b) {
    return b ? 최대공약수(b, a % b) : a;
}

void 갱신(int 노드, int 모드) {
    배열[노드].값 *= 모드;
    방문 |= (1 << 노드);
    for (auto e : 배열[노드].연결) {
        if (!(방문 & (1 << e))) {
            갱신(e, 모드);
        }
    }
}

int main() {
    int 노드수, a, b, p, q, 최대공약수값, a모드, b모드;
    cin >> 노드수;
    for (int i = 0; i < 노드수 - 1; i++) {
        cin >> a >> b >> p >> q;
        최대공약수값 = 최대공약수(p, q);
        a모드 = 배열[b].값 * p / 최대공약수값;
        b모드 = 배열[a].값 * q / 최대공약수값;
        최대공약수값 = 최대공약수(a모드, b모드);
        방문 = 0;
        갱신(a, a모드 / 최대공약수값);
        갱신(b, b모드 / 최대공약수값);
        배열[a].연결.push_back(b);
        배열[b].연결.push_back(a);
    }

    for (int i = 0; i < 노드수; i++) {
        cout << 배열[i].값 << " ";
    }
    return 0;
}
