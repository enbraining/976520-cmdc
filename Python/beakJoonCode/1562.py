import sys

input_func = sys.stdin.readline

N = int(input_func())
dp = [[[0 for _ in range(1 << 10)] for _ in range(10)] for _ in range(N)]
#자릿수 ㅁ까지 봤을 때 현재 숫자로 ㄴ를 선택한 경우, 비트 ㅇ에 해당하는 숫자들을 방문하는 경우의 수
mod = 1000000000
result = 0

for starting_digit in range(1, 10):  # 0을 제외하고 시작하는 모든 숫자에 대해
    dp[0][starting_digit][1 << starting_digit] = 1  # 초기값 1 

for digit_length in range(1, N):  # 각 자릿수에 대해
    for current_digit in range(10):  # 0~9 중 택1
        for bit_mask in range(1024):  # 모든 방문 기록을 고려
            if current_digit - 1 >= 0:
                dp[digit_length][current_digit][bit_mask | (1 << current_digit)] += dp[digit_length - 1][current_digit - 1][bit_mask]
            if current_digit + 1 <= 9:
                dp[digit_length][current_digit][bit_mask | (1 << current_digit)] += dp[digit_length - 1][current_digit + 1][bit_mask]
            dp[digit_length][current_digit][bit_mask | (1 << current_digit)] %= mod

for last_digit in range(10):  # 마지막 자릿수의 숫자에 대해서
    result += dp[N - 1][last_digit][1023]  # 0부터 9까지 모든 숫자를 방문한 경우 (1111111111(2) = 1023)
    result %= mod

print(result)
