#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

#define N 300 //Dimensione delle matrici considerate
#define R 100 //run

//FUNZIONI UTILI

//----------------------------------------------------------------------------------------------------

//calcolo matrice trasposta
void trasposta(int matrix[][N], int matrixT[][N]){
  for(int r = 0; r < N; r++)
    for(int c = 0; c < N; c++)
      matrixT[c][r] = matrix[r][c];
}

//prodotto tra due matrici
void product(int matrix1[][N], int matrix2[][N], int product[][N]){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      product[i][j] = 0;
      for(int k = 0; k < N; k++)
        product[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
}

//calcolo della matrice semipositiva
//per avere una matrice semipositiva calcoliamo la trasposta di B e la moltiplichiamo per B stessa
//il risultato sarà contenuto in A
void semi_positive(int B[][N], int A[][N]){
  int BT[N][N];
  trasposta(B, BT);
  product(BT,B,A);
}


//calcolo della traccia (da definizione)
//ovvero la somma degli elementi diagonali della matrice
int trace(int matrice[][N]){
  int counter = 0;
  int traccia = 0;
  while(counter < N){
    traccia += matrice[counter][counter];
    counter++;
  }
  return traccia;
}

//calcolo della norma di frobenius (da definizione)
//ovvero la radice quadrata della sommatoria degli elementi di A elevati alla seconda
long int frobenius(int matrice[][N]){
  long int IAI2 = 0;
  for(int r = 0; r < N; r++)
    for(int c = 0; c < N; c++)
      IAI2 += matrice[r][c]*matrice[r][c];
  return sqrt(IAI2);
}

//semplice calcolo varianza
double varianza (vector<double> res, double media){
  double var = 0.0;
  for(int i = 0; i < res.size(); i++)
    var += ((res.at(i)-media)*(res.at(i)-media));
  var /= res.size();
  return var;
}

//-------------------------------------------------------------------------------------------------

//ORACOLO
//l'oracolo che permette di calcolare dato vettore e matrice vettore^T matrice vettore che è result
int oracolo(int matrice[][N], int vettore[N]){
  int aux[N] = {0};
  int result = 0;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      aux[i] += matrice[j][i]*vettore[j];

  for(int k = 0; k < N; k++)
    result += aux[k]*vettore[k];

  return result;
}


/*ALGORITMO MCTRACE (come da pseudocodice)
Campiono un vettore di Rademacher casualmente e calcolo,
tramite la funzione "oracolo", uT*A*u.
Infine restituisco la stima della traccia ottenuta.  */
int MCTrace(int matrix[][N], int M){
  int stima = 0;
  srand(time(NULL));
  for(int m = 0; m < M; m++) {
    int rademacher[N] = { 0 };
    for(int j = 0; j < N; j++){
      int index = rand()%2; //ELEMENTO CASUALE DEL NOSTRO ALGORITMO
      if(index == 0) rademacher[j] = -1;
      else rademacher[j] = 1;
    }
    int oracle = oracolo(matrix, rademacher); //chiamo l'oracolo che mi restituisce uT*A*u
    if(m == 0) stima = oracle;
    else stima += (oracle - stima)/m;
  }
  return stima;//restituisco la stima della traccia come da definizione nello pseudocodice
}

int main() {
  int matrice[N][N];
  int semipositiva[N][N] = {0};
  srand(time(NULL));
  for(int r = 0; r < N; r++)
    for(int c = 0; c < N; c++)
      matrice[r][c] = rand()%2;

  //INIZIALIZZAZIONE VARIABILI E VETTORE RISULTATI
  int traccia = 0;
  long double media = 0;
  long int frob_var = 0;
  vector<double> res;
  vector<double> finalres;

  //*******************************************************************************************//
  //*********************                   M=5              **********************************//
  //*******************************************************************************************//
  for(int i = 0; i < R; i++){
    semi_positive(matrice, semipositiva);
    traccia = trace(semipositiva);
    res.push_back(MCTrace(semipositiva, 5));
  }
  for(int i= 0; i < R; i++)
  	finalres.push_back(res.at(i));

  //CALCOLI DA DEFINIZIONE
  frob_var = frobenius(semipositiva);
  cout << "Norma di Frobenius: " << frob_var << endl;
  cout << "Traccia effettiva: " << traccia << endl;
  //MEDIA CAMPIONARIA
  for(int j = 0; j < R; j++) media += res.at(j);
  cout << endl << "Media campionaria(M = 5): " << media/100 << endl;
  //ANALISI RISULTATI
  cout << "Varianza: " << varianza(res,media/100) << endl;
  double frobM = 2*frob_var*frob_var/5;
  cout << "2*Frobenius/M: " << frobM << endl;

  //RESET
  media = 0;
  cout << endl;
  res.clear();

  //*******************************************************************************************//
  //*********************                   M=10             **********************************//
  //*******************************************************************************************//
  for(int i = 0; i < R; i++){
    semi_positive(matrice, semipositiva);
    res.push_back(MCTrace(semipositiva, 10));
  }
  for(int i= 0; i < R; i++)
  	finalres.push_back(res.at(i));
  //MEDIA CAMPIONARIA
  for(int j = 0; j < R; j++) media += res.at(j);
  cout << "Media campionaria(M = 10): " << media/100 << endl;
  //ANALISI RISULTATI
  cout << "Varianza: " << varianza(res,media/100) << endl;
  frobM = 2*frob_var*frob_var/10;
  cout << "2*Frobenius/M: " << frobM << endl;

  //RESET
  media = 0;
  cout << endl;
  res.clear();

  //*******************************************************************************************//
  //*********************                   M=25             **********************************//
  //*******************************************************************************************//
  for(int i = 0; i < R; i++){
    semi_positive(matrice, semipositiva);
    res.push_back(MCTrace(semipositiva, 25));
  }
  for(int i= 0; i < R; i++)
  	finalres.push_back(res.at(i));
  //MEDIA CAMPIONARIA
  for(int j = 0; j < R; j++) media += res.at(j);
  cout << "Media campionaria(M = 25): " << media/100 << endl;
  //ANALISI RISULTATI
  cout << "Varianza: " << varianza(res,media/100) << endl;
  frobM = 2*frob_var*frob_var/25;
  cout << "2*Frobenius/M: " << frobM << endl;
  //RESET
  media = 0;
  cout << endl;
  res.clear();

  //*******************************************************************************************//
  //*********************                  M=100             **********************************//
  //*******************************************************************************************//
  for(int i = 0; i < R; i++){
    semi_positive(matrice, semipositiva);
    res.push_back(MCTrace(semipositiva, 200));
  }
  for(int i= 0; i < R; i++)
  	finalres.push_back(res.at(i));
  //MEDIA CAMPIONARIA
  for(int j = 0; j < R; j++) media += res.at(j);
  cout << "Media campionaria(M = 100): " << media/100 << endl;
  //ANALISI RISULTATI
  cout << "Varianza: " << varianza(res,media/100) << endl;
  frobM = 2*frob_var*frob_var/200;
  cout << "2*Frobenius/M: " << frobM << endl;
  
    	ofstream f;
    f.open("dataM.txt", ios::out);
    for(int i=0; i< 4 *R; i++)
        f << finalres.at(i) << endl;
}
