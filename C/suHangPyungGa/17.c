#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//입력값이 50이상 60이하이면 win, 그 외에 lose
int main17() {
	int a;
	scanf("%d", &a);

	if (50 <= a && a <= 60) {
		printf("win");
	}
	else {
		printf("lose");
	}

}


