import matplotlib.pyplot as plt
from math import log2

sem_heap_x = []
sem_heap_y = []
com_heap_x = []
com_heap_y = []

log_x = []
log_y = []

for x in range(1,1100):
    log_x.append(x)
for i in log_x:
    i = log2(i)
    log_y.append(i)



with open("output.txt","r") as arquivo:
    for line in arquivo:
        line = line.split()
        #print("({},{}),({},{})".format(line[0],line[1],line[0],line[2]))

        sem_heap_x.append(int(line[0]))
        sem_heap_y.append(int(line[1]))

        com_heap_x.append(int(line[0]))
        com_heap_y.append(int(line[2]))

plt.title("Enqueue/Insert - FP com Heap vs FP sem Heap ")
plt.xlabel('Prioridade')
plt.ylabel('Numero de Comparações')

plt.grid(True, 'major', 'both')

plt.plot(sem_heap_x,sem_heap_y,'.',color='blue',label='Sem heap')
plt.plot(com_heap_x,com_heap_y,'.',color='orange',label='Com heap')
plt.plot(log_x,log_y,color='red',label='O(log2(n))')


plt.legend()

plt.show()

