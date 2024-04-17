#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//각 배열의 총점을 각 행의 5번째 열에 저장

int total(int score[4][5]) {

	int sum = 0, j;
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (j = 0; j < 4; j++) {
			sum = sum + score[i][j];
		}
		score[i][4] = sum;
	}
}

int main60() {
	int score[4][5] = { {81, 92, 23, 39, 0}, {69, 81, 48 ,96, 0}, { 81, 92, 23, 39, 0 }, { 69, 81, 48,96, 0 } };
	int i = 4;
	total(score);

	for (i = 0; i < 4; i++) {
		printf("%d ", score[i][4]);
	}
}


