#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//4자리 수를 입력받아 거꾸로 출력하기

int main38() {
	int input;
	scanf("%d", &input);

	while (input > 0) {
		printf("%d", input % 10);
		input = input / 10;
	}
}


