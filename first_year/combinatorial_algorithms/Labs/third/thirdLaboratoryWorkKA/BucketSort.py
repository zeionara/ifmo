import math;
def FindMax(a):
    maxx = 0;
    isWasMax = 0;
    for i in range(len(a)):
        if ((a[i] > maxx) or (isWasMax == 0)):
            isWasMax = 1
            maxx = a[i]
    return maxx

def InsertionSort(a):
    for i in range(1,len(a)):
        key = a[i]
        j = i - 1
        while ((j >= 0) and (a[j] > key)):
            a[j+1] = a[j]
            j -= 1
        a[j + 1] = key

def BucketSort(a):
    b = []
    buckets = [[] for i in range(len(a))]
    maxx = FindMax(a)
    radixes = 0
    while maxx > 0:
        maxx = maxx//10
        radixes += 1
    for i in range(len(a)):
        buckets[math.ceil((a[i]/10**radixes)*len(a))].append(a[i])
    for i in range(len(a)):
        InsertionSort(buckets[i])
        for j in range(len(buckets[i])):
            b.append(buckets[i][j])
    return b
    
k = [55,5,22,3,3,3,3,33,2,1]

print(BucketSort(k))
        
        
