#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//키를 입력하면 120보다 큰지 작은지 출력, 작으면 얼마나 커야 120인지 출력
int main22() {
	int input;
	scanf("%d", &input);

	if (input < 120) {
		printf("%d", 120 - input);
	}
	else {
		printf("ga nung");
	}

}


