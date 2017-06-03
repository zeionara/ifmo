import random
minrandom = 0
maxrandom = 100
numberofelements = 8192
i = 0

f = open('data8192.txt','w')
f.write(str(numberofelements)+'\n')
while i<numberofelements:
    f.write(str(random.randint(minrandom,maxrandom))+'\n')
    i=i+1
f.close()
