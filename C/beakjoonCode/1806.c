#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//1806 ÇÕ¼º°ö
main1806() {
    int n, s;
    scanf("%d %d", &n, &s);

    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int min = 1000000000;
    int start = 0, end = 0;
    int sum = 0;

    while (1) {
        if (sum >= s) {
            min = ((end - start) < min) ? (end - start) : min;
            sum = sum - arr[start++];
        } else if (end == n) {
            break;
        } else {
            sum = sum + arr[end++];
        }
    }

    if (min == 1000000000) {
        printf("0\n");
    } else {
        printf("%d\n", min);
    }

    return 0;
}