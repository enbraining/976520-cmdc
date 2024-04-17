#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//57 Àç±Í ÆÑÅä¸®¾ó

int factorial(int a) {
	int output = 1;
	if (a > 1) {
		return (a * factorial(a - 1));
	}
	return 1;
}
int main57() {
	int a;
	scanf("%d", &a);
	printf("%d", factorial(a));
}


