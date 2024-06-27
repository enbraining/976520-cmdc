import sys
input = sys.stdin.readline

for i in range(1, int(input())+1):
    if 30 % (i+1) == 0:
        print(i)
