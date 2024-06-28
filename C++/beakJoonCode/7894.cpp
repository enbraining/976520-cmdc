#include <iostream>
#include <cmath>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0) 
using namespace std;

int main() {
    fastio;
    int tc;
    cin >> tc;
    while (tc--) {
        double s, result = 0;
        cin >> s;
        for (double i = 1; i <= s; i++) {
            result += log10(i);
        }
        cout << static_cast<int>(result) + 1 << '\n';
    }
    return 0;
}
