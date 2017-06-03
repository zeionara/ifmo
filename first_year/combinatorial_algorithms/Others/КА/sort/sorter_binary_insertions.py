import time
f = open('data4096.txt')
j=0
k = []

numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1=time.time()
for i in range(1,len(k)):
    if k[i-1]>k[i]:
        left = 0
        right = i - 1
        while True:
            mid = (left + right) // 2
            if k[mid]>k[i]:
                right = mid - 1
            else:
                left = mid + 1
            if left > right:
                break
        key = k[i]
        for j in reversed(range(left+1,i+1)):
            k[j] = k[j-1]
        k[left] = key
tit2=time.time()
print(tit2-tit1)
    
            
