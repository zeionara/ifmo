'Программа которая строит таблицу инверсий для перестановки
k = [3,6,5,2,4,8,7,1]
inv = k.copy()
strr = ''
for i in range(0,len(k)):
    current = 0
    for j in range(0,i):
        if k[j]>k[i]:
            current+=1
    inv[k[i]-1] = current
print(inv)
