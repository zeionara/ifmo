#MergeSort
#Merge - unions two arrays in one and return it
def Merge(a,b):
    n = len(a)
    m = len(b)
    i = 0
    j = 0
    union = []
    #For each element in array with n+m elements
    for k in range(n+m):
        #If index out in first array write from second
        if i >= n:
            union.append(b[j])
            j+=1
        #If index out in second array write from first
        elif j>= m:
            union.append(a[i])
            i+=1
        #If index not out, compare two values from arrays
        elif (a[i]<b[j]):
            union.append(a[i])
            i+=1
        else:
            union.append(b[j])
            j+=1
    return union

#Mergesort - sorting array with using merge parts
def MergeSort(a):
    #If array simple, then return it
    if len(a) <= 1:
        return a
    #Else merge sorted by merge two equals by length parts
    return Merge(MergeSort(a[:len(a)//2]),MergeSort(a[len(a)//2:]))
