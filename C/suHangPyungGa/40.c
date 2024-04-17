#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//소문자 입력 대문자 출력

int main40() {
	int input = 'a';

	while (input != 'q') {
		input = getchar();
		getchar();
		printf("%c %c\n", input, input - 32);
	}


}


