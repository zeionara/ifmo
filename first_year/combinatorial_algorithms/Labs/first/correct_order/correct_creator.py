import random
numberofelements = 256
i = 0

f = open('data256.txt','w')
f.write(str(numberofelements)+'\n')
while i<numberofelements:
    f.write(str(i)+'\n')
    i=i+1
f.close()
