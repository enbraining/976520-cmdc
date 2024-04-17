#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//±× ¹®Á¦
int main18_1() {
	int x = 10, y = 5;
	y = x != 2 || y == 2;
	printf("%d %d\n", x, y); //10 1

	x = 4, y = 0;
	y += x || y;
	printf("%d %d\n", x, y); //4 1

	x = y = 1;
	x = -x-- + -y++;
	printf("%d %d\n", x, y); // -2 2

}


int main18_2() {
	int count = 10;
	int a, b;
	a = ++count;
	printf("%d %d\n", a, count); //11 11

	count = 10;
	b = count++;
	printf("%d %d\n", b, count); //10 11

	count = 10;
	a = --count;
	printf("%d %d\n", a, count); //9 9

	count = 10;
	b = count--;
	printf("%d %d\n", b, count); //10 9


}