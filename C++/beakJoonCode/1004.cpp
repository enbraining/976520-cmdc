#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int 시도횟수, x1, y1, x2, y2, 중심x, 중심y, 반지름, 원수;
	float 거리 = 0;
	cin >> 시도횟수;

	while (시도횟수--) {
		int 카운트 = 0;
		cin >> x1 >> y1 >> x2 >> y2;
		cin >> 원수;

		while (원수--) {
			cin >> 중심x >> 중심y >> 반지름;

			거리 = sqrt(pow(중심x - x1, 2) + pow(중심y - y1, 2));

			bool 시작점_원이내 = sqrt(pow(중심x - x1, 2) + pow(중심y - y1, 2)) <= 반지름;
			bool 끝점_원이내 = sqrt(pow(중심x - x2, 2) + pow(중심y - y2, 2)) <= 반지름;

			if (시작점_원이내 != 끝점_원이내) {
				카운트++;
            }
		}

		cout << 카운트 << "\n";
	}
}
