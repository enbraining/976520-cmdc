import sys, itertools
input = sys.stdin.readline
테스트_케이스_수 = int(input())

for _ in range(테스트_케이스_수):
    점의_개수 = int(input())
    좌표_리스트 = []
    총_x, 총_y = 0, 0

    for _ in range(점의_개수):
        x, y = map(int, input().split())
        총_x += x
        총_y += y
        좌표_리스트.append((x, y))

    조합 = list(itertools.combinations(좌표_리스트, 점의_개수 // 2))
    최소값 = 3e5

    for 조합_부분 in 조합[:len(조합) // 2]:
        그룹1_x, 그룹1_y = 0, 0
        for x, y in 조합_부분:
            그룹1_x += x
            그룹1_y += y
        그룹2_x, 그룹2_y = 총_x - 그룹1_x, 총_y - 그룹1_y

        합벡터 = ((그룹2_x - 그룹1_x) ** 2 + (그룹2_y - 그룹1_y) ** 2) ** 0.5
        최소값 = min(최소값, 합벡터)

    print(최소값)
