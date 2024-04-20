#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//17433 신비로운 수

int f(long long int a, long long int b) { //두 값의 최대공약수 구하기
    long long int temp;
    while (1) {
        if (b == 0) {
            break;
        } else if (a % b == 0) { //나가는조건
            break;
        }
        temp = a;
        a = b;
        b = temp % b; //다음 반복에 쓸거
    }
    return b;
}

int main1() {
    int N;
    scanf("%d", &N);
    for (int s = 0; s < N; s++) {
        int t, k, x = 0;
        long long int jungsu[2000] = { 0 }, cha[2000] = { 0 }, sexyJungsu[2000] = { 0 };

        scanf("%d", &t); //첫째 줄에 테스트 케이스의 개수 T가 주어진다.

        for (int i = 0; i < t; i++) { //각 테스트 케이스는 두 줄로 이루어져 있고, 첫째 줄에 N, 둘째 줄에 N개의 정수가 주어진다.
            scanf("%lld", &jungsu[i]);
        }

        for (int j = 0; j < t - 1; j++) { //cha에 이웃한 두 양수 사이 차의 절댓값을 저장
            //자미막 값에는 이웃할 아이가 없어요. ㅅ-1
            cha[j] = llabs(jungsu[j] - jungsu[j + 1]);
        }

        if (t == 2) { //테스트 케이스의 길이가 2일 때

            if (cha[0] == 0) {
                printf("INFINITY\n");
                continue;
            }

            printf("%lld\n", cha[0]);

        } else { //테스트 케이싀 길이가 2보다 클 때

            sexyJungsu[0] = f(cha[0], cha[1]); //cha의 값끼ㅣ리최대공약수를 계산하여 첫 번째 값을 sexyJungsu에 저장

            for (k = 1; k < t - 2; k++) { //sexyJungsu 나머지 값을 계산
                sexyJungsu[k] = f(sexyJungsu[k - 1], cha[k + 1]);
            }


            if (sexyJungsu[k - 1] == 0) { //마지막이 0이면 이상하잖아
                printf("INFINITY\n");
                continue;
            }

            printf("%lld\n", sexyJungsu[k - 1]); //안이상하면 마지막꺼 출력할게
        }
    }
}