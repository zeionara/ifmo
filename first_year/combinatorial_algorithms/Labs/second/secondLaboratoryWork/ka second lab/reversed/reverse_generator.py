import random
numberofelements = 262144
i = 0

f = open('data262144.txt','w')
f.write(str(numberofelements)+'\n')
while i<numberofelements:
    f.write(str(numberofelements-i)+'\n')
    i=i+1
f.close()
