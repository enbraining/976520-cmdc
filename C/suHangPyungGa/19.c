#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//입력 2개 받아서 큰수-작은수
int main19() {
	int a = 0, b = 0;
	scanf("%d %d", &a, &b);
	printf("%d", ((a > b) ? a : b) - ((a < b) ? a : b));
}


