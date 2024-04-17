#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//100보다 작은 정수를 입력받아서 십의 자리, 일의 자리로 분리하여 출력하는 프로그램
int main15() {
	int a;
	scanf("%d", &a);
	printf("%d %d", a / 10, a % 10);
}


