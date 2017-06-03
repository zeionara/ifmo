import time
import math
f = open('data8192.txt')
j=0
k = []
queue = []

def Append(q,v):
    q.append(v)
    k = len(q) - 1
    while (math.ceil(k/2 - 1) >= 0):
        p = math.ceil(k/2 - 1)
        if (q[p] <= q[k]):
            break
        q[p],q[k] = q[k],q[p]
        k = p

def Pop(q):
    element = q[0]
    q[0],q[len(q)-1] = q[len(q)-1],q[0]
    q.pop()
    Heapify(q,0,len(q))
    return element

def Heapify(q,k,n):
    while (k < n//2):
        child = 2*k + 1
        if (child < n-1):
            if (q[child] > q[child+1]):
                child += 1
        if (q[k] < q[child]):
            break
        q[k],q[child] = q[child],q[k]
        k = child


numberofelements = int(f.readline())
while j<numberofelements:
    i = int(f.readline())
    k.append(i)
    j=j+1

tit1 = time.time()
Append(queue,5)
Append(queue,3)
Append(queue,4)
Append(queue,2)
Append(queue,1)
Append(queue,0)
print(Pop(queue))
print(Pop(queue))
print(Pop(queue))
print(Pop(queue))
print(Pop(queue))
print(Pop(queue))
tit2 = time.time()
print(queue)

print('For ',numberofelements,' values = ',tit2-tit1,' sec');

