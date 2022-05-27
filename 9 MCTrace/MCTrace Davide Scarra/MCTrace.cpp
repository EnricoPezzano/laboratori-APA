#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <random>   
#include <chrono> 

using namespace std;

#define SIZE 300
ofstream fout("output.txt");

void generaMatrice(vector<vector<float>> &mat){		// genera una matrice di dimensione SIZE con elementi randomici tra 0 e 1 
	for (int j = 0; j < SIZE ; j++){
		for(int i = 0; i < SIZE; i++){
			mat[j][i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	}
}

void stampa(vector<vector<float>> mat){		// stampa la matrice
	for (int j = 0; j < SIZE ; j++){
		for(int i = 0; i < SIZE; i++){
			cout << mat[j][i] << " ";
		}
		cout << endl;
	}
}

vector<vector<float>> trasposta(vector<vector<float>>mat){		// traspone la matrice
	vector <float> temp(SIZE);
	vector<vector<float>>matT(SIZE, temp);
	for (int j = 0; j < SIZE ; j++){
		for(int i = 0; i < SIZE; i++){
			matT[j][i]=mat[i][j];
		}
	}
	return matT;
}

float norma(vector<vector<float>> mat){		// calcola la norma di Frobenius al quadrato
	float sum = 0;
	for (int j = 0; j < SIZE ; j++){
		for(int i = 0; i < SIZE; i++){
			sum += pow(mat[j][i], 2);
		}
	}
	return sum;
}

vector<vector<float>> prodotto(vector<vector<float>>mat1, vector<vector<float>>mat2){		// calcola il prodotto riga per colonna tra due matrici
	vector <float> temp(mat1.size());		//righe
	vector<vector<float>>ris(mat2.size(), temp);		//colonne
	for (int i = 0; i < mat2.size(); i++) 
		for(int j = 0; j < mat1.size() ; j++) {
			ris[i][j]=0;
			for(int k = 0; k < mat1.size() ; k++)    
				ris[i][j]=ris[i][j]+mat1[i][k]*mat2[k][j];
	}
	return ris;
}

vector<float> prodotto(vector<vector<float>>mat, vector<float>vect){		// calcola il prodotto tra una matrice e un vettore
	vector <float> ris;
	float sum = 0;
	for(int j = 0; j < mat.size(); j++) {
		sum = 0;
		for (int i = 0; i < vect.size(); i++) 
			sum += vect[i]*mat[j][i];
		ris.push_back(sum);
	}
	return ris;
}

float prodotto(vector<float>vect1, vector<float>vect2){		// calcola il prodotto tra due vettori
	float sum = 0;
	for (int i = 0; i < vect1.size(); i++) 
		sum += vect1[i]*vect2[i];
	return sum;
}

vector<float> rademacher(){		// crea il vettore di Rademacher
	vector<float> rademacher;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	for (int i = 0; i < SIZE; i++){
		if(rand()%2 == 0)
			rademacher.push_back(1);		// con probabilità 1/2 metto 1
		else
			rademacher.push_back(-1);		// con probabilità 1/2 metto -1
	}
	shuffle(rademacher.begin(), rademacher.end(), rng);		// rimescolo il vettore così ne avrò uno diverso ad ogni iterazione
	return rademacher;
}

float traccia(vector<vector<float>>mat){		// calcolo la traccia sommando la diagonale di una matrice
	float sum = 0;
	int i = 0;
	for (int j = 0; j < SIZE ; j++){
		sum += mat[j][j];
	}
	return sum;
}

float varianza(vector<vector<float>> mat){
	float sum = 0;
	for (int j = 0; j < SIZE ; j++){
		for(int i = 0; i < j; i++){
			sum += pow(mat[j][i], 2);
		}
	}
	return sum;
}

int main(){
	srand(time(NULL));
	int M[4]={5, 10, 25, 100};		// array contenente in numero di iterazioni da effettuare
	int iter;
	vector <float> temp(SIZE);
	vector<vector<float>>mat(SIZE, temp);
	generaMatrice(mat);			// matrice generata randomicamente con valori compresi tra 0 e 1
	vector<vector<float>>matT=trasposta(mat);		// traspongo la matrice appena generata
	vector<vector<float>>A=prodotto(matT, mat);		// moltiplico la matrice per se stessa trasposta per trovare A
	vector <float> Xm;		// vettori che conterrà gli Xm
	float tracciaMedia;
	float varianzaMedia;
	vector <float> media(100);		// vettore che conterrà le medie campionarie (di 100 elementi per funzionare anche nel caso in cui M=100)
	media[0]=0;
	vector<float> u;		// vettore di Rademacher
	float var=0;

	fout << (int)traccia(A) << endl;		// stampo su file la traccia effettiva
	cout << endl;
	cout << "--- La traccia effettiva della matrice A è: " << traccia(A) << " ---" << endl;
	cout << endl;
	for (int k = 0; k < 4; k++){
		iter = M[k];
		cout << "Con M = " << iter << ":" << endl;
		cout << "La varianza della media campionaria è: " << 4*varianza(A)/iter << endl;
		tracciaMedia=0;
		for (int n = 0; n < 100; n++){
			for (int j = 1; j <= iter; j++){
				u=rademacher();		// campiono un vettore di Rademacher
				vector<float> Au=prodotto(A, u);
				float X=prodotto(Au, u);		// ottengo Xm
				Xm.push_back(X);		// e lo inserisco nel corrispettivo vettore
				media[j]=media[j-1]+((X-media[j-1])/j);		// stimo la traccia
			}
			fout << (int)media[iter] << endl;		// stampo su file la stima appena trovata
			tracciaMedia+=media[iter];		// calcolo la media delle 100 stime per ogni M
			varianzaMedia=0;
			var=0;
			for (int i = 1; i <= iter; i++){
				var+=pow(Xm[i]-media[iter], 2)/(iter-1);		// calcolo la varianza
			}
			varianzaMedia+=var;		// calcolo la media delle 100 varianze per ogni M
		}

		cout << "La traccia stimata media è: " << tracciaMedia/100 << endl;
		cout << "Il quadrato della norma di Frobenius è: " << norma(A) << endl;
		cout << "La varianza campionaria media della stima è: " << varianzaMedia/100 << endl;
		cout << "Due volte il quadrato della norma di Frobenius fratto M equivale a: " << 2*norma(A)/iter << endl;
		cout << "--------------------------------------------------" << endl;
		fout << (int)(traccia(A)-sqrt(pow(Xm[6]-media[iter], 2)/(iter-1))) << endl;		// prendo uno dei 100 valori della varianza campionaria per poi confrontarlo nell'istogramma
		fout << (int)(traccia(A)+sqrt(pow(Xm[6]-media[iter], 2)/(iter-1))) << endl;
		}

}