#include <iostream>
#include <vector> 
#include <string>
#include <string>
#include <random>   
#include <chrono>  
#include <algorithm>

using namespace std; 


struct vertexNode;

typedef vertexNode* Graph;

Graph createEmptyGraph();

bool addVertex(string, Graph&);

bool addEdge(string, string, Graph&);

bool isEmpty(Graph&);

void printGraph(Graph&);

void printAdjList(string, Graph&);

void MCMinCut(string, Graph&);

void renameVertex(string, string, string, Graph&);

void mergeAdjList(string,string,Graph&);

void removeVertex(string, Graph&);

int size(Graph);

int randomizer(Graph&);

int minCut(Graph g);

int start();

Graph creaGrafo();