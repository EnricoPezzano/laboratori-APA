#include<iostream>
#include<vector>
#include<cmath>
#include <vector>
#include <stdlib.h>
#include<fstream>
#include <stdio.h>
#include <algorithm>


using namespace std;


void scambia(vector<int>& v, int i, int j)
{
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}



int partizionaInPlace(vector<int>& v, int inizio, int fine, int& conf)
{
   int pivotIndex = inizio+rand()%(fine-inizio+1); //scelgo un indice tra inizio e fine
   scambia(v, pivotIndex, inizio); // metto il pivot in cima alla sequenza
   int i = inizio+1;
   for (int j=inizio+1; j<=fine; ++j)
       {
       if (v[j] < v[inizio]) //confronto
          {
           conf++; //incremento dei confronti
          scambia(v, i, j);
          ++i;

              
          }
       }
 scambia(v, inizio, i-1);
    
    return i-1;
}


void qs(vector<int>& v, int inizio, int fine, int& conf)
{
    if (inizio < fine)
      {
          int pivot_index=partizionaInPlace(v, inizio, fine, conf);
    
          qs(v, inizio, pivot_index-1, conf);
          qs(v, pivot_index+1, fine, conf);
      }
}

void quickSort(vector<int>& v, int& conf)
{
    
    qs(v, 0, v.size()-1, conf);
}

long double run(vector<int>& v, int conf)
{
    
    
    for (int i=0; i<v.size(); i++)
    {
        v.at(i)=rand();//riempo un vettore di valori randomici
    }
    quickSort(v, conf);
    cout << " #CONFRONTI: " << conf << " "<<endl;
    
    return conf;
}

//funzione per contare quante volte si ripete lo stesso numero di confronti
int conta(vector<int> s, int n)
{
	int count=0;
	
		for(int j=0; j<s.size(); j++)
		{
			if(n==s.at(j))
				count++;
		}
	
  return count;
}


int main(){
    
    fstream file;
    int conf=0;
    int size=pow(10,5);
    srand(time(NULL));
    vector<int> v (pow(10,4));
    vector<int> s (size);
    long double sum, valmed, var, som, in;
    som=0;
    sum=0;
    
    for(int i=0; i<size; i++)
    {
        s.at(i)=run(v, conf);
        sum=sum+s.at(i);
    }
    valmed=sum/size;
    for(int i=0; i<size; i++)
    {
        in=pow((s.at(i)-valmed),2);
        som=som+in;
    }
    
    var=som/size;
    cout << "Valore medio: " << valmed << " ";
    cout << "Varianza: " << var << endl;
    
    int a;
    quickSort(s, a); //ordino il vettore di confronti
    
    vector<int> count(size);
    int valq, vald, contvald, contvalq;
    vald=valmed*2;
    valq=valmed*5;
    contvald=0;
    contvalq=0;
    
   int cont=0;
   float probd, probq, p;
   
   for(int i=0; i<s.size(); i++)
    { 
        count.at(i)=conta(s,s.at(i));
        if(vald==s.at(i))
        	contvald++;
        if(valq==s.at(i))
        	contvalq++;
    }
    p=static_cast<float>(1/s.size());
    
   if(contvald==0) cout << "Non ci sono valori che siano il doppio del valore medio" << endl;
   else{
       probd=pow(p, contvald)*pow((1-p),(s.size()-contvald));
       cout << "Probabilità di ottenere il doppio del valore medio: " << 	probd << endl;
    }
    if(contvalq==0) cout << "Non ci sono valori che siano il quintuplo del valore medio" << endl;
    else{
    	probq=pow(p, contvalq)*pow((1-p),(s.size()-contvalq));
    	cout <<"Probabilità di ottenere il quintuplo del valore medio: " 	<< probq << endl;
    }
    
//------CREAZIONE ISTOGRAMMA-------
    int x=0;
    int val;
    val=static_cast<int>(valmed);
    
     ofstream FileMed("valoremed.txt");
    if (FileMed.is_open() )
    {	//inserisco in un file il valore medio che mi servirà per fare il grafico
               FileMed<<val<<endl;
    }
	  
    //chiudo il file con le coordinate dei punti da visualizzare
       
     FileMed.close();
    
    //apro il file per registrare i punti della funzione
     ofstream OpenFile("las.txt");
    if (OpenFile.is_open() )
    {
      //int count=0;
        for(int i=0; i<s.size(); i++)
        {	
                //scrivo sul file le coordinate del punto (x,y)
               OpenFile<<s.at(i)<<"\t"<<count.at(i)<<endl;
          
                
            }
        }
	  
    
    //chiudo il file con le coordinate dei punti da visualizzare
       
     OpenFile.close();
  

}
