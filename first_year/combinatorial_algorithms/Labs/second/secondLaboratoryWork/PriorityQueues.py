#Priority Queue
#SiftingUp - element with index i will elevate up to it's position in heap
def SiftUp(k,i):
    #Until element has parent
    while (i >= 1):
        #Definite index of parents
        parent = (i-1)//2
        #If necessary, element goes up
        if k[parent] >= k[i]:
            break;
        k[parent],k[i] = k[i],k[parent]
        #Continue going up
        i = parent

#SiftingDown - element with index i will go down in the heap
def SiftDown(k,i):
    #Until element has children
    while (i < len(k)//2):
        #Definite left child
        child = i*2 + 1
        #If element has right child compare children
        if (child < len(k) - 1):
            if (k[child] < k[child + 1]):
                child += 1
        #If necessary swap parent and child
        if (k[child] < k[i]):
            break;
        k[child],k[i] = k[i],k[child]
        #Continue sifting down
        i = child

#Append Element - appending new value to the end and Sift it Up
def AppendElement(k,value):
    #Append to the end of queue
    k.append(value)
    #Sifting Up appended value
    SiftUp(k,len(k)-1)

#Extracting Max value and sift down last from root
def ExtractMax(k):
    #Save maximal
    mx = k[0]
    #Throw out maximal from heap
    k[0],k[len(k)-1] = k[len(k)-1],k[0]
    k.pop()
    #Sifting down last entry
    SiftDown(k,0)
    print(" Maximal = ",mx)

#Building heap from array
def HeapBuilder(k):
    #SiftDown all items which have childs
    for i in reversed(range(0,len(k)//2)):
        SiftDown(k,i)
        print(k)
#General
print(k)

        
