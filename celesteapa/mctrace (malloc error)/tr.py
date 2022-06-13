import matplotlib.pyplot as plt
import numpy as np

f = open('output.txt', 'r')
lines=f.readlines()
val_tr = open('Traccia_confron.txt', 'r')
l=val_tr.readlines()

arr=[]
for x in range(0, 99):   
	arr.append(int(lines[x]))
plt.hist(arr, bins=30, edgecolor="w")
plt.axvline(int(l[0]), label='traccia', c='r')
plt.axvline(int(l[1]), label='traccia+varianza', c='g')
plt.axvline(int(l[2]), label='traccia-varianza', c='b')
plt.xticks(np.arange(min(arr), max(arr), 8000.0))
  
plt.gca().set(title='M=5', xlabel='Tracce', ylabel='Frequenze')
plt.savefig('MCT5.png')
plt.close()

arr=[]
for x in range(100, 199):   
	arr.append(int(lines[x]))
plt.hist(arr, bins=30, edgecolor="w")
plt.axvline(int(l[0]), label='traccia', c='r')
plt.axvline(int(l[3]), label='traccia+varianza', c='g')
plt.axvline(int(l[4]), label='traccia-varianza', c='b')
plt.xticks(np.arange(min(arr), max(arr), 8000.0))
    
plt.gca().set(title='M=10', xlabel='Tracce', ylabel='Frequenze')
plt.savefig('MCT10.png')
plt.close()

arr=[]
for x in range(200, 299):   
	arr.append(int(lines[x]))
plt.hist(arr, bins=30, edgecolor="w")
plt.axvline(int(l[0]), label='traccia', c='r')
plt.axvline(int(l[5]), label='traccia+varianza', c='g')
plt.axvline(int(l[6]), label='traccia-varianza', c='b')

plt.xticks(np.arange(min(arr), max(arr), 8000.0))
plt.gca().set(title='M=25', xlabel='Tracce', ylabel='Frequenze')
plt.savefig('MCT25.png')
plt.close()

arr=[]
for x in range(300, 399):   
	arr.append(int(lines[x]))
plt.hist(arr, bins=30, edgecolor="w")
plt.axvline(int(l[0]), label='traccia', c='r')
plt.axvline(int(l[7]), label='traccia+varianza', c='g')
plt.axvline(int(l[8]), label='traccia-varianza', c='b')

plt.xticks(np.arange(min(arr), max(arr), 8000.0))
plt.gca().set(title='M=100', xlabel='Tracce', ylabel='Frequenze')
plt.savefig('MCT100.png')
plt.close()
