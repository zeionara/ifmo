import time
def Merge(series):
    lengths = []
    indexes = []
    numberofsteps = 0
    merging = []
    for s in series:
        numberofsteps+=len(s)
        lengths.append(len(s))
        indexes.append(0)
    for i in range(numberofsteps):
        minimum = 0
        isminimumset = 0
        for j in range(len(series)):
            if (indexes[j] < lengths[j]):
                if (isminimumset == 0):
                    isminimumset = 1
                    minimum = series[j][indexes[j]]
                    jmin = j
                elif (series[j][indexes[j]] < minimum):
                    minimum = series[j][indexes[j]]
                    jmin = j
        indexes[jmin]+=1
        merging.append(minimum)
    return merging

def DMergeSort(a,d):
    if len(a)<=1:
        return a
    series = []
    for i in range(d):
        series.append(DMergeSort(a[i*len(a)//d:(i+1)*len(a)//d],d))
    return Merge(series)

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
        k = DMergeSort(k,d)
        tit2=time.time()
        print('For ',filename,' = ',tit2-tit1)
    
