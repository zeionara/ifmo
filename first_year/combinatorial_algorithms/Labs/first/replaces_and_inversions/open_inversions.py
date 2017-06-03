' Программа восстановления перестановки по таблице инверсий
k = [7,3,0,2,1,0,1,0]
strr = ''
for i in reversed(range(1,len(k)+1)):
    if (k[i-1] > len(strr)):
        strr = strr + str(i)
    else:
        strr = strr[:k[i-1]] + str(i) + strr[k[i-1]:]
print(strr)
