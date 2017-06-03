import time
leastValue = -1

def FillTree(b):
    i = len(b) - 2
    while (i >= 1):
        parent = (i - 1)//2
        if (b[i] >= b[i+1]):
            b[parent] = b[i]
        else:
            b[parent] = b[i+1]
        i -= 2
    print('filled')

def ExtractMax(b, numOfLeaves):
    indsOfMax = [];
    maxx = b[0]
    i = 0
    maxInd = len(b) - 1
    for i in range(numOfLeaves):
        if (b[maxInd - i] == maxx):
            b[maxInd - i] = leastValue
            indsOfMax.append(maxInd - i);
    
    for j in range(len(indsOfMax)):
        
        i = (indsOfMax[j] - 1)//2;
        while (i >= 0):
            child = 2*i + 1
            if (b[child] >= b[child + 1]):
                b[i] = b[child]
            else:
                b[i] = b[child + 1]
            i = (i - 1)//2
    ret = [maxx,len(indsOfMax)]
    return ret

def SelectionFromTree(a):
    b = [0 for i in range(len(a) + len(a) - 1)]
    for i in range(len(a)):
        b[len(a)-1+i] = a[i]
    FillTree(b)
    i = len(a) - 1
    while (i >= 0):
        ret = ExtractMax(b,len(a))
        for j in range(ret[1]):
            a[i] = ret[0]
            i -= 1
            
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
filenames = ['data256.txt', 'data512.txt', 'data1024.txt', 'data2048.txt',
         'data4096.txt','data8192.txt']
for filename in filenames:
    k = LoadFile(filename)
    tit1=time.time()
    SelectionFromTree(k)
    tit2=time.time()
    print('For ',filename,' = ',tit2-tit1)
