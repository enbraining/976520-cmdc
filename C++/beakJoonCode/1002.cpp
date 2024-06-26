#include <iostream>
using namespace std;

int main() {
    int x1, y1, r1, x2, y2, r2, distanceSquared, innerRadiusDiffSquared, outerRadiusSumSquared, numTestCases;

    cin >> numTestCases; // 테스트 케이스 수 입력
    
    for(int i = 0; i < numTestCases; i++) { // 각 테스트 케이스에 대해 반복
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2; // 각 원의 중심 좌표와 반지름 입력
        distanceSquared = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); // 두 원의 중심 간 거리의 제곱 계산
 
        innerRadiusDiffSquared = (r1 - r2) * (r1 - r2); 
        outerRadiusSumSquared = (r1 + r2) * (r1 + r2); 
        
        if(distanceSquared == 0) {
            if(innerRadiusDiffSquared == 0) { 
                cout << "-1" << '\n';  // 걍 같은 원
            } else {
                cout << "0" << '\n';  // 접점 x
            }
        } else if (distanceSquared == innerRadiusDiffSquared || distanceSquared == outerRadiusSumSquared) {
            cout << "1" << '\n';  // 접점 1 
        } else if (innerRadiusDiffSquared < distanceSquared && distanceSquared < outerRadiusSumSquared) {
            cout << "2" << '\n';  // 접점 2
        } else {
            cout << "0" << '\n';  // 접점 x
        }
           
    }

    return 0;
}
