import time

#SiftDown - element, which has index i, moves down in tree to find it's position
def SiftDown(a,i,n,d):
    # For each element in tree, under element with index i
    while (i <= (n-1)//d):
        # Compare childs and choose greatest
        child = i*d + 1
        for j in range(2,d+1):
            if (i*d + j <= n-1):
                if a[child] < a[i*d + j]:
                    child = i*d + j
        # If it necessary, swap selected child and current element
        if (child > n-1):
            break
        if a[child] < a[i]:
            break
        a[child],a[i] = a[i],a[child]
        # Continue sifting down
        i = child

#HeapSort - sorting array with using heap, which builds by SiftDown
def HeapSort(k,d):
    #Creating Heap for O(n)
    for i in reversed(range(0,(len(k)-2)//d+1)):
        SiftDown(k,i,len(k),d)
    #Sorting array (i but not i+1 means that k[i] we already trow out from heap)
    for i in reversed(range(0,len(k))):
        k[i],k[0] = k[0],k[i]
        SiftDown(k,0,i,d)

#Loading data
k = [10,9,8,7,6,5,4,3,2,1,0]
def LoadFile(filename):
    f = open(filename)
    j=0
    numberofelements = int(f.readline())
    while j<numberofelements:
        i = int(f.readline())
        k.append(i)
        j=j+1

#General
filenames = ['data8192.txt', 'data16384.txt', 'data32768.txt', 'data65536.txt',
         'data131072.txt','data262144.txt']
#for filename in filenames:
LoadFile('data256.txt')
tit1=time.time()
HeapSort(k,15)
print(k)
tit2=time.time()
print('For ',filename,' = ',tit2-tit1)


