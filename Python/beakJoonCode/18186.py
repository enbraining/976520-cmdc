import sys
input = sys.stdin.buffer.readline

number_of_customers, price_of_bundle, price_of_individual = map(int, input().split())
lamen_count_per_customer = list(map(int, input().split())) + [0, 0]
total_cost = 0

if price_of_bundle <= price_of_individual:
	print(price_of_bundle * sum(lamen_count_per_customer))
	exit()

for current_customer_index in range(number_of_customers):
	while lamen_count_per_customer[current_customer_index]:
		if lamen_count_per_customer[current_customer_index + 1]:
			if lamen_count_per_customer[current_customer_index + 2]:
				if lamen_count_per_customer[current_customer_index + 1] > lamen_count_per_customer[current_customer_index + 2]:
					minimum_lamen_count_to_buy_two = min(lamen_count_per_customer[current_customer_index], lamen_count_per_customer[current_customer_index + 1] - lamen_count_per_customer[current_customer_index + 2])
					lamen_count_per_customer[current_customer_index] -= minimum_lamen_count_to_buy_two
					lamen_count_per_customer[current_customer_index + 1] -= minimum_lamen_count_to_buy_two
					total_cost += (price_of_bundle + price_of_individual) * minimum_lamen_count_to_buy_two
				else:
					minimum_lamen_count_to_buy_three = min(lamen_count_per_customer[current_customer_index], lamen_count_per_customer[current_customer_index + 1], lamen_count_per_customer[current_customer_index + 2])
					lamen_count_per_customer[current_customer_index] -= minimum_lamen_count_to_buy_three
					lamen_count_per_customer[current_customer_index + 1] -= minimum_lamen_count_to_buy_three
					lamen_count_per_customer[current_customer_index + 2] -= minimum_lamen_count_to_buy_three
					total_cost += (price_of_bundle + 2 * price_of_individual) * minimum_lamen_count_to_buy_three
			else:
				minimum_lamen_count_to_buy_two = min(lamen_count_per_customer[current_customer_index], lamen_count_per_customer[current_customer_index + 1])
				lamen_count_per_customer[current_customer_index] -= minimum_lamen_count_to_buy_two
				lamen_count_per_customer[current_customer_index + 1] -= minimum_lamen_count_to_buy_two
				total_cost += (price_of_bundle + price_of_individual) * minimum_lamen_count_to_buy_two
		else:
			total_cost += price_of_bundle * lamen_count_per_customer[current_customer_index]
			lamen_count_per_customer[current_customer_index] = 0

print(total_cost)
