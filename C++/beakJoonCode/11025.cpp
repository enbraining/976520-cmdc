#include <iostream>
using namespace std;

int main() {
	int ㅁ, ㄴ;
	cin >> ㅁ >> ㄴ;

	int ㅇ = 0;
	for (int i = 2; i <= ㅁ; ++i) {
		ㅇ = (ㅇ + ㄴ) % i;
	}
	cout << ㅇ + 1;
}
