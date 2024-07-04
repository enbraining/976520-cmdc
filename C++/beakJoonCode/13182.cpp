#include <stdio.h>
#define mod 1000000007

long long 제곱_모듈러 (long long A, long long 제곱);

int main() {

	int 테스트케이스수;
	scanf("%d", &테스트케이스수);
	
	int 빨강, 초록, 파랑, 횟수;
	while(테스트케이스수--) {
		scanf("%d %d %d %d", &빨강, &초록, &파랑, &횟수);
		
		long long 답 = 횟수;
		
		long long 임시변수;
		임시변수 = 제곱_모듈러(파랑, 횟수) * 제곱_모듈러(1+파랑, mod - 횟수 - 1) % mod;
		임시변수 = (1 - 임시변수 + mod) % mod;
		임시변수 = 임시변수 * 빨강 % mod;
		
		답 = (답 + 임시변수) % mod;
		
		임시변수 = 초록 * 제곱_모듈러(파랑, mod - 2) % mod;
		임시변수 = 임시변수 * 횟수 % mod;
		
		답 = (답 + 임시변수) % mod;
		printf("%lld\n", 답);
	}
	return 0;
}

long long 제곱_모듈러 (long long ㅇ, long long 제곱) {
	long long 결과 = 1;
	while(제곱) {
		if (제곱 % 2) {
			결과 = 결과 * ㅇ % mod;
		}
		ㅇ = ㅇ * ㅇ % mod;
		제곱 /= 2;
	}
	return 결과;
}
