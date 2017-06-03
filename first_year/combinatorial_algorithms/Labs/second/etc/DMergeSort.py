import time
import math
def SiftUp(k,i):
    while (i >= 1):
        parent = (i-1)//2
        if k[parent] <= k[i]:
            break;
        k[parent],k[i] = k[i],k[parent]
        i = parent

def SiftDown(k,i):
    while (i < len(k)//2):
        child = i*2 + 1
        if (child < len(k) - 1):
            if (k[child] < k[child + 1]):
                child += 1
        if (k[child] < k[i]):
            break;
        k[child],k[i] = k[i],k[child]
        i = child

def ExtractMin(k):
    mn = k[0]
    k[0],k[len(k)-1] = k[len(k)-1],k[0]
    k.pop()
    SiftDown(k,0)
    return mn

def AppendElement(k,value):
    k.append(value)
    SiftUp(k,len(k)-1)

def Merge(series):
    lengths = []
    indexes = []
    numberofsteps = 0
    merging = []
    for s in series:
        numberofsteps+=len(s)
        lengths.append(len(s))
        indexes.append(0)
    tree = []
    merged = []
    for i in range(len(series)):
        if (lengths[i] > 0):
            AppendElement(tree,series[i][0])
            indexes[i] += 1
    for i in range(numberofsteps):
        mn = ExtractMin(tree)
        merged.append(mn)
        numOfS = mn[1]
        if (indexes[numOfS] < lengths[numOfS]):
            AppendElement(tree,series[numOfS][indexes[numOfS]])
            indexes[numOfS] += 1
    return merged
        
def DMergeSort(a,p):
    print(a)
    numOfS = -1
    if len(a)<=1:
        return a
    if (type(a[0]) == type([])):
        print('a 0 -----',a[0])
        numOfS = a[0][1]
        for i in range(len(a)):
            a[i] = a[i][0]
    print(a)
    series = []
    for i in range(p):
        series.append([])
    i = 0
    while (i < len(a)):
        print(i,i//p,len(series))
        series[i%p].append([a[i],i%p])
        i += 1
    for s in series:
        print('series before merging = ',series)
        s = DMergeSort(s,p)
        print('series after merging = ',series)
    print(series)
    if (numOfS > -1):
        
        merged = Merge(series)
        b = []
        
        for i in range(len(a)):
            merged[i] = [merged[i][0],numOfS]
        return merged
    print('->>>')
    print(series)
    return Merge(series)

#Loading data
k = []
def LoadFile(filename):
    k = []
    f = open(filename)
    j=0
    numberofelements = int(f.readline())
    while j<numberofelements:
        i = int(f.readline())
        k.append(i)
        j=j+1
    return k

#General
#tit1=time.time()
k = [7,6,5,4,3,2,1]
k = DMergeSort(k,3)
print(k)
#tit2=time.time()
#print('For ',filename,' = ',tit2-tit1)
    
