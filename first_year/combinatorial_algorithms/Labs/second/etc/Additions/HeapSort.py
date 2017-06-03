import time

#SiftDown - element, which has index i, moves down in tree to find it's position
def SiftDown(a,i,n):
    # For each element in tree, under element with index i
    while (i < n//2):
        # Choose left child
        child = i*2 + 1
        # If has right child
        if (child < n - 1):
            # Compare right and left child and choose greatest
            if (a[child] < a[child + 1]):
                child += 1
        # If it necessary, swap selected child and current element
        if a[child] < a[i]:
            break
        a[child],a[i] = a[i],a[child]
        # Continue sifting down
        i = child

#HeapSort - sorting array with using heap, which builds by SiftDown
def HeapSort(k):
    #Creating Heap for O(n)
    for i in reversed(range(0,len(k)//2)):
        SiftDown(k,i,len(k))
    #Sorting array (i but not i+1 means that k[i] we already trow out from heap)
    for i in reversed(range(0,len(k))):
        k[i],k[0] = k[0],k[i]
        SiftDown(k,0,i)

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
filenames = ['data8192.txt', 'data16384.txt', 'data32768.txt', 'data65536.txt',
         'data131072.txt','data262144.txt']
for filename in filenames:
    k = LoadFile(filename)
    tit1=time.time()
    HeapSort(k)
    tit2=time.time()
    print('For ',filename,' = ',tit2-tit1)


