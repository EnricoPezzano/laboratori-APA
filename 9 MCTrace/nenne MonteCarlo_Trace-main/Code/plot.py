import matplotlib 
matplotlib.use('AGG')     # per salvare il grafico su file senza passare da interfaccia grafica
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from scipy.stats import norm

f = open(" INSERIRE NOME FILE .txt", "r") #cambiare il nome del file a seconda del grafico

MCs = []
for i in f:
    MCs.append(int(i))

# print(MCs)

    
plt.hist(MCs)
plt.style.use('ggplot') 
plt.title('Istogramma media campionaria: M= INSERIRE VALORE M, run=100') #cambiare anche M
plt.grid(True)
plt.savefig('histogram_M= INSERIRE VALORE M .png') #anche qua
    
