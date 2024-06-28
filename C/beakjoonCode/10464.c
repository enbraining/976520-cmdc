#include <stdio.h>

int computeXorContribution(int *value) {
    int remainder = *value % 4;
    if (remainder == 0) {
        remainder = *value;
    } else if (remainder == 1) {
        remainder = 1;
    } else if (remainder == 2) {
        remainder = *value + 1;
    } else if (remainder == 3) {
        remainder = 0;
    }
    return remainder;
}

int main() {
    int testCases;
    scanf("%d", &testCases);
    while (testCases--) {
        int startValue, endValue;
        scanf("%d %d", &startValue, &endValue);
        --startValue;
        printf("%d\n", computeXorContribution(&endValue) ^ computeXorContribution(&startValue));
    }
}
