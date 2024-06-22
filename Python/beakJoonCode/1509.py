import sys
sys.setrecursionlimit(10 ** 8)
input_func = lambda: sys.stdin.readline().rstrip()

string = input_func()
length = len(string)

dp = [2500 for _ in range(length + 1)]
dp[-1] = 0
is_palindrome = [[0 for _ in range(length)] for _ in range(length)]

for i in range(length):
    is_palindrome[i][i] = 1

for i in range(1, length):
    if string[i - 1] == string[i]:
        is_palindrome[i - 1][i] = 1

for l in range(3, length + 1):
    for start in range(length - l + 1):
        end = start + l - 1
        if string[start] == string[end] and is_palindrome[start + 1][end - 1]:
            is_palindrome[start][end] = 1

for end in range(length):
    for start in range(end + 1):
        if is_palindrome[start][end]:
            dp[end] = min(dp[end], dp[start - 1] + 1)
        else:
            dp[end] = min(dp[end], dp[end - 1] + 1)

print(dp[length - 1])
