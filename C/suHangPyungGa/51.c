#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//배열의 max값

int main51() {
	int array[5] = { 6, 2, 7, 9, 3 }, max=0;

	for (int i = 0; i < 5; i++) {
		if (max < array[i]) {
			max = array[i];
		}
	}
	printf("%d", max);
}


