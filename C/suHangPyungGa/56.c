#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//56
int maxReturn(int a, int b) {
	return((a > b) ? a : b);
}
int main56() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d", max(a, b));
}


