n = int(input())
arr = []
for i in range(n):
    arr.append(int(input()))
       
arr.sort(reverse=True)
result = []

for j in range(n):
    result.append(arr[j] * (j+1))

print(max(result))
