import sys
from cmath import exp, pi

def fast_fourier_transform(input_array):
    number_of_elements = len(input_array)
    if number_of_elements == 1:
        return input_array
    even_indexed_elements = fast_fourier_transform(input_array[0::2])
    odd_indexed_elements = fast_fourier_transform(input_array[1::2])
    twiddle_factors = [exp(2j * pi * n / number_of_elements) for n in range(number_of_elements // 2)]
    return [even_indexed_elements[n] + twiddle_factors[n] * odd_indexed_elements[n] for n in range(number_of_elements // 2)] + \
           [even_indexed_elements[n] - twiddle_factors[n] * odd_indexed_elements[n] for n in range(number_of_elements // 2)]

def inverse_fast_fourier_transform(input_array):
    number_of_elements = len(input_array)
    if number_of_elements == 1:
        return input_array
    even_indexed_elements = inverse_fast_fourier_transform(input_array[0::2])
    odd_indexed_elements = inverse_fast_fourier_transform(input_array[1::2])
    twiddle_factors = [exp(-2j * pi * n / number_of_elements) for n in range(number_of_elements // 2)]
    return [even_indexed_elements[n] + twiddle_factors[n] * odd_indexed_elements[n] for n in range(number_of_elements // 2)] + \
           [even_indexed_elements[n] - twiddle_factors[n] * odd_indexed_elements[n] for n in range(number_of_elements // 2)]

number_of_bits = int(sys.stdin.readline())
number_of_elements = 2 * number_of_bits
even_power_of_two = 0
for i in range(18):
    if number_of_bits == 2 ** i:
        even_power_of_two = -100
        break
    elif number_of_elements < 2 ** i:
        even_power_of_two = i
        break

input_array_a = list(map(int, sys.stdin.readline().split()))
input_array_b = list(map(int, sys.stdin.readline().split()))

if even_power_of_two == -100:
    input_array_a = input_array_a[:] + input_array_a[:]
    input_array_b = input_array_b[::-1] + [0] * number_of_bits
    output_array = [0] * number_of_elements
    fft_of_input_array_a = fast_fourier_transform(input_array_a)
    fft_of_input_array_b = fast_fourier_transform(input_array_b)
    for i in range(number_of_elements):
        output_array[i] = fft_of_input_array_a[i] * fft_of_input_array_b[i]

    inverse_fft_of_output_array = inverse_fast_fourier_transform(output_array)
    for k in range(number_of_elements):
        inverse_fft_of_output_array[k] = round(inverse_fft_of_output_array[k].real / number_of_elements)
    maximum_number = max(inverse_fft_of_output_array)
else:
    number_of_elements_prime = 2 ** i
    number_of_elements, number_of_elements_prime = number_of_elements_prime, number_of_elements
    input_array_a = input_array_a[:] + [0] * (number_of_elements - number_of_elements_prime // 2)
    input_array_b = input_array_b[::-1] + [0] * (number_of_elements - number_of_elements_prime) + input_array_b[::-1]

    output_array = [0] * number_of_elements
    fft_of_input_array_a = fast_fourier_transform(input_array_a)
    fft_of_input_array_b = fast_fourier_transform(input_array_b)
    for i in range(number_of_elements):
        output_array[i] = fft_of_input_array_a[i] * fft_of_input_array_b[i]
    inverse_fft_of_output_array = inverse_fast_fourier_transform(output_array)
    for k in range(number_of_elements):
        inverse_fft_of_output_array[k] = round(inverse_fft_of_output_array[k].real / number_of_elements)
    maximum_number = max(inverse_fft_of_output_array)

print(maximum_number)
