def FindMax(a):
    maxx = 0;
    isWasMax = 0;
    for i in range(len(a)):
        if ((a[i] > maxx) or (isWasMax == 0)):
            isWasMax = 1
            maxx = a[i]
    return maxx

def CountingSort(a):
    b = [0 for i in range(len(a))]
    maxx = FindMax(a)
    counts = [0 for i in range(maxx + 1)]
    for i in range(len(a)):
        counts[a[i]] += 1
        
    for i in range(1,maxx + 1):
        counts[i] += counts[i - 1]
        
    for i in reversed(range(len(a))):
        if (counts[a[i]] >= 1):
            b[counts[a[i]] - 1] = a[i]
            counts[a[i]] -= 1
    return b

k = [5,4,3,3,3,3,2,1,0]
print(CountingSort(k))
