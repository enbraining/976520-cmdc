import math

def d(N): 
    return N > 1 and all(N % i for i in range(2, int(math.sqrt(N)) + 1))

N = int(input())

for _ in range(N):
    num = int(input())
    A, B = num // 2, num // 2
    
    while not (d(A) and d(B)):
        A, B = A - 1, B + 1
    
    print(A, B)
