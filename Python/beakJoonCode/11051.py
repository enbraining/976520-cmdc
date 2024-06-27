from math import factorial
import sys

n, k = map(int, sys.stdin.readline().split())
print(factorial(n) // (factorial(k) * factorial(n - k)) % 10007)
