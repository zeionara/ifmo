import time;
#MergeSort
#Merge - unions two arrays in one and return it
def Merge(a,b):
    n = len(a)
    m = len(b)
    i = 0
    j = 0
    union = []
    #For each element in array with n+m elements
    for k in range(n+m):
        #If index out in first array write from second
        if i >= n:
            union.append(b[j])
            j+=1
        #If index out in second array write from first
        elif j>= m:
            union.append(a[i])
            i+=1
        #If index not out, compare two values from arrays
        elif (a[i]<b[j]):
            union.append(a[i])
            i+=1
        else:
            union.append(b[j])
            j+=1
    return union

#Mergesort - sorting array with using merge parts
def MergeSort(a):
    #If array simple, then return it
    if len(a) <= 1:
        return a
    #Else merge sorted by merge two equals by length parts
    return Merge(MergeSort(a[:len(a)//2]),MergeSort(a[len(a)//2:]))

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
    MergeSort(k)
    tit2=time.time()
    print('For ',filename,' = ',tit2-tit1)
