import sys

def compute_probability_of_event():
    input_values = sys.stdin.readline()
    input_values_list = list(map(int, input_values.split()))
    initial_state, initial_successes, future_trials, future_successes = input_values_list[0], input_values_list[1], input_values_list[2], input_values_list[3]
   
    current_probability = 1
    for trial_index in range(0, future_trials + 1):
        current_probability = current_probability * (initial_state - initial_successes + 1 + trial_index) / (initial_state + 2 + trial_index)
    cumulative_probability = current_probability
    
    for success_index in range(1, future_successes + 1):
        current_probability *= (initial_successes + success_index) * (future_trials + 2 - success_index) / success_index / (initial_state + future_trials - initial_successes + 2 - success_index)
        cumulative_probability += current_probability

    sys.stdout.write(str(cumulative_probability) + '\n')

number_of_cases = int(input())
for case_index in range(number_of_cases):
    compute_probability_of_event()
