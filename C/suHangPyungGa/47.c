#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//세로와 가로를 입력받고 별로 사각형 출력

int main47() {
	int h, w;
	scanf("%d %d", &h, &w);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			printf("*");
		}
		printf("\n");
	}
}


