//https://www.acmicpc.net/problem/1038

#include <stdio.h>

// 주어진 숫자가 감소하는 수인지 확인
int isDecreasingNumber(long number) {
    if (number <= 10) return 1;
    while (1) {
        int lastDigit = number % 10;
        number /= 10;
        if (number == 0) return 1;
        if (number % 10 <= lastDigit) return 0;
    }
}

int main() {
    int input;
    scanf("%d", &input);
    input++;

    // 1023보다 큰 경우 감소하는 수를 만들 수 없으므로 -1 출력
    if (input > 1023) {
        printf("-1");
    }
    else {
        long answer = -1;
        int count = 1;

        // 특정 범위의 input에 대해 초기 answer와 count 설정
        if (input <= 10) {
            answer = 0;
            count = 1;
        }
        else if (input <= 55) {
            answer = 10;
            count = 11;
        }
        else if (input <= 175) {
            answer = 210;
            count = 56;
        }
        else if (input <= 385) {
            answer = 3210;
            count = 176;
        }
        else if (input <= 637) {
            answer = 43210;
            count = 386;
        }
        else if (input <= 847) {
            answer = 543210;
            count = 638;
        }
        else if (input <= 967) {
            answer = 6543210;
            count = 848;
        }
        else if (input <= 1012) {
            answer = 76543210;
            count = 968;
        }
        else if (input <= 1022) {
            answer = 876543210;
            count = 1013;
        }
        else if (input <= 1023) {
            answer = 9876543210;
            count = 1023;
        }

        // 시작 숫자에서 1 감소
        answer--;

        // input에 도달할 때까지 감소하는 수를 찾아 증가
        while (count <= input) {
            count += isDecreasingNumber(++answer);
        }

        // 결과 출력
        printf("%ld", answer);
    }
}
