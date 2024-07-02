numberOfIntervals = int(input())
 
start1, end1 = map(int, input().split())
 
totalLength = 0
for _ in range(numberOfIntervals - 1):
    start2, end2 = map(int, input().split())
 
    if start1 <= end2 <= end1:  
        continue
    elif start1 <= start2 <= end1 and not start1 <= end2 <= end1: 
        end1 = end2
    else:   
        totalLength += abs(end1 - start1)
        start1, end1 = start2, end2
 
print(totalLength + abs(end1 - start1))
