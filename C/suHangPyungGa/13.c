#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//16진수 정수를 입력받아서 8진수 10진수 16진수로 출력하는 프로그램
int main13() {
	int input;
	scanf("%d", &input);
	printf("%#o %d %#x", input, input, input);
}


