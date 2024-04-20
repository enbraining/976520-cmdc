#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//18790 n의 배수
char sexyArray[1000][501][500];

void sexyFunction(int result[], int input[], char sexyArray[][501][500], int position, int selected, int remain, int N) {
    //position = 현재 위치 인덱스, selected = 선택된 숫자 개수, remain= 서낵된숫자합 % n
    if (position == 0) {
        for (int i = 1; i <= N; ++i) {  //위치가 0이면
            printf("%d ", result[i]); //결과 출력
        }
        return;
    }
    //섹시어레이로 현위치에서 가능한 겨우를 확인하여 재ㅜ귀
    if (sexyArray[position][selected][remain] && sexyArray[position - 1][selected - 1][(remain - input[position] + N) % N]) {
        result[selected] = input[position];
        sexyFunction(result, input, sexyArray, position - 1, selected - 1, (remain - input[position] + N) % N, N);
    } else { //혅 이치에서 불가능한 경우를 캐치하기위해 재귀
        sexyFunction(result, input, sexyArray, position - 1, selected, remain, N);
    }
}

int main(void) {
    int N; //배열의크기, ㅇㅂ력숫자갯
    int input[1000]; //주어진걸로 원하는 합을 만들수잇는지를 체크
    int result[501];
    //
    scanf("%d", &N);
    sexyArray[0][0][0] = 1; //sexyArray[a][b][c] 는 a번째까지의 숫자 b개를 사용해서 합을 c로 만들수 잇는지 여부

    for (int i = 1; i <= 2 * N - 1; ++i) { //숫자를 입력받으면서 dp배열 업데이트
        scanf("%d", input + i);
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                //이전 상태 -> 현재 상태
                sexyArray[i][j][k] |= sexyArray[i - 1][j][k]; //|= or연산 후 할당하는 연산자
                sexyArray[i][j + 1][(k + input[i]) % N] |= sexyArray[i - 1][j][k];
            }
        }
    }

    sexyFunction(result, input, sexyArray, 2 * N - 1, N, 0, N);

    return 0;
}
