#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//입력한 문자열의 글자 수 출력

int main37() {
	char input[100];
	scanf("%s", input);
	int i = 0;
	while (input[i] != '\0') {
		i++;
	}
	printf("%d", i);
}


