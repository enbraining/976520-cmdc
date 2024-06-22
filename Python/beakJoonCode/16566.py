from bisect import bisect_left, bisect_right
import sys
input = sys.stdin.readline

total_number_of_cards, number_of_cards_to_submit, number_of_duplicates = map(int, input().strip().split())
card_numbers = list(map(int, input().strip().split()))
submitted_cards = list(map(int, input().strip().split()))
visited_indices = [False] * (len(card_numbers) + 1)

card_numbers.sort()
for submitted_card in submitted_cards:
    right_index = bisect_right(card_numbers, submitted_card)
    while True:
        if not visited_indices[right_index]:
            visited_indices[right_index] = True
            print(card_numbers[right_index])
            break
        else:
            right_index += 1
