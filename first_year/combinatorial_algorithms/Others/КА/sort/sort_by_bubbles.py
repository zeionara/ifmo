import time
f = open('data8192.txt')
j=0
k = []

numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1 = time.time()
for n in reversed(range(len(k))):
        for m in range(1, n + 1):
            if k[m-1] > k[m]:
                k[m], k[m-1] = k[m-1], k[m]
tit2 = time.time()
print('For ',numberofelements,' values = ',tit2-tit1,' sec');

