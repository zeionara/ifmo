import time
f = open('data256.txt')
j=0
k = []

numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1 = time.time()
for n in range(len(k)-1):
    minimum = n
    index = n + 1
    while index < len(k):
        if k[index] < k[minimum]:
            minimum = index
        index+=1
    t = k[n]
    k[n] = k[minimum]
    k[minimum] = t
    

tit2 = time.time()
print('For ',numberofelements,' values = ',tit2-tit1,' sec');

