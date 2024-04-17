#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//윤년인지 아닌지 판별 (4의 배수이면서 100의 배수가 아니면 윤년, 400의 배수는 윤년)
int main16() {
	int a;
	scanf("%d", &a);

	if (a % 4 == 0 && a % 100 != 0) {
		printf("yes");
	}
	else if (a % 400 == 0) {
		printf("yes");
	}
	else {
		printf("no");
	}

}


