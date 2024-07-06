#include<iostream>
#include<algorithm>
using namespace std;

int 배열[100001];
int dp[100001][2];

int main() {
    ios_base::sync_with_stdio(false);
    int 개수;
    cin >> 개수;
    for (int 인덱스 = 0; 인덱스 < 개수; 인덱스++) {
        cin >> 배열[인덱스];
    }

    int 최대합 = 배열[0];
    for (int 인덱스 = 0; 인덱스 < 개수; 인덱스++) {
        dp[인덱스][0] = dp[인덱스][1] = 배열[인덱스];
        if (인덱스 == 0) continue;
        dp[인덱스][0] = max(dp[인덱스 - 1][0] + 배열[인덱스], 배열[인덱스]);
        dp[인덱스][1] = max(dp[인덱스 - 1][0], dp[인덱스 - 1][1] + 배열[인덱스]);
        최대합 = max(최대합, max(dp[인덱스][0], dp[인덱스][1]));
    }
    cout << 최대합 << '\n';
    return 0;
}
