target_number = int(input())

min_operations = [0] * 1000001

for num in range(2, target_number + 1):
    min_operations[num] = min_operations[num - 1] + 1
    if num % 2 == 0:
        min_operations[num] = min(min_operations[num], min_operations[num // 2] + 1)
    if num % 3 == 0:
        min_operations[num] = min(min_operations[num], min_operations[num // 3] + 1)

print(min_operations[target_number])
