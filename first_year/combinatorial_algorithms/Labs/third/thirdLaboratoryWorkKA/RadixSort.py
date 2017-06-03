def FindMax(a):
    maxx = 0;
    isWasMax = 0;
    for i in range(len(a)):
        if ((a[i] > maxx) or (isWasMax == 0)):
            isWasMax = 1
            maxx = a[i]
    return maxx

def RadixSort(a):
    b = []
    maxx = FindMax(a)
    radixes = 0
    while maxx > 0:
        maxx = maxx//10
        radixes += 1
    for k in range(radixes):
        for j in range(10):
            for i in range(len(a)):
                if (a[i]%10**(k+1)//10**k == j):
                    b.append(a[i])
        for j in range(len(a)):
            a[j] = b[j]
        b = []
    return a

print(5//10)
k = [55,5,22,3,3,3,3,33,2,1]
RadixSort(k)
print(k)
        
        
