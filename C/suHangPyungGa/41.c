#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//1부터 20까지 n의 배수 제외 출력

int main41() {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= 20; i++) {
		if (i % n == 0) {
			continue;
		}
		else {
			printf("%d ", i);
		}
	}

}


