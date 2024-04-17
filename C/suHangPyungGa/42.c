#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//1부터 100 중 입력한 수의 배수의 개수 출력

int main42() {
	int input, count = 0;
	scanf("%d", &input);
	for (int i = 1; i <= 100; i++) {
		if (i % input == 0) {
			count++;
		}
	}
	printf("%d", count);

}


