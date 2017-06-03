import random
minrandom = 0
maxrandom = 262144
numberofelements = maxrandom
i = 0

f = open('data262144.txt','w')
f.write(str(numberofelements)+'\n')
while i<numberofelements:
    f.write(str(random.randint(minrandom,maxrandom))+'\n')
    i=i+1
f.close()
