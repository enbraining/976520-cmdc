#include <iostream>
using namespace std;

int main() {
	int 시도횟수 = 0;
    int 입력값 = 0;
	cin >> 시도횟수;
	int* 배열;
	while (시도횟수--) {
		cin >> 입력값;
		if (입력값 < 2) {
			if (입력값 == 0) {
				cout << "1 0" << endl;
			} else {
				cout << "0 1" << endl;
			}
		} else {
			배열 = new int[41];
			배열[0] = 1, 배열[1] = 1;
			for (int i = 2; i <= 입력값; i++) {
				배열[i] = 배열[i - 1] + 배열[i - 2];
			}
			cout << 배열[입력값 - 2] << " " << 배열[입력값 - 1] << endl;
		}
	}
	return 0;
}
