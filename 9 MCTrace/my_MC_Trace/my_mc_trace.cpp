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

// genera una matrice di dimensione SIZE con elementi randomici tra 0 e 1
void fill_matrix(vector<vector<float>> &mat){
	for (int j=0; j<SIZE; j++)
		for(int i=0; i<SIZE; i++)
			mat[j][i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

}

// da controllare se utilizzata nel codice "stampa()"
void my_print(vector<vector<float>> mat){
	for (int j=0; j<SIZE; j++){
		for(int i=0; i<SIZE; i++){
			cout << mat[j][i] << " ";
		}
		cout << endl;
	}
}

vector<vector<float>> transpose(vector<vector<float>>mat){		// traspone la matrice
	vector <float> temp(SIZE);
	vector<vector<float>> matT(SIZE, temp);
	for (int j=0; j<SIZE ; j++){
		for(int i=0; i<SIZE; i++){
			matT[j][i] = mat[i][j];
		}
	}
	return matT;
}

float frobenius_norme(vector<vector<float>> mat){		// calcola la norma di Frobenius al quadrato
	float sum = 0;
	for (int j=0; j<SIZE; j++){
		for(int i=0; i<SIZE; i++){
			sum += pow(mat[j][i], 2);
		}
	}
	return sum;
}

// calcola il prodotto riga per colonna tra due matrici
vector<vector<float>> mul(vector<vector<float>>mat1, vector<vector<float>>mat2){
	vector <float> temp(mat1.size());		//righe
	vector<vector<float>> ris(mat2.size(), temp);		//colonne
	for (int i=0; i<mat2.size(); i++) 
		for(int j=0; j<mat1.size(); j++) {
			ris[i][j] = 0;
			for(int k=0; k<mat1.size(); k++)    
				ris[i][j] = ris[i][j]+mat1[i][k]*mat2[k][j];
	}

	return ris;
}

// calcola il prodotto tra una matrice e un vettore
vector<float> mul(vector<vector<float>>mat, vector<float>vect){
	vector <float> ris;
	float sum = 0;
	for(int j=0; j<mat.size(); j++) {
		sum = 0;
		for (int i=0; i<vect.size(); i++) 
			sum += vect[i]*mat[j][i];
		ris.push_back(sum);
	}
	return ris;
}

// calcola il prodotto tra due vettori
float mul(vector<float>vect1, vector<float>vect2){
	float sum = 0;
	for (int i=0; i<vect1.size(); i++)
		sum += vect1[i]*vect2[i];

	return sum;
}

// crea ed inizializzo il vettore di Rademacher
vector<float> rademacher(){
	vector<float> rademacher;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	for (int i=0; i<SIZE; i++){
		if(rand()%2 == 0)
			rademacher.push_back(1);		// con probabilità 1/2 metto 1
		else
			rademacher.push_back(-1);		// con probabilità 1/2 metto -1
	}
	shuffle(rademacher.begin(), rademacher.end(), rng);		// rimescolo il vettore così ne avrò uno diverso ad ogni iterazione
	return rademacher;
}

// calcola la traccia sommando la diagonale della matrice
float trace(vector<vector<float>>mat){
	float sum = 0;
	int i = 0;
	for (int j=0; j<SIZE; j++)
		sum += mat[j][j];

	return sum;
}

float variance(vector<vector<float>> mat){
	float sum = 0;
	for (int j=0; j<SIZE; j++)
		for(int i=0; i<j; i++)
			sum += pow(mat[j][i], 2);

	return sum;
}

int main()
{
	srand(time(NULL));

	int M[4] = {5, 10, 25, 100};  // ogni "cella" contiene il numero di iterazioni da effettuare
	int iterations;

	vector <float> temp(SIZE);
	vector<vector<float>> mat(SIZE, temp);

	fill_matrix(mat); // riempo randomicamente la mtrice con valori [0,1]

	vector<vector<float>> matT = transpose(mat);
	vector<vector<float>> A = mul(matT, mat); // moltiplico la matrice per la sua trasposta per trovare A, come da consegna
	vector<float> Xm; // vettore per contenere gli Xm
	float avg_trace;
	float avg_variance;

	vector<float> avg_vect(100);	// vettore per contenere le medie campionarie (di 100 elementi per far funzionare anche il caso in cui M=100)
	avg_vect[0] = 0; // valore init
	vector<float> rademacher_vect;   // vettore di Rademacher per i campionamenti
	float var = 0;

	fout << (int)trace(A) << endl; // stampo su file la traccia effettiva
   
	cout << endl << "La traccia effettiva della matrice A è: " << trace(A) << endl << endl;

	for (int k=0; k<4; k++){ // {5, 10, 25, 100}
		iterations = M[k];
		cout << "Con M = " << iterations << ":" << endl;
		cout << "La varianza della media campionaria è: " << 4*variance(A)/iterations << endl;
		avg_trace = 0;

		for(int n=0; n<100; n++){
			for(int j=1; j<=iterations; j++){
				rademacher_vect = rademacher();  // campiono un vettore di Rademacher
				vector<float> Au = mul(A,rademacher_vect);
				float X = mul(Au,rademacher_vect);  // calcolo X di m...
				Xm.push_back(X);  //...e lo inserisco nel vettore corrispondente
				avg_vect[j] = avg_vect[j-1]+((X-avg_vect[j-1])/j); // stima della traccia
			}
			fout << (int)avg_vect[iterations] << endl; // stampo su file la stima appena trovata
			avg_trace += avg_vect[iterations];   // calcolo la media delle 100 stime per ogni M...{5, 10, 25, 100}
			avg_variance = 0;
			var = 0;
			for (int i=1; i<=iterations; i++)
				var += pow(Xm[i]-avg_vect[iterations],2)/(iterations-1);  // calcolo la varianza
			
// TODO perchè somma var ciclicamente?
			avg_variance += var; // calcolo la media delle 100 varianze per ogni M...{5, 10, 25, 100}
		}

		cout << "La traccia stimata media è: " << avg_trace/100 << endl;
		cout << "Il quadrato della norma di Frobenius è: " << frobenius_norme(A) << endl;
		cout << "La varianza campionaria media della stima è: " << avg_variance/100 << endl;
		cout << "Due volte il quadrato della norma di Frobenius fratto M equivale a: " << 2*frobenius_norme(A)/iterations << endl;

		cout << "Fine calcolo. Salvo uno dei 100 valori della varianza campionaria per poi confrontarlo nell'istogramma." << endl;

      // TODO perchè sottraggo e poi sommo lo stesso valore?
		fout << (int)(trace(A)-sqrt(pow(Xm[3]-avg_vect[iterations], 2)/(iterations-1))) << endl;
		fout << (int)(trace(A)+sqrt(pow(Xm[3]-avg_vect[iterations], 2)/(iterations-1))) << endl;
	} // end for k<4
}