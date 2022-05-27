#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

#define ITER 100000

// lancio la moneta
int moneta(){
	return rand()%2;
}

// calcolo il tally
int tally(int maj, vector<int>generali){
	int tally = 0;
	for(int x : generali){
		if ( x == maj)
      {
         printf("\n%d",tally);
         tally++;
      }
			
	}
	return tally;
}

// verifico se si è raggiunto un accordo (sulla diagonale devono esserci gli stessi valori).
// Essendo gen una matrice con 4 colonne e 3 righe il processo malevolo, essendo l'ultimo, è escluso dalla diagonale
bool accordo(vector<vector<int>>gen){
	int acc = 0;
	int s = 0;
	for (int j = 0; j < 3 ; j++){
		if(gen[j][s]==1)
			acc++;
		s++;	
	}
	return(acc == 0 || acc == 3);		// se sulla diagonale ci sono 3 uni o 0 zeri vuol dire che si è raggiunto un accordo
}

// calcolo la maggioranza
int maj(vector<int>generali){
	int scelta = 0;
	for(int i = 0; i < generali.size(); i++){
		if (generali[i] == 1)
			scelta +=1;
	}
	if (scelta == 2){		// se si è in una condizione di stallo scelgo randomicamente il da farsi
		return rand()%2;
	}
	if(scelta>2)
		return 1;
	else 
		return 0;
}

// al round 0 le decisioni dei processi affidabili sono randomiche
void inizio(vector<vector<int>> &gen){
	int z = 0;
	for (int j = 0; j < 3 ; j++){
		if(j==0){
			for(int i = 0; i < 3; i++){
				gen[j][i]=rand()%2;
			}
		}
		gen[j]=gen[0];		// i 2t + 1 processi affidabili si scambiano le scelte
		gen[j][3]=1-gen[j][z];		// il processo maligno sceglie ad ogni round il contrario della dcisione di un processo affidabile
		z++;
	}
}

// Ad ogni round i processi affidabili prendono una decisione in base al tally e alla maggioranza mentre il processo malevolo dice il contrario
void round(vector<vector<int>> &gen){
	int z = 0;
	int coin = moneta();		// lancio la moneta globale
	int s=0;
	for (int j = 0; j < 3 ; j++){
		if(j==0){
			for(int i = 0; i < 3; i++){
				if(tally(maj(gen[s]), gen[s])>=3)		// if tally(i) ≥ 2t + 1
					gen[0][i]=maj(gen[s]);		// then b(i) ← maj(i)
				else 
					gen[0][i]=coin;		// then b(i) ← risultato della moneta
				s++;
			}
		}
		gen[j]=gen[0];		// i 2t + 1 processi affidabili si scambiano le scelte
		gen[j][3]=1-gen[j][z];		// il processo maligno sceglie ad ogni round il contrario della dcisione di un processo affidabile
		z++;
	}
}

int probAcc (vector<int>numeriRound){
	// Determino il numero di round dopo il quale la probabilità che l'accordo è raggiunto è più grande del 99.9%
	vector <int> ripetitions(44);
	int somma = 0;
	for (int i = 0; i<numeriRound.size(); i++){		// riempo un vettore con tutti i possibili numeri di round dopo i quali si raggiunge un accordo e conto quate volte escono
    	ripetitions[numeriRound[i]]++;
  	}
  	for (int i = 0; i<ripetitions.size(); i++){		// sommo le volte in cui si raggiunge un accordo in tali round e se questo supera il 99.9% delle volte lo ritorno
    	somma+=ripetitions[i];
    	if (somma>=ITER-ITER*0.001)
    		return i;
  	}
  	return 0;
}

int main(){
	srand(time(NULL));
	int nRound = 0;
	vector <int> temp(4);
	vector<vector<int>>gen(3, temp);		// costruisco la matrice rappresentante le scelte dei 4 processi
	vector<int>numeriRound;		// vettore che contiene i numeri di round dopo i quali si è raggiunto un accordo
	
	for (int i = 0; i < ITER; i++){
		nRound=0;
		inizio(gen);		// genero randomicamente le decisioni iniziali dei processi affidabili
		while (!accordo(gen)){		// finchè non si raggiunge un accordo si va avanti con i round
			round(gen);
			nRound++;
		}
		numeriRound.push_back(nRound);
	}

	cout << "Il numero di round dopo il quale la probabilità di raggiungere un accordo è maggiore del 99.9% è: " << probAcc(numeriRound) << endl;
	
	//calcolo la media
	int somma = 0;
	for (int i = 0; i < numeriRound.size(); i++)
		somma += numeriRound[i];
	float media = (float)somma/ITER;
	cout << "La media di round è: " << media << endl;
	
	//calcolo la varianza usando la formula E[u^2] − µ^2
	somma = 0;
	for (int i = 0; i < numeriRound.size(); i++)
		somma += pow(numeriRound[i], 2);
	float mediaPow = (float)somma/ITER;
  	float varianza = mediaPow-pow(media, 2);
  	cout << "La varianza è: " << varianza << endl;
}