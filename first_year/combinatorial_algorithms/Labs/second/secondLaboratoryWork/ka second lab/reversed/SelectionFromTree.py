import time
leastValue = -1

def SiftUpTo(i,b):
    while (i < len(b)//2):
        child = 2*i + 1
        if (b[child] < b[child + 1]):
            child += 1
        if (b[child] < b[i]):
            break
        b[i],b[child] = b[child],b[i]
        i = child

def FillTree(b):
    i_counter = len(b) - 2
    while (i_counter >= 1):
        i = i_counter
        parent = (i - 1)//2
        if (b[i+1] > b[i]):
            i += 1
        if (b[i] < b[parent]):
            i_counter -= 2
            continue
        b[parent] = b[i]
        b[i] = leastValue
        SiftUpTo(i,b)
        i_counter -= 2

def ExtractMax(b):
    indsOfMax = [];
    maxx = b[0]
    b[0] = leastValue
    SiftUpTo(0,b)
    return maxx

def SelectionFromTree(a):
    b = [0 for i in range(len(a) + len(a) - 1)]
    for i in range(len(a)):
        b[len(a)-1+i] = a[i]
    FillTree(b)
    for i in range(len(a)):
        a[len(a) - 1 - i] = ExtractMax(b)
            
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
    SelectionFromTree(k)
    tit2=time.time()
    print('For ',filename,' = ',tit2-tit1)
