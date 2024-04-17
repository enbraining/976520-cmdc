#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//평을 제곱미터로 환산하는 프로그램, 1평=3.3058제곱미터
int main11() {
	double x, y;

	scanf("%lf", &x);

	y = 3.3058 * x;

	printf("%lf", y);
}


