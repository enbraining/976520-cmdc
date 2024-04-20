#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int hh[100000];

long long int size(int s, int e) { //0, n-1
    if (e < s) { //어림도없지
        return -1;
    }
    if (s == e) { //'첨 = 끝' 일때 그 막대기높이 반환
        return hh[s];
    }

    int mid = (s + e) / 2; //중간 막대기 설정
    int i = mid, j = mid + 1; //서쪽인덱스 = 중간막대기 하나전에서 시작, 동쪽시끼 = 준간막대기 하나다음부터
    int h = hh[mid]; //현재 높이
    long long int westSize = size(s, mid - 1); //왼쪽부터 중간막대기 하나전까지
    long long int eastSize = size(mid + 1, e); //중간대 다음부터 오른쪽끝까지
    long long int gaeJjang = hh[mid]; //리턴될아이

    while (s <= i || j <= e) { //둘 다 달성해야 종료

        if (i < s || (j <= e && hh[i] < hh[j])) { //i가 왼쪽 끝에로 갓다 || (오른쪽 인덱스가 범위안에 있다 && 오른쪽 막대의 높이가 더 크다)
            h = hh[j] < h ? hh[j] : h; //h에 최소높이 할당
            gaeJjang = gaeJjang > (long long int) h * (j - i) ? gaeJjang : (long long int) h * (j - i); //높이 * 폭(=넙이)
            j++; //왼쪽에 더 못가니까 오른쪽만 증가
        } else { //아직 끝에 안닿으면
            h = hh[i] < h ? hh[i] : h; //h에 최소높이 할당
            gaeJjang = gaeJjang > (long long int) h * (j - i) ? gaeJjang : (long long int) h * (j - i); //넓이
            i--; //왼쪽만 계속가
        }
    }

    //결승전
    if (gaeJjang < westSize) {
        gaeJjang = westSize;
    }
    if (gaeJjang < eastSize) {
        gaeJjang = eastSize;
    }

    return gaeJjang;
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n); //직사각형의 수 n이 가장 처음으로 주어진다. (1 ≤ n ≤ 100,000)
        if (n == 0) { //입력의 마지막 줄에는 0이 하나 주어진다.
            break;
        }
        for (int i = 0; i < n; ++i) { //그 다음 n개의 정수 h1, ..., hn (0 ≤ hi ≤ 1,000,000,000)가 주어진다.
            scanf("%d", &hh[i]); //이 숫자들은 히스토그램에 있는 직사각형의 높이이며, 왼쪽부터 오른쪽까지 순서대로 주어진다.
        }
        printf("%lld\n", size(0, n - 1)); //출력
    }
    return 0;
}
