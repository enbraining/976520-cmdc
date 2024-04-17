#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//문자를 입력받아 출력하고 q가 입력되면 종료하기

int main39() {
	char input = 'a';

	while (input != 'q') {
		scanf("%c", &input);
		printf("%c", input);

	}
}


