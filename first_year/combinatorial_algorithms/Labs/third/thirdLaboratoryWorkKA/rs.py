def FindMax(a):
    maxx = 0
    isWasMax = 0
    for i in a:
        if (i > maxx):
            maxx = i
        elif (isWasMax == 0):
            isWasMax = 1
            maxx = i
    return maxx

def RadixSort(a):
    bina = []
    maxx = FindMax(a)
    lenOfMaxx = len(bin(maxx)) - 2
    for i in a:
        bini = bin(i)[2:]
        if (len(bini) < lenOfMaxx):
            for j in range(lenOfMaxx - len(bini)):
                bini = '0' + bini
        bina.append(bini)
    print(bina)

RadixSort([1,2,3,4,5])
    
    
