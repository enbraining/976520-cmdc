#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//정수n 입력받고 구구단 n단 출력

int main31() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= 9; i++) {
		printf("%d\n", i * n);
	}
}


