import sys
input = sys.stdin.readline

num_elements, data_list, sum_values, frequency_count = int(input()), [], 0, {}

for _ in range(num_elements):
    value = int(input())
    data_list.append(value)
    sum_values += value
    frequency_count[value] = frequency_count.get(value, 0) + 1

data_list.sort()
print(round(sum_values / num_elements), data_list[num_elements // 2], sep='\n')

max_frequency = max(frequency_count.values())
mode_candidates = sorted(key for key, count in frequency_count.items() if count == max_frequency)
print(mode_candidates[0] if len(mode_candidates) == 1 else mode_candidates[1])
print(data_list[-1] - data_list[0])
