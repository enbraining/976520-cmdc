#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//문자열을 입력받아 문자열에 포함된 각 문자의 출현 횟수

int main() {
	char input[1000];
	int alphabet[26] = {0}, i=0;
	scanf("%s", input);

	while (input[i] != '\0') {
		alphabet[input[i] - 97]++;
		i++;
	}

	for (int k = 0; k < 26; k++) {
		if (alphabet[k] != 0) {
			printf("%c: %d\n", k+97, alphabet[k]);
		}
	}
}


