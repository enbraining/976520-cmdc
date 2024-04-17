#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//a와 b 사이 수 중 1의 자리가 3인 숫자의 개수 33

int main33() {
	int a, b, count = 0;
	scanf("%d %d", &a, &b);
	for (int i = a; i < b; i++) {
		if (i % 10 == 3) {
			count++;
		}
	}
	printf("%d", count);
}


