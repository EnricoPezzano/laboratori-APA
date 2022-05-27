#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

typedef int vert;

const int inesistente=-1;
const int arcoassente=0;
const int maxvert=10;
typedef int Peso;
typedef struct{
	int numvert;
	Peso matrice[maxvert][maxvert];
}Grafo;

Grafo creagrafo(const int n);
bool addedge(Grafo&, vert, vert, Peso);
bool uniti(Grafo , vert , vert);
bool collegati(const Grafo& , vert , vert , vert&);
void mincut(Grafo);
void print(Grafo);

Grafo creagrafo(const int n){
	Grafo g;
	for (int i=0; i<maxvert; ++i)
		for(int j=0; j<maxvert; ++j)
			g.matrice[i][j]=inesistente;
		g.numvert=n;
	for(int i=0; i<g.numvert; ++i)
		for(int j=0; j<g.numvert; ++j)
			g.matrice[i][j]=arcoassente;
	return g;
}


bool addedge(Grafo& g, vert v1, vert v2, Peso p){
	if(0<=v1 && v1<=g.numvert && 0<=v2 && v2<=g.numvert && p>=0 && v1!=v2){
	g.matrice[v1][v2]=p;
	return true;
	}
	else
	return false;
}

void print(Grafo g){
	for (int i=0; i<g.numvert;++i){
		for(int j=0; j<g.numvert; ++j)
			cout << g.matrice[i][j] << "\t";
		cout << endl;}
}

bool collegati(Grafo& g, vert v1, vert v2, vert v){
	if(g.numvert==0) return false;
	for(int i=0; i<g.numvert; ++i)
	{
		if(g.matrice[v1][i]!=0 && g.matrice[i][v2]!=0)
		{
			v=i;
			return true;
		}	
	}
	v=inesistente;
	return false;
}

bool uniti(Grafo g, vert v1, vert v2){
	if(g.matrice[v1][v2]!=0)
	{  
		return true;
	}	
	else return false;
}

void mincut(Grafo g)
{

int n=g.numvert;
int numvr=g.numvert;
while(numvr>2)
{
	int i=rand()%numvr;
	int j=rand()%numvr;
	
	cout << "vert i-j: " << i << " " << j << endl;
	if(uniti(g, i, j))
	{
		for(int x=0; x<g.numvert; ++x)
		{
			if(g.matrice[i][x]!=arcoassente)
			{
				g.matrice[j][x]=1;
				g.matrice[i][x]=arcoassente;
			}
		}
		n-=1;	
	}
	numvr-=1;	
}
cout << "mincut: " << n << endl;
}

int main(){
	Grafo g;
	g=creagrafo(9);
	addedge(g, 0, 1, 1);
	addedge(g, 0, 2, 1);
	addedge(g, 0, 3, 1);
	addedge(g, 0, 7, 1);
	addedge(g, 0, 8, 1);
	addedge(g, 1, 2, 1);
	addedge(g, 1, 4, 1);
	addedge(g, 1, 5, 1);
	addedge(g, 1, 8, 1);
	addedge(g, 2, 3, 1);
	addedge(g, 2, 4, 1);
	addedge(g, 2, 6, 1);
	addedge(g, 3, 6, 1);
	addedge(g, 3, 7, 1);
	addedge(g, 4, 5, 1);
	addedge(g, 4, 6, 1);
	addedge(g, 5, 6, 1);
	addedge(g, 5, 7, 1);
	addedge(g, 5, 8, 1);
	addedge(g, 6, 7, 1);
	addedge(g, 7, 8, 1);
	print(g);
	
	srand(time(NULL));
	float m=pow(10,5);	
	float Prtaglio, min;
	for(int i=0; i<m; ++i) {
	cout << "----------------------------------------------"<< endl;
		mincut(g);
		//print(g);
		Prtaglio=2/pow(g.numvert,2);
	 	min=pow((1-2/pow(9,2)),i-1);
	 	cout << Prtaglio << " < " << min << endl;
	}

	 
}
