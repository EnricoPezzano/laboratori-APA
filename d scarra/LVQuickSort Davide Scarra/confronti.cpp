#include "confronti.h"

/*Costruisci una sequenza S di numeri con |S| = 10^4. Implementa LVQuickSort e conta il numero
Nj di confronti effettuati in ogni singolo run j per ordinare la sequenza S. Calcola il valore medio
e la varianza del numero di confronti effettuati su 10^5 run. Produci un istogramma con i valori
ottenuti usando 50 bin ed evidenzia il bin nel quale cade il valor medio. Normalizza a 1 l’area
dell’istogramma e stima empiricamente la probabilita con la quale ` LVQuickSort effettua il doppio e
il quintuplo del valor medio dei confronti.*/

ofstream fout("output.txt");

void valoreMedioVarianza(int iter, vector <int>seq){
  vector < int >ris;    // vettore che conterrà tutti i confronti fatti ad ogni run
  for(int i = 0; i<iter; i++){
    ris.push_back(LVQuickSort(seq));
    fout<<confronti<<endl;    // stampo su file
    confronti=0;
  }   // ho riempito il vettore
  double somma=0;
  for(int i = 0; i<ris.size(); i++){
    somma+=ris[i];
  }   // sommo il numero di confronti fatti ad ogni run 
  double media = somma/iter;   // calcolo il valore medio
  float sommatoria = 0;
  for(int i = 0; i<ris.size(); i++){
    sommatoria += sqrt((ris[i]-media)*(ris[i]-media));
  }   // calcolo la sommatoria della varianza
  float varianza = sommatoria/iter;   // calcolo la varianza\\\\\\\\\\\\\\\\\\\\\ quadrato e poi radice
  cout << endl;
  cout << "-------------------------------------" << endl;
  cout << "La varianza e': " << varianza << endl;
  cout << "Il valore medio e': " << media << endl;
  cout << "-------------------------------------" << endl;
  cout << endl;
}

vector < int > creaSeq ()
{
  vector < int >seq;
  srand ((unsigned) time (NULL));
  for (int i = 0; i < 10000; ++i)
    seq.push_back (rand ());
  return seq;
}

void scambia (vector < int >&v, int i, int j)
{
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

int QuickSort (vector < int >&v, int inizio, int fine)
{
  int pivotIndex = inizio + rand () % (fine - inizio + 1);	
  scambia (v, pivotIndex, inizio);	
  int i = inizio + 1;
  for (int j = inizio + 1; j <= fine; ++j)
    {
      confronti++;
      if (v[j] < v[inizio])	
	{
	  scambia (v, i, j);
	  ++i;
	}
    }
  scambia (v, inizio, i - 1);
  return i - 1;
}


void LVqs (vector < int >&v, int inizio, int fine)
{
  if (inizio < fine)
    {
      int pivot_index = QuickSort (v, inizio, fine);
      LVqs (v, inizio, pivot_index - 1);
      LVqs (v, pivot_index + 1, fine);
    }
}

int LVQuickSort (vector < int >&v)
{
  LVqs (v, 0, v.size () - 1);
  
  return confronti;
}

int main ()
{
  valoreMedioVarianza(100000, creaSeq ());

  fout.close();
}
