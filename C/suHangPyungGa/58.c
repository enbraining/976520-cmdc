#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//58 피보나치 수열

int fibo(int a) {
	if (a > 1) {
		return fibo(a - 1) + fibo(a - 2);
	}
	return a;
}
int main58() {
	int a;
	scanf("%d", &a);
	printf("%d", fibo(a));
}


