#최댓값과 최솟값
def solution(s):
    return f"{min(map(int, s.split()))} {max(map(int, s.split()))}"

    '''
    1. split()를 통해 제공된 문자열 s를 공백을 기준으로 분리하여 list로 만든다
    2. map()을 이용해 만들어진 list의 모든 원소를 int로 바꾼다
    3. min()과 max()를 각각 이용해 int로만 이루어진 list에서 최소값과 최대값을 찾는다.
    4. f-string 문법을 통해 값들을 문자열로 합쳐서 return한다.
    '''