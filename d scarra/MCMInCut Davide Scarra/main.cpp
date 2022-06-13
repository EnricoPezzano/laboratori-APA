#include "graph.h"


using namespace std;

int main() { 
  vector <int> ris;
  vector <int> ripetitions(11, 0);
  int prob;
  int max = 0;
  int indice;

  for (int i = 0; i < 100000; i++){
    ris.push_back(start());   // in questo vettore memorizzo i risultati di ogni run del mincut
  }
  for (int i = 0; i<=ris.size(); i++){
    ripetitions[ris[i]]++;        // ora vado a contare quante volte è uscito lo stesso mincut
  }
  for (int i = 1; i<=ripetitions.size(); i++){
    cout <<"Il taglio minimo candidato di valore " << i << " è uscito " << ripetitions[i] << " volte, con probabilità " << (float) ripetitions[i]/ 100000 << endl;
  }
  for(int i = 0; i < ripetitions.size(); i++){        // ora vado a vedere qual è il mincut uscito più volte
    if (ripetitions[i] > max){
      max = ripetitions[i];
      indice = i;
    }
  }
  cout << endl;
  cout << "Il taglio minimo è " << indice <<" che è uscito " << max << " volte con una probabilità di " << (float) max/ 100000 << endl << endl;
}




/*
I: H G F B A
H: I G E C A
G: I H F E
F: I G E D B
E: H G F D C
D: F E C B A
C: D E H A
B: D F I A
A: D B C I H    */