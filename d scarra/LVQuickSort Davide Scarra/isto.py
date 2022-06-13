import matplotlib.pyplot as plt
import numpy as np

f = open('output.txt', 'r')

numBin = [50]

for binCount in numBin:
  val = []
  f.seek(0)
  for line in f.readlines():
    val.append(int(line))
  #dopo aver creato l'array contenente i valori vado a creare l'istogramma
  N, bins, patches = plt.hist(val, bins=binCount, edgecolor='white')
  patches[12].set_facecolor('r')
  plt.gca().set(title='LasVegasQuickSort', xlabel='Confronti', ylabel='Frequenza')
  plt.savefig(f'Hist.png')
  plt.close()
  
  weights = np.ones_like(val)/float(len(val)) #normalizzo l'istogramma
  N, bins, patches = plt.hist(val, weights=weights, bins=binCount, edgecolor='white')
  patches[12].set_facecolor('r')
  plt.gca().set(title='LasVegasQuickSort', xlabel='Confronti', ylabel='Frequenza')
  plt.savefig(f'NormHist.png')
  plt.close()