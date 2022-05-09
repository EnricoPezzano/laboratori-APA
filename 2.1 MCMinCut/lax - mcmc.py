import random

# nodo di una lista
class Node:
	# constructor
	def __init__(self, data = None, next=None): 
		self.data = data
		self.next = next

# lista linkata con un singolo nodo
class LinkedList:
	def __init__(self):  
		self.head = None
  
	# inserimento in una lista linkata
	def insert(self, data):
		newNode = Node(data)
		if(self.head):
			current = self.head
			while(current.next):
				current = current.next
			current.next = newNode
		else:
			self.head = newNode	

	# Given a reference to the head of a list and a key,
	# delete the first occurrence of key in linked list
	def deleteNode(self, key):
         
		# Store head node
		temp = self.head
 
		# If head node itself holds the key to be deleted
		if (temp is not None):
			if (temp.data == key):
				self.head = temp.next
				temp = None
				return
 
		# Search for the key to be deleted, keep track of the
		# previous node as we need to change 'prev.next'
		while(temp is not None):
			if temp.data == key:
				break
			prev = temp
			temp = temp.next
 
		# if key was not present in linked list
		if(temp == None):
			return
	 
		# Unlink the node from linked list
		prev.next = temp.next
	 
		temp = None
		
  
	# stampa della lista
	def printLL(self):
		current = self.head
		print("[", end ="")
		while(current):
			if(current.next):
				print(current.data, end =", ")
			else:
				print(current.data, end ="")
			current = current.next
		print("]")


def printGraph(graph):
	for key in graph:
			print ("Nodo: " + key + " - AdjList: ", end ="")
			graph[key].printLL()

def genFritsch():
	Fritsch = {}

	# nodo A
	LA = LinkedList()
	LA.insert('B')
	LA.insert('C')
	LA.insert('D')
	LA.insert('H')
	LA.insert('I')
	# LA.printLL()
	Fritsch['A'] = LA

	# nodo B
	LB = LinkedList()
	LB.insert('A')	
	LB.insert('D')
	LB.insert('E')
	LB.insert('H')
	# LB.printLL()
	Fritsch['B'] = LB

	# nodo C
	LC = LinkedList()
	LC.insert('A')	
	LC.insert('D')
	LC.insert('F')
	LC.insert('I')
	# LC.printLL()
	Fritsch['C'] = LC

	# nodo D
	LD = LinkedList()
	LD.insert('A')	
	LD.insert('B')
	LD.insert('C')
	LD.insert('E')
	LD.insert('F')
	# LD.printLL()
	Fritsch['D'] = LD

	# nodo E
	LE = LinkedList()
	LE.insert('B')	
	LE.insert('D')
	LE.insert('F')
	LE.insert('H')
	LE.insert('G')
	# LE.printLL()
	Fritsch['E'] = LE

	# nodo F
	LF = LinkedList()
	LF.insert('C')	
	LF.insert('D')
	LF.insert('E')
	LF.insert('G')
	LF.insert('I')
	# LF.printLL()
	Fritsch['F'] = LF

	# nodo G
	LG = LinkedList()
	LG.insert('E')	
	LG.insert('F')
	LG.insert('H')
	LG.insert('I')
	# LG.printLL()
	Fritsch['G'] = LG

	# nodo H
	LH = LinkedList()
	LH.insert('A')	
	LH.insert('B')
	LH.insert('E')
	LH.insert('G')
	LH.insert('I')
	# LH.printLL()
	Fritsch['H'] = LH

	# nodo I
	LI = LinkedList()
	LI.insert('A')	
	LI.insert('C')
	LI.insert('F')
	LI.insert('G')
	LI.insert('H')
	# LI.printLL()
	Fritsch['I'] = LI

	return Fritsch


# conta i nodi in un grafo
def countNodes(graph):
	cnt = 0

	for key in graph:
		cnt = cnt + 1

	return cnt


# campiona un nodo dal grafo
def getRandNode(graph):
	n = random.randint(0, countNodes(graph)-1)

	count=0
	for elem in sorted(graph.keys()):
		if n==count:
			return elem
		else:
			count+=1

def countElem(adjList):
		counter = 0
		current = adjList.head
		while(current.next):
			counter = counter + 1
			current = current.next

		return counter+1


# campiono un nodo adiacente ad un nodo
def getRandAdjNode(graph, keyNode):
	n = random.randint(0, countElem(graph[keyNode])-1)

	current = graph[keyNode].head

	count=0
	while(n > count):
		current = current.next
		count = count + 1

	return current.data


# collasso i due nodi in un nodo solo
# unendo le liste di adiacenza ed eliminando da esse i riferimenti ai nodi stessi
def collapseNodes(graph, keyA, keyB):
	adjListAB = LinkedList()

	# inserisco nella nuova lista gli elementi della adjList di A
	current = graph[keyA].head
	while(current):
		# a patto che non sia uguale all'altro nodo
		if(current.data != keyB):
			adjListAB.insert(current.data)
		current = current.next

	# inserisco nella nuova lista gli elementi della adjList di B
	current = graph[keyB].head
	while(current):	
		if(current.data != keyA):
			adjListAB.insert(current.data)
		current = current.next


	# sostituisco in tutte le altre liste di adiacenza i nodi A e B con il nodo AB
	for elem in sorted(graph.keys()):
		current = graph[elem].head
		while(current):	
			if(current.data == keyA):
				graph[elem].deleteNode(keyA) # levalo dalla lista di adiacenza
				graph[elem].insert(keyA + keyB) # inserisci il nuovo

			if(current.data == keyB):
				graph[elem].deleteNode(keyB) # levalo dalla lista di adiacenza
				graph[elem].insert(keyA + keyB) # inserisci il nuovo

			current = current.next

	# rimuovo i due nodi dalla lista
	graph.pop(keyA)
	graph.pop(keyB)

	# aggiungo il nodo derivante dal nuovo join
	graph[keyA + keyB] = adjListAB
	
	# ne ritorno la chiave
	return (keyA + keyB)


# ottiene un taglio minimo 
def getMinCut(graph):
	# fino a quando il numero di nodi è maggiore di due
	while(countNodes(graph) > 2):
		# campiono un nodo
		keyRandNode = getRandNode(graph)
		# print("Nodo Estratto: " + keyRandNode) # DEBUG
		# campiono un nodo adiacente ad esso
		keyRandAdjNode = getRandAdjNode(graph, keyRandNode)
		# print("Nodo Adiacente Estratto: " + keyRandAdjNode) # DEBUG
		# collasso i due nodi in un nodo solo
		# unendo le liste di adiacenza ed eliminando da esse i riferimenti ai nodi stessi
		keyNewNode = collapseNodes(graph, keyRandNode, keyRandAdjNode)
		# printGraph(graph) # DEBUG

	# conto e ritorno quanti archi hanno i due nodi
	return countElem(graph[keyNewNode])

def main():
	print("Mincut - La Corte Lorenzo\n")
	# dichiara un dizionario (mincut, freq)
	cutsHT = {}

	# applica MCMinCut 10^5 volte
	nIter = 100000
	x = range(nIter)

	for run in x:
		if run == 0:
			print("Elaborazione della prima corsa su " + str(nIter))
		elif run % 10000 == 0:
			print("Elaborazione della " + str(run) + "esima corsa su " + str(nIter))
		# Genera il grafo di Fritsch 
		Fritsch = genFritsch()

		# printGraph(Fritsch) # DEBUG

		# ottieni un taglio minimo 
		mincut = getMinCut(Fritsch)

		# metti il taglio minimo nel dizionario (mincut, freq)
		# controlla se è già nel dizionario
		if mincut not in cutsHT:
			# se non è nel dizionario aggiungilo
			cutsHT[mincut] = 1

		else:
			# altrimenti aumentane la frequenza corrispondente
			cutsHT[mincut] = cutsHT[mincut] + 1

		# printGraph(Fritsch) # DEBUG

	# ordina il dizionario
	# prendi la minima chiave e guarda quante volte è uscita
	minMinCut = min(cutsHT.items(), key=lambda x: x[0]) 

	print("L'algoritmo termina con successo\n\nMinimo mincut: " + str(minMinCut[0]))
	print("Quante volte esce: " + str(minMinCut[1]))

	Fritsch = genFritsch() # rigenero il grafo per contarne i nodi

	# calcola la frequenza empirica facendo la divisione tra
	# la freq. di uscita del mincut minimo e il numero di iterazioni
	f = minMinCut[1] / nIter
	# confronta il risultato ottenuto con la stima p ≈ 2/n^2.
	p = 2/(countNodes(Fritsch)**2)

	print("La frequenza empirica del mincut è: " + str(f))
	print("La stima p ≈ 2/n^2 è: " + str(p))


main()