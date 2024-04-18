#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//태양과 행성간의 거리가 주어질 때 각 행성까지 빛이 도달하는 분 (광속 = 300,000m/s)

int main54() {
	char planet[4][100] = { "mercury", "vinus", "earth", "mars" };
	int distance[4] = { 58000000, 108000000, 150000000, 228000000 };
	double result[4] = {0};
	double lightspeed = 300000;

	for (int i = 0; i < 4; i++) {
		printf("%s %lf \n", planet[i], (distance[i] / lightspeed)/60);
	}
}


