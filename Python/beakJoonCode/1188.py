ㅁ, ㄴ = map(int, input().split())

def gcd(ㅇ, ㄹ):
    if ㅇ % ㄹ == 0:
        return ㄹ
    return gcd(ㄹ, ㅇ % ㄹ)

print(ㄴ - gcd(ㅁ, ㄴ))
