import time

def SiftDown(a,n,i,d):
    while (i <= (n-2)//d):
        child = i*d + 1
        maxChild = a[child]
        for j in range(1,d):
            nextChild = i*d+1+j
            if (nextChild <= n-1):
                if (a[nextChild]>a[child]):
                    child = nextChild
                    maxChild = a[child]
        if (a[child] < a[i]):
            break;
        a[child],a[i] = a[i],a[child]
        i = child

def DHeapSort(a,d):
    if d<2:
        return
    for i in reversed(range(0,(len(a)-2)//d+1)):
        SiftDown(a,len(a),i,d)
    
    for i in reversed(range(0,len(a))):
        a[0],a[i] = a[i],a[0]
        SiftDown(a,i,0,d)

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
for d in range(3,7):
    print('For d = ',d)
    for filename in filenames:
        k = LoadFile(filename)
        tit1=time.time()
        DHeapSort(k,d)
        tit2=time.time()
        print('For ',filename,' = ',tit2-tit1)



