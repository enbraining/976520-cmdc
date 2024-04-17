#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//3개의 정수 값을 입력받아서 최대값을 출력하는 프로그램
int main12() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	printf("%d", ((a > b) ? a : b) > c ? ((a > b) ? a : b) : c);
}


