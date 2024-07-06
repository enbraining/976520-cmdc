result_pairs = []
number_list = list(map(int, input().split()))
number_list = [[number_list[i], i + 1] for i in range(3)]

while True:
    number_list.sort()
    if number_list[0][0] == 0:
        break
    
    quotient, remainder = divmod(number_list[1][0], number_list[0][0])
    flag = remainder <= number_list[0][0] >> 1
    quotient += flag ^ 1
    
    while quotient > flag ^ 1:
        if quotient & 1:
            result_pairs.append((number_list[1][1], number_list[0][1]))
            number_list[1][0] -= number_list[0][0]
            number_list[0][0] <<= 1
        else:
            result_pairs.append((number_list[2][1], number_list[0][1]))
            number_list[2][0] -= number_list[0][0]
            number_list[0][0] <<= 1
        quotient >>= 1
    
    if flag ^ 1:
        result_pairs.append((number_list[0][1], number_list[1][1]))
        number_list[0][0] -= number_list[1][0]
        number_list[1][0] <<= 1

print(len(result_pairs))
for pair in result_pairs:
    print(*pair)
