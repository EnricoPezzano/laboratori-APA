#include <cstdlib>
#include <iostream>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;
const int x=3;
const int y=4;
const int r=10000;

void stampa(int m [x] [y]){
		for (int i = 0; i < x; i++) {
			for(int j=0;j<y;j++){
				cout<<	m[i][j]<<"  ";
			}
			cout<<endl;
		}

} 
void impostor(int m [x] [y]){
		for(int j=0;j<3;j++){
			for (int i = 0; i < 3; i++) {
				if(i==j)m[i][3]=1-m[i][j];
			}
		}
}
int mj(int m [x] [y],int x){
	int zero=0;
	int uno=0;
	for(int j=0; j<4; j++){// calcolo maj
		if(m[x][j]==0) zero++;
		else uno++;
		}
					//ritorno  maj
	if(zero>uno) return 0;
	return 1;
				
}

int ty (int m [x] [y],int x){
	int zero=0;
	int uno=0;
	for(int j=0; j<4; j++){// calcolo tally
		if(m[x][j]==0) zero++;
		else uno++;
		}
					//ritorno tally
	if(zero>uno)return zero;
	return uno;

}

int accprob (int a[r]){
	// Determino il numero di round dopo il quale la probabilità che l'accordo è raggiunto è più grande del 99.9%
	int ripetizioni [r];
	int somma = 0;
	for (int i = 0; i<r; i++){	//inizializzo vettore a 0
    	ripetizioni[i]=0;
  	}
  		for (int i = 0; i<r; i++){			// riempo un vettore con tutti i possibili numeri di round dopo i quali si raggiunge un accordo e conto quate volte escono
    	ripetizioni[a[i]]++;
  	}
  		for (int i = 0; i<r; i++){	
  	}
  	
  	for (int i = 0; i<44; i++){		// sommo le volte in cui si raggiunge un accordo in tali round e se questo supera il 99.9% delle volte lo ritorno
    	somma+=ripetizioni[i];
    	if (somma>=r-(r*0.001))	return i++;
	}
}
float media(int a[r]){
	float med=0;
	for(int i=0;i<r;i++){
		med+=a[i];
	}
	return med=med/r;
}
float varianza(int a[r]){
		float somma = 0;
		for (int i = 0; i < r; i++)
		somma += pow(a[i], 2);
		float mediaPow = (float)somma/r;
  		float var;
  		return var = mediaPow-pow(media(a), 2);
}

int main()
{
	
    srand((unsigned)time(NULL));
	int a [x][y];
	int num_round=0;
	int med_round[r];
	bool loop=true;
	int zero=0;
	int uno=0;
	int maj;
	int tally;
	for(int l=0;l<r;l++){
		int a2 [x];// ogni volta ridefinisco a2
		num_round=0; //azzero i numeri di round
		// inizializzo il generatore di numeri pseudo-casuali
	 	int val= rand()%2;
		for(int j=0;j<3;j++){ // ciclo 10k
			for (int i = 0; i < 3; i++) {
					a[i][j]=val;
			}
			 val= rand()%2;
		}
		// make the impostor
		cout<<endl<<"                    MATRICE INIZIALE              :"<<endl;
		impostor(a);		
		stampa(a);
		int flag=0;	
		int moneta;
		bool loop =true;
			while(loop!=false){
				
			// itero con una variabile i sulle righe della matrice
				for(int i=0; i<3 ;i++){
							//precondizione
						if(a[0][0]==a[0][1] && a[0][1]==a[0][2]){
							med_round[l]=num_round;
							loop=false;
							cout<<endl<<"NUMERO DI ROUND:    "<<num_round<<endl;
							break;
						}
					num_round++;
					moneta=rand()%2;					
					// Calcolo maj e tally tra i 4 valori di quella riga di quel determinato round i
					maj=mj(a,i); 
					tally=ty(a,i);
					cout<<endl<<endl<<"MAJ:       "<<maj<<"    TALLY:         "<<tally<<"          MONETA:           "<<moneta<<endl<<endl;
						 // Se tally > 2t+1
					if(tally>=3){
							a2[i]=maj; // Nel prossimo round il processo i avrà valore = maj, quindi tutta l'i-esima colonna della matrice avrà solo il valore maj
					}
					else{// altrimenti

						a2[i]=moneta;// Nel prossimo round il processo i avrà valore = moneta, quindi tutta l'i-esima colonna della matrice avrà solo il valore moneta	

					}
							//ridefinire la matrice a attraverso i valori in a2
					for (int j = 0; j < 3; j++) {
							a[j][i]=a2[i];
					}
					impostor(a);
					stampa(a);
						
				}
		    }
		}
		
		//calcolo media round

	
		cout<<endl<<"MEDIA ROUND:"<<media(med_round)<<endl;
		cout << "Il numero di round dopo il quale la probabilita di raggiungere un accordo > del 99.9% è: " << accprob(med_round)<<endl;
			//calcolo la varianza usando la formula E[u^2] - µ^2
  		cout << "varianza: " << varianza(med_round) << endl;
}
