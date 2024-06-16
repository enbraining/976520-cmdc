import sys
k, n = map(int, sys.stdin.readline().split())
used_numbers = [0]
triplet_set = set()  # (a, b, c) 형태의 삼중쌍 저장
triplet_set.add((0, 1, k))

while n:
    temp_set = triplet_set.copy()  # 현재 triplet_set을 temp_set에 복사
    for a, b, c in triplet_set:  # 모든 삼중쌍을 탐색
        if a != b and b != c:  # 세 숫자가 서로 다를 때
            if a not in used_numbers and b not in used_numbers and c not in used_numbers:  # 이미 사용된 숫자가 아닐 때
                used_numbers += [a, b, c]  # 사용된 숫자들에 추가
                print(a, b, c)  # a, b, c 출력
                n -= 1  # 출력 횟수 감소
                if n == 0:  # n이 0이 되면
                    break  # 반복문 종료
            for _ in range(3):  # 3번 반복 (a, b, c 각각에 대해)
                new_number = k * (a + b) - c  # 새로운 숫자 생성
                if new_number >= 0:  # 새로운 숫자가 0 이상일 때
                    temp_set.add(tuple(sorted([a, b, new_number])))  # temp_set에 추가
                a, b, c = b, c, a  # 순서를 바꾸어 다음 탐색
    triplet_set = temp_set  # triplet_set 갱신
