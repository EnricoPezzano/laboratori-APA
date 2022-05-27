#include "graph.h"

// Mezzo arco, non tiene il nodo sorgente
struct halfEdgeNode {
  vertexNode *vertPtr;
  halfEdgeNode* next=NULL; // puntatore al mezzo arco successivo
};

// Un vertice è caratterizzato dall'etichetta, il puntatore alla lista dei vertici adiacenti, il puntatore al prossimo vertice e un booleano che indica se il nodo è già stato visitato (serve per implementare il cammino tra due città
struct vertexNode {
  string name;    
  halfEdgeNode *adjList;
  vertexNode *next=NULL;
  bool visited;
};

halfEdgeNode* emptyHalfEdgeNode = NULL;

// Ritorna il puntatore al vertice avente label "l" (se esiste)
vertexNode* getVertex(string l, Graph& g) {
  for (Graph v = g; v != NULL; v = v->next) {
   if (v->name == l) return  v;
  }
  return NULL; 
}

// Ritorna true se il vertice e' presente nel grafo
bool isVertexInGraph(string l, Graph& g) {
  return (getVertex(l, g)!=NULL);
}

// Ritorna true se l'arco e' presente nel grafo
bool isEdgeInGraph(string from, string to, Graph& g) {
  vertexNode* vNode = getVertex(from, g);
  if (vNode == NULL) return false;
  for (halfEdgeNode* n = vNode->adjList; n != emptyHalfEdgeNode; n = n->next) {
    if (n->vertPtr->name == to ) return true;
  }
  return false;
}

// Aggiunge il "mezzo edge" alla lista di adiacenza
void addHalfEdge(string from, string to,Graph& g) {
  halfEdgeNode *e = new halfEdgeNode;
  e->vertPtr = getVertex(to, g);
  vertexNode* vNode = getVertex(from, g);
  if (vNode->adjList == emptyHalfEdgeNode) {
    vNode->adjList = e;
    e->next = emptyHalfEdgeNode;
  } else {
    e->next = vNode->adjList;
    vNode->adjList = e;
  }
}

// Restituisce il grafo vuoto
Graph createEmptyGraph() {
  return NULL;
}

// Aggiunge nuovo vertice con etichetta la stringa. Fallisce se gia' presente
bool addVertex(string l, Graph& g) {
  if (isVertexInGraph(l, g))
    return false;  // etichetta gia' presente
  // aggiungi nuovo vertice
  Graph v = new vertexNode;
  v->name = l;
  v->adjList = emptyHalfEdgeNode;
  v->visited = false;
  if (isEmpty(g)) {
    g = v;
    v->next = NULL;
  } else {
    v->next = g;
    g = v;
  }
  return true;
}

// Aggiunge un arco di peso "w" tra i nodi con etichetta "f" e "t"
bool addEdge(string from, string to, Graph& g) {
  // non permetto arco tra un nodo ed esso stesso
  if (from == to)
    return false;
  // entrambi i nodi devono gia' esistere nel grafo
  if (!isVertexInGraph(from, g) || !isVertexInGraph(to, g))
    return false;
  addHalfEdge(from, to, g);
  addHalfEdge(to, from, g);
  return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool isEmpty(Graph& g) { 
   return (g==NULL);
}

// stampa il grafo
void printGraph(Graph& g) {
  for (Graph v = g; v != NULL; v = v->next) {
    cout << v->name << ": ";
    printAdjList(v->name, g);
  }
}

// stampa la lista di adiacenza del nodo
void printAdjList(string l, Graph& g) {
    vertexNode* vNode = getVertex(l, g);
    if (vNode==NULL) return;
    for (halfEdgeNode* n = vNode->adjList; n != emptyHalfEdgeNode; n = n->next) {
      cout << n->vertPtr->name << " ";
    }
    cout << endl;
}

// funzione che fa tutto il "lavoro sporco"
void MCMinCut(string l, Graph& g) {
  vertexNode* node = getVertex(l, g);
  string node1=node->name;		// striga che conterrà il nome del primo nodod da fondere
  string node2=node -> adjList -> vertPtr -> name;		// stringa che conterrà il nome del secondo nodo da fondere
  string newNode =  node1 + node2;		// nome del nodo risultante dopo la fusione
  renameVertex(node1, node2, newNode, g);
  mergeAdjList(node1, newNode, g);
  mergeAdjList(node2, newNode, g);
  removeVertex(node1, g);
  removeVertex(node2, g);
}

// vado a cancellare il vertice l dal grafo. Questo perchè dopo aver fuso due nodi li devo cancellare lasciando solo il nodo fuso nel grafo
void removeVertex(string l, Graph& g) {
  if(g->name==l){
    if(g->next==NULL){
      g=NULL;
    }
    else
      g=g->next;
  }
  else{
	  for (Graph node = g; node->next != NULL; node = node->next) {
	    if(node->next->name==l){
	      if(node->next->next==NULL){
	        node->next=NULL;
          return;
	      }
	      else
	        node->next=node->next->next;
		  }
	  }
  }
}

// vado a cercare in tutte le liste di adiacenza i puntatori ai nodi che ho fuso e rimpiazzo quei puntatori con il puntatore al nodo fuso
void renameVertex(string old1, string old2, string newN, Graph& g) {
  addVertex(newN, g);
  for (Graph node = g; node != NULL; node = node->next) {
		for (halfEdgeNode* v = node->adjList; v != emptyHalfEdgeNode; v = v->next) {
			if(v->vertPtr->name==old1||v->vertPtr->name==old2)
				v->vertPtr=getVertex(newN, g);
		}
	}
}

// fondo le liste di adiacenza dei due nodi che ho fuso
void mergeAdjList(string l, string newN, Graph& g) {
  vertexNode* node = getVertex(l, g);
	for (halfEdgeNode* v = node->adjList; v != emptyHalfEdgeNode; v = v->next) {
		if (newN != v->vertPtr->name)
      addHalfEdge(newN, v->vertPtr->name,g);
	}
}

// restituisce il numero di nodi presenti nel grafo
int size(Graph g) {
  int size = 0;
	for (Graph node = g; node != NULL; node = node->next) {
		size +=1;
	}
	return size;
}

// si occupa di troavre randomicamente il nodo da fondere
int randomizer(Graph &g) {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  Graph node;
  vector <int> rand;
  while(size(g)>2){
    for(int i = 0; i <100; i++)   // riempo un vettore con i numeri da 1 a 100
      rand.push_back(i);
    shuffle(rand.begin(), rand.end(), rng);   // mescolo il vettore in modo casuale in modo da avere ogni volta un numero random in ogni posizione. Ho utilizzato questo metodo perchè la funzione rand() non funzionava
    node = g;
	for(int i = 0; i < rand[size(g)]%size(g); i++)   // pesco randomicamente il nodo da fondere
      	node=node->next;
	MCMinCut(node->name, g);    // funzione che si occupa di fondere un nodo con il primo nodo della sua lista di adiacenza, fondere le due liste di adiacenza e cancellare i due vecchi nodi 
	}
  return minCut(g);
}

// restituisce il min cut della run
int minCut(Graph g) {
  int mincut = 0;
  for (halfEdgeNode* v = g->adjList; v != emptyHalfEdgeNode; v = v->next)
    mincut +=1;
  return mincut;
}

// creo il grafo
Graph creaGrafo() {
  Graph g = createEmptyGraph();  
  addVertex("A", g);
  addVertex("B", g);
  addVertex("C", g);
  addVertex("D", g);
  addVertex("E", g);
  addVertex("F", g);
  addVertex("G", g);
  addVertex("H", g);
  addVertex("I", g);

  addEdge("A", "H", g);
  addEdge("A", "I", g);
  addEdge("A", "C", g);
  addEdge("A", "B", g);
  addEdge("A", "D", g);
  addEdge("B", "I", g);
  addEdge("B", "F", g);
  addEdge("B", "D", g);
  addEdge("C", "H", g);
  addEdge("C", "E", g);
  addEdge("C", "D", g);
  addEdge("D", "E", g);
  addEdge("D", "F", g);
  addEdge("E", "F", g);
  addEdge("E", "G", g);
  addEdge("E", "H", g);
  addEdge("F", "G", g);
  addEdge("F", "I", g);
  addEdge("G", "H", g);
  addEdge("G", "I", g);
  addEdge("H", "I", g);
  return g;
}

// funzione di partenza
int start() {
  Graph g = creaGrafo();
  return randomizer(g);
}