#하샤드 수

def solution(x):
    if x % sum([int(digit) for digit in str(x)]) == 0:
        return True
    else:
        return False