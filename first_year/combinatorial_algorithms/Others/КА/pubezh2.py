#####Third lab
###Pseudocode for Counting Sort
# C - array for count each element with size k
# x - unsorted array with elements [1;k] and size n
# B - sorted array with same size as x 
for i = 1...k
    C[k] = 0
for i = 1...n
    C[x[i]] += 1
for i = 1...k
    C[i] = C[i] + C[i-1]
for i = n...1
    B[C[x[i]]] = x[i]
    C[x[i]] -= 1
###Pseudocode for Bucket Sort
# B - array of buckets (each bucket is a structure of data like array, list, etc) with size n
# A - unsorted array with elements [a,b]
# method concat concatenates all lists in one from list of lists
B = new List<List<int>>(n)
for i = 1...length(A)
    B[floor(n*(A[i]-a)/(b-a))].append(A[i])
for i = 1...n
    B[i].sort()
return B.concat()
###Pseudocode for Radix Sort (MSD)
# B - array of buckets in each of which the same value of some radix
# A - unsorted array
# method getradix returns some radix of value
def radixsort(A,numofradix)
    B = new List<List<int>>(n);
    if (length(A) <= 1):
        return A
    for i = 1...length(A)
        B[getradix(A[i],numofradix)].append(A[i])
    for i = 1...n
        B[i] = radixsort(B[i],numofradix+1)
    return B.concat()
#####Fiveth lab
### Pseudocode for chaining hash-table
def Remove(htable, x):
    node = Find(htable, x)
    if (node.previous != Null)
        prev = node.previous
        prev.next = node.next
    else
        htable[hash(x)] = node.next
        
def Find(htable, x):
    node = htable[hash(x)]
    while (node != Null) && (node.key != x)
        node = node.next
    return node
    
def Add(htable, x):
    htable[hash(x)].addToBegin(x)

### Pseudocode for open-addressing hash-table

def Add(htable, x):
    i = 0
    position = h1(x)
    while (htable[position] != DELETED) || (htable[position] != NULL):
        position = (h1(x) + i*h2(x)) mod m
    htable[position] = x

def Remove(htable, x):
    i = 0
    position = h1(x)
    while (htable[position] != x) && (htable[position] != Null):
        position = (h1(x) + i*h2(x)) mod m
    htable[position] = DELETED
    
def Find(htable, x):
    i = 0
    position = h1(x)
    while (htable[position] != x) && (htable[position] != Null):
        position = (h1(x) + i*h2(x)) mod m
    return position
    
    

    
