import matplotlib.pyplot as plt
import numpy as np


x,y=np.loadtxt('las.txt', delimiter='\t', unpack='True')
val=np.loadtxt('valoremed.txt', unpack='True')
x_w=np.empty(x.shape)
x_w.fill(1/x.shape[0])

plt.figure(1)
plt.hist(x, bins=50, weights=x_w, histtype='bar', rwidth=0.8, color='b')
plt.annotate("valore medio", xy=(val,0.07), xytext=(val+1000,0.08), arrowprops={"facecolor":"r","shrink":0.05})

plt.title('LasVegas')
plt.xlabel('x')
plt.ylabel('y')
plt.show()

