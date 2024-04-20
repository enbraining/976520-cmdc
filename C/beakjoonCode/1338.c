#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//1338 알 수 없는 번호
int main() {
    long long int min, max, x, y;
    scanf("%lld %lld", &min, &max); //첫 번째 줄에는 수가 있을 수 있는 범위의 양끝 값을 의미하는 두 개의 수가 주어진다.
    if (min > max) {
        long long int temp = max;
        max = min;
        min = temp;
    }
    scanf("%lld %lld", &x, &y); //두 번째 줄에는 나누는 수 x와 나머지 y가 주어진다.
    x = llabs(x); //마이너스로 나눌라고 하다니. [절댓값] 형벌에 처해라.

    long long int a = (min / x * x) + y; //그 수
    long long int b = (min / x * x - x) + y; //그 수보다 하나작음
    long long int c = (min / x * x + x) + y; //그 수 보다 하나큼
    //몇 개가 들어가는지가 중요한게 아니라 1개인지 아닌지가 중요하니까 2개 넘는건 굳이 계산 안해
    int count = (min <= b && b <= max) + (min <= a && a <= max) + (min <= c && c <= max); //범위에 들어가는 값 개수


    if (y < 0 || y >= x || x == 0) { //만약 정확히 한 개로 추측할 수 없다면 Unknwon Number를 출력한다.
        printf("Unknwon Number");
    } else {
        if (count == 1) { //1개일때만
            if (min <= a && a <= max) { //어짜피 1개니까 걍 맞는거 출력
                printf("%lld", a);
            } else if (min <= b && b <= max) {
                printf("%lld", b);
            } else if (min <= c && c <= max) {
                printf("%lld", c);
            }
        } else { //어림도 없지
            printf("Unknwon Number");
        }
    }
}

