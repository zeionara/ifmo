import random
numberofelements = 8192
i = 0

f = open('data8192.txt','w')
f.write(str(numberofelements)+'\n')
while i<numberofelements:
    f.write(str(numberofelements-i)+'\n')
    i=i+1
f.close()
