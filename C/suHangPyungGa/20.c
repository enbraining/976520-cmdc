#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//세 변의 길이(a<=b<=c)를 입력받고 무슨 삼각형(삼각형이 아님, 정, 이등변, 직각, 일반)인지 판단
int main20() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	if (a + b <= c) {
		printf("삼각형이 아님");
	}
	else if (a == b && b == c) {
		printf("정삼각형");
	}
	else if (a == b || b == c || c || a) {
		printf("이등변삼각형");
	}
	else if (a * a + b * b == c * c) {
		printf("직각삼각형");
	}
	else {
		printf("일반삼각형");
	}
}


