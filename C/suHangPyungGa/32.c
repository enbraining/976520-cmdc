#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//a에 b를 n번 반복해서 더하기

int main32() {
	int a = 4, b = 5, n = 9;
	for (int i = 0; i < n; i++) {
		a = a + b;
	}
	printf("%d", a);
}


