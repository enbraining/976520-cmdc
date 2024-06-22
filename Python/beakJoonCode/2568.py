#pypy로 제출하니까 성공하는 ㄹㅈㄷ억까채점;;
#https://www.acmicpc.net/problem/2568

def find_lower_bound_index(sorted_list, target):
    low = 0
    high = len(sorted_list) - 1
    while low < high:
        mid = (low + high) // 2
        if target <= sorted_list[mid]:
            high = mid
        elif target > sorted_list[mid]:
            low = mid + 1
    return high

item_dict = {}
items_list = []
longest_increasing_subsequence = [-1]
result_list = []
removed_items = []
number_of_items = int(input())

for _ in range(number_of_items):
    item_price, item_id = map(int, input().split(' '))
    item_dict[item_id] = item_price

sorted_prices = sorted(item_dict)
for key in sorted_prices:
    items_list.append(item_dict.get(key))

for price in items_list:
    if price > longest_increasing_subsequence[-1]:
        longest_increasing_subsequence.append(price)
    else:
        longest_increasing_subsequence[find_lower_bound_index(longest_increasing_subsequence, price)] = price
    result_list.append(longest_increasing_subsequence.index(price) + 1)

lis_length = len(longest_increasing_subsequence)
for i in range(len(items_list) - 1, -1, -1):
    if result_list[i] == lis_length:
        removed_items.append(items_list[i])
        lis_length -= 1

print(number_of_items - (len(longest_increasing_subsequence) - 1))
items_list.sort()
for item in removed_items:
    items_list.remove(item)
for item in items_list:
    print(item)
