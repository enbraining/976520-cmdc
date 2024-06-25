import sys
input_from_stdin = sys.stdin.readline

number_of_test_cases = int(input_from_stdin())

extremely_large_number = 10**9
for _ in range(number_of_test_cases):
    number_of_books = int(input_from_stdin())
    book_page_counts = list(map(int, input_from_stdin().split()))
    prefix_sum_of_book_page_counts = [0]*(number_of_books+1)
    dynamic_programming_table = [[extremely_large_number] *number_of_books for _ in range(number_of_books)]
    minimum_k_index_store_array = list(range(number_of_books))
    for i in range(number_of_books):
        dynamic_programming_table[i][i] = 0
        prefix_sum_of_book_page_counts[i+1] = prefix_sum_of_book_page_counts[i] + book_page_counts[i]
    for term_length in range(1,number_of_books):
        new_minimum_k_index_store_array = [None]*number_of_books
        for start_index in range(number_of_books-term_length):
            end_index = term_length+start_index
            for k in range(minimum_k_index_store_array[start_index],min(minimum_k_index_store_array[start_index+1]+1,end_index)):
                if dynamic_programming_table[start_index][end_index] > dynamic_programming_table[start_index][k]+dynamic_programming_table[k+1][end_index]:
                    dynamic_programming_table[start_index][end_index] = dynamic_programming_table[start_index][k]+dynamic_programming_table[k+1][end_index]
                    new_minimum_k_index_store_array[start_index] = k

            dynamic_programming_table[start_index][end_index] += prefix_sum_of_book_page_counts[end_index+1] - prefix_sum_of_book_page_counts[start_index]
        minimum_k_index_store_array = new_minimum_k_index_store_array
    print(dynamic_programming_table[0][number_of_books-1])
