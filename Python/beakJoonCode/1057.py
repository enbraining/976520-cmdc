n, start, end=map(int, input().split())
count=0
while start!=end:
  start -= start//2
  end -= end//2
  count+= 1
print(count)
