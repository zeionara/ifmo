import time
f = open('data8192.txt')
j=0
k = []

numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1=time.time()
for i in range(1,len(k)):
    key = k[i]
    j = i - 1
    while j >= 0 and k[j] > key:
        k[j+1] = k[j]
        j = j-1
    k[j+1] = key
tit2=time.time()
print(tit2-tit1)
    
            
