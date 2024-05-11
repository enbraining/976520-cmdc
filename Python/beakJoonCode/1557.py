#1557 제곱 ㄴㄴ https://www.acmicpc.net/problem/1557
def check(x):
    count = 0  #제곱ㄴㄴ수 개수
    namauji = 0  #x를 제곱수로 나누었을 때 나머지가 있는지
    queue = [(1, -1, 1)]  # (n, i, sign)

    while queue:  #queue가 비어있을 때까지
        n, i, sign = queue.pop()  # queue에서 마지막으로 들어간 값
        for j in range(i + 1, P):  # i + 1부터 시작하여 소수를 반복
            nn = n * prime[j] ** 2  # n에 prime[j]의 제곱을 곱한 값을 계산
            if nn > x:  # nn이 목표값 x를 초과하면 루프를 종료
                break

            count += x // nn * sign #x 안에 n1의 배수의 개수를 더하여 count를 업데이트하고 sign과 곱함
            namauji |= int(not x % nn) #x가 n1로 나누어 떨어지지 않으면 namauji를 업데이트
            
            queue.append((nn, j, -sign)) # queue에 (nn, j, -sign)를 추가해가꼬 계속
    return x - count, namauji

prime = [] # 소수를 저장할 리스트 
visited = [0] * 50001 #확인한 숫자인지 여부를 표시할 리스트

for i in range(2, 50001): # 에라토스트뭐시기의 체
    if not visited[i]:  # i가 확인되지 않았다면 소수인것이여
        prime.append(i)  # 소수 리스트에 i 추가

        # i의 모든 배수를 확인한 것으로 표시
        if i < 317:  #317은 50000을 넘지 않는 가장 작은 소수 = 반복 회수 줄어들어서 최적화
            for j in range(1, 50000 // i + 1):
                visited[i * j] = 1

P = len(prime) # 소수 리스트의 길이 계산
K = int(input()) #몇번째 제곱ㄴㄴ수인지 입력받음

x, c = 1 << 31, 30 # x를 ㅈㄴ큰 값으로 초기화하고 c를 30으로 초기화

# 이진 탐색 루프를 사용하여 K번째 제곱ㄴㄴ수를 찾음
while 1:  # break 문에 도달할 때까지 무한 루프
    k, namauji = check(x)  # check 함수를 호출하여 k와 namauji 얻기

    if k < K:  #k가 원하는 값 K보다 작으면
        x += 1 << c  # x를 2^c만큼 증가
    elif k > K or (k == K and namauji):  # k가 K보다 크거나 같고 namauji가 True이면
        x -= 1 << c  # x를 2^c만큼 감소
    else:  # k가 K와 같고 namauji가 False인 경우
        break

    c -= 1  # c를 1만큼 감소시킴

print(x) # K번째 제곱ㄴㄴ수를 출력
