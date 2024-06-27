ㅁ, ㄴ = map(int, input().split())
result = ㅁ*ㄴ

while ㄴ:
    if ㅁ > ㄴ:
        ㅁ, ㄴ = ㄴ, ㅁ
    ㄴ %= ㅁ

print(result//ㅁ)
