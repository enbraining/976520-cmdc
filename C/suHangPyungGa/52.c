#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//Çà¿­ÇÕ

int main52() {
	int a[2][3] = { 3, 4, 5, 6, 7, 8 };
	int b[2][3] = { 2, 3, 4, 5, 6, 7 };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", a[i][j] + b[i][j]);
		}
		printf("\n");
	}
}


