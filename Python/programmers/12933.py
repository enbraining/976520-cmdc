#정수 내림차순으로 배치하기

def solution(n):
    return int(''.join(map(str, sorted([int(digit) for digit in str(n)], reverse=True))))

    '''
    1. str()을 이용해 n을 문자열로 바꾼다.
    2. 문자열이 된 n을 한 자리씩 int로 바꿔 리스트에 저장한다. 
    3. sorted()로 이 list를 오름차순으로 정렬하고, reverse=True를 통해 내림차순으로 바꿔준다.
    4. map()을 통해 정렬된 원소들을 다시 문자열로 바꾼다.
    5. ''.join을 이용해 원소들을 이어붙여서 한 문자열로 만든다.
    6. 합쳐진 문자열을 int()를 이용해 정수로 바꿔서 return한다.
    '''