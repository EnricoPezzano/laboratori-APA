# 2022:
# Genera il grafo di Fritsch (che trovi nelle note) con 9 vertici e 21 archi e 
# verifica la frequenza empirica ^p con la quale ottieni un taglio minimo applicando 
# MCMinCut 10^5 volte. --- Utilizza ^p per calcolare il numero di run R necessari per 
# ottenere il taglio minimo con una probabilità del 99,9%

# output: 
# {8: 225934, 7: 191365, 9: 102495, 4: 22957, 10: 63960, 13: 9257, 12: 18848, 11: 33451, 5: 30195, 14: 1538}
# Il taglio minimo è  4
# la frequenza empirica  0.22957

# LF:
from random import choice
def stamp(g, i=0):
   for key, value in g.items():
      print(str(key)+' -->  ', str(value)+'\n')

def merge_vertices(g,u,v,l):
   ulist=g[u]+g[v]
   ulist.remove(u)
   ulist.remove(v)
   g.pop(u)
   g.pop(v)

   g[u+v]=ulist
   for k, val in g.items():
      if u in val or v in val:
            g[k] = [x if x!=u and x!=v else u+v for x in val]
#sistemo grafo
   for k, val in g.items():
      new_list = []
      for item in val:
         if k not in item :
            new_list.append(item)
      g[k] = new_list

#conto elementi
n_run = 100000
my_list = []
contator = 0

#itero per 100000 volte
for _ in range(num):
   #creazione del grafo
   graph = {
				"A" : ["B", "C","D","H","I"],
				"B" : ["C", "E", "A","G","I"],
				"C" : ["A","B","D","E"],
				"D" : ["C", "A","H","F","E"],
				"E" : ["B", "C","G","F","D"],
				"F" : ["D", "E","H","G","I"],
				"G" : ["I", "F","E","B"],
				"H" : ["I", "D","F","A"],
				"I" : ["B", "A","H","G","F"]
   }
   #applico MCMinCut
   while len(graph)>2:
      u = choice(list(graph.keys()))
      v=choice(graph[u])
      merge_vertices(graph,u,v,list)
      n=0
      for k, val in graph.items():
         n=len(val)
      my_list.append(n)



#calcolo delle occorrenze e della frequenza empirica
occ={}
for y in my_list:
    if y in occ:
        occ[y]+=1
    else:
        occ[y] = 1

print(occ)
print("Il taglio minimo è ", min(occ.keys()))
print("la frequenza empirica ", occ[min(occ.keys())]/num)