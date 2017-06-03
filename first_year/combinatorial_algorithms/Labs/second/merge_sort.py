import time

def Merge (a,b):
    N = len(a)
    M = len(b)
    i = 0
    j = 0
    c = []
    for k in range(M+N):
        if (i == N):
            c.append(b[j])
            j+=1
            continue
        if (j == M):
            c.append(a[i])
            i+=1
            continue
        if (a[i]<b[j]):
            c.append(a[i])
            i+=1
            continue
        c.append(b[j])
        j+=1
    return c

def MergeSort(a):
    if (len(a) == 1):
        return a
    return Merge(MergeSort(a[:len(a)//2]),MergeSort(a[len(a)//2:]))

f = open('data256.txt')
j=0
k = []

numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1 = time.time()
k = MergeSort(k)
tit2 = time.time()
print(k)
#print('For ',numberofelements,' values = ',tit2-tit1,' sec');

