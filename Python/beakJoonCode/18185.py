def purchase_one_item(index):
    global total_cost
    total_cost += 3 * item_quantities[index]

def purchase_two_items(index):
    global total_cost
    min_quantity = min(item_quantities[index:index+2])
    item_quantities[index] -= min_quantity
    item_quantities[index+1] -= min_quantity
    total_cost += 5 * min_quantity

def purchase_three_items(index):
    global total_cost
    min_quantity = min(item_quantities[index:index+3])
    item_quantities[index] -= min_quantity
    item_quantities[index+1] -= min_quantity
    item_quantities[index+2] -= min_quantity
    total_cost += 7 * min_quantity

import sys
number_of_items = int(sys.stdin.readline())
item_quantities = list(map(int, sys.stdin.readline().split())) + [0, 0]
total_cost = 0

for i in range(len(item_quantities) - 2):
    if item_quantities[i+1] > item_quantities[i+2]:
        min_quantity = min(item_quantities[i], item_quantities[i+1] - item_quantities[i+2])
        item_quantities[i] -= min_quantity
        item_quantities[i+1] -= min_quantity
        total_cost += 5 * min_quantity
        purchase_three_items(i)
        purchase_one_item(i)
    else:
        purchase_three_items(i)
        purchase_two_items(i)
        purchase_one_item(i)

print(total_cost)
