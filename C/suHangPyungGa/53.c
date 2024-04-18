#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//n을 입력받고 n^2 2차원 배열 출력 (값은 0행부터, 1부터 오름차순 출력)

int main53() {
	int n, t=1, array[100][100];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			array[i][j] = t++;

		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}


