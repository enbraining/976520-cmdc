#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//2단부터 n단까지 출력하기

int main46() {
	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= 9; j++) {
			printf("%d * %d = %d ", i, j, i * j);
		}
		printf("\n");
	}
}


