import time

def Heapify (a,k,n):
    while (k < n//2):
        child = 2*k + 1
        if (child < n-1):
            if (a[child] < a[child + 1]):
                child += 1
        if (a[k] >= a[child]):
            break
        a[k],a[child] = a[child],a[k]
        k = child

def HeapSort(a):
    for i in reversed(range(0,len(a)//2)):
        Heapify(a,i,len(a))
    for i in reversed(range(1,len(a))):
        a[i],a[0] = a[0],a[i]
        Heapify(a,0,i)

f = open('data8192.txt')
j=0
k = []

numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1 = time.time()
HeapSort(k)
tit2 = time.time()

print('For ',numberofelements,' values = ',tit2-tit1,' sec');

