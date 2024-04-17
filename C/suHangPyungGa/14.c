#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//2개의 정수를 입력받아서 첫 번째를 두번재로 나누었을때 몫과 나머지를 출력
int main14() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d %d", a / b, a % b);
}


