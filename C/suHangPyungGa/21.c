#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//초를 입력받아 시 분 초로 출력
int main21() {
	int second;
	scanf("%d", &second);

	int hour = second / 3600;
	second = second % 3600;
	int minute = second / 60;
	second = second % 60;
	printf("%d시 %d분 %d초", hour, minute, second);
}


