#QuickSort
import random;
import time
#Partition - simpliest function for cutting array
def Partition(a,p,r):
    #Last value in array saves as key for compareing 
    x = a[r]
    # i - last index of set of elements, which less than or equals to key
    i = p - 1
    # j - variable for viewing elements in array
    j = p
    # For each element excluding last
    while (j < r):
        # if element less than or equals to key
        if a[j] <= x:
            #add it to the set
            i+=1
            a[i],a[j] = a[j],a[i]
        j+=1
    #Replace last element to the space between two parts
    a[i+1],a[r] = a[r],a[i+1]
    return i+1

#Randomized partiiton for more effictive selection
def RandomPartition(a,p,r):
    #Select random index in array and swap it with last
    x = random.randrange(p,r+1)
    a[x],a[r] = a[r],a[x]
    #Call standard partition
    i = Partition(a,p,r)
    return i

#If unique elements not so much, it's rational to call this method instead basical or randomized partition
def FewUniqueElementsPartition(a,p,r):
    #It is container for two returned items
    returned = []
    #Save last as key
    x = a[r]
    #That index will show, where begins zone (>)
    i = p
    j = p
    #That index will show, where ends zone (>)
    e = r
    while (j < e):
        #If found element less than key, placing it to zone (<)
        if a[j] < x:
            a[i],a[j] = a[i],a[j]
            j+=1
            i+=1
        #If found element equals to key, placing it to zone (=)
        elif a[j] == x:
            e-=1
            a[j],a[e] = a[e],a[j]
        #Zone (>) will creates by itself
        else:
            j+=1
    #Select interval with minimal size between zone (<) and zone (=)
    if (r - e + 1 < e - i):
        size = r - e + 1
    else:
        size = e - i
    #Replace equals to center and zone (>) to end
    for k in range(1,size+1):
        a[i+k-1],a[r-k+1] = a[i+k-1],a[r-k+1]
    returned.append(i-1)
    returned.append(r-e+i)
    return returned

#Alternative version of procedure Partition,
#which effective for not sorted arrays
def AlternativePartition(a,p,r):
    print(a)
    # Index lo indicates, where ended zone (<)
    lo = p
    # Index hi indicates, where begins zone (>=)
    hi = r
    # Select first element as divider
    x = a[p]
    while (True):
        # Searching last element < x and move it to zone (<)
        while (a[hi] >= x):
            hi -= 1
            if hi <= lo:
                break
        if hi <= lo:
                break
        a[hi],a[lo] = a[lo],a[hi]
        # Searching first element >= x and move it to zone (<=)
        lo += 1
        while (a[lo] < x):
            lo += 1
            if hi <= lo:
                break
        if hi <= lo:
            break
        a[hi],a[lo] = a[lo],a[hi]
    print(a)
    return lo

#Basic version of QuickSort
def QuickSort(a,p,r):
    #If we have correct part of array, divide it on two parts and sort them
    #singularly
    if (p<r):
        i = Partition(a,p,r)
        QuickSort(a,p,i-1)
        QuickSort(a,i+1,r)

#Version of QuickSort with calling random version of Partition
def RandomQuickSort(a,p,r):
    #If we have correct part of array, divide it on two parts and sort them
    #singularly
    if (p<r):
        i = RandomPartition(a,p,r)
        QuickSort(a,p,i)
        QuickSort(a,i+1,r)

#Version of QuickSort with calling special version of Partition for few unique elements in array
def FewUniqueElementsQuickSort(a,p,r):
    #If we have correct part of array, divide it on two parts and sort them
    #singularly
    if (p<r):
        returned = FewUniqueElementsPartition(a,p,r)
        QuickSort(a,p,returned[0])
        QuickSort(a,returned[1],r)

def AlternativeQuickSort(a,p,r):
    if (p<r):
        i = AlternativePartition(a,p,r)
        AlternativeQuickSort(a,p,i-1)
        AlternativeQuickSort(a,i+1,r)

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
    QuickSort(k,0,len(k)-1)
    tit2=time.time()
    print('For ',filename,' = ',tit2-tit1)


