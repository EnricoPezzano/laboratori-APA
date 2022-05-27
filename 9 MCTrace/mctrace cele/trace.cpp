#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <random>   
#include <chrono> 
#define n 300
using namespace std;

void creamatrice(vector<vector<double>>&);
void stampamatrice(vector<vector<double>>);
void trasposta(vector<vector<double>>&, vector<vector<double>>);
void prodotto(vector<vector<double>>, vector<vector<double>>, vector<vector<double>>&);
int Tr(vector<vector<double>>);
vector<double> rademacher();
vector<double> prodottovet_mat(vector<vector<double>>, vector<double>);
double prodottoX(vector<double>, vector<double>);
double varianza(vector<vector<double>>);
double frobenius(vector<vector<double>>);

int main(){
	fstream file;
	ofstream OpenFile("output.txt");
	ofstream File("Traccia_confron.txt");
	srand(time(NULL));
	vector <double> b(n);
	vector<vector<double>>B(n, b); 
	creamatrice(B);
	
	
	vector<vector<double>>Bt(n, b); 
	trasposta(Bt, B);
	
	
	vector<vector<double>>A(n, b);
	prodotto(Bt, B, A);
	vector<double> M{5,10,25,100};
	vector <double> Xm;
	vector <double> u;
	vector <double> media(100);
	double tracciaMedia, traccia;
	double varianzaMedia, var;
	media[0]=0;
	int count;
	traccia=Tr(A);//è data dalla somma degli elementi diagonali di A
	cout << "Tr(A): " << traccia << endl;
	if (File.is_open()){
		File << (int)traccia <<endl;
	} 
	for(int m=0; m<4; m++){
		count = M.at(m);
		cout << "Con M = " << count << ":" << endl;
		cout << "La varianza della media campionaria è: " << 4*varianza(A)/count << endl;
		tracciaMedia=0;
		for(int i=0; i<100; i++){
			for(int j=1; j<=count; j++){
				u=rademacher();
				vector<double> uA=prodottovet_mat(A, u);
				double X=prodottoX(uA, u);
				Xm.push_back(X);
				media[j]=media[j-1]+((X-media[j-1])/j);	
			}	
			
			if (OpenFile.is_open() )
    			{
				OpenFile << (int)media[count]<<endl; 
			}  
			tracciaMedia+=media[count];
			varianzaMedia=0;
			var=0; 
			double sum = 0;
			
			for (int t = 1; t <= count; t++){
				var+=pow(Xm[t]-media[count], 2)/(count-1);
					
			}
			varianzaMedia+=var;
		}
		
		cout << "La traccia stimata media è: " << tracciaMedia/100 << endl;
		cout << "Il quadrato della norma di Frobenius è: " << frobenius(A) << endl;
		cout << "La varianza campionaria media della stima è: " << varianzaMedia/100 << endl;
		cout << "Due volte il quadrato della norma di Frobenius fratto M equivale a: " << 2*frobenius(A)/count << endl;
		if (File.is_open()){
			File << (int)(traccia+sqrt(pow(Xm[7]-media[count], 2)/(count-1))) << endl; 
			File << (int)(traccia-sqrt(pow(Xm[7]-media[count], 2)/(count-1))) << endl;
		}   //inserisco nel file uno dei cento valori da confrontare con la traccia effettiva
	
	}
	//chiudo i file con le coordinate dei punti da visualizzare
     	OpenFile.close();
     	File.close();
}



void creamatrice(vector<vector<double>> &B){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			B[i][j]=rand()%2;
		}
	}
}

void stampamatrice(vector<vector<double>>B){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
	cout<< endl;
}

void trasposta(vector<vector<double>>&Bt, vector<vector<double>>B){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			Bt[i][j]=B[j][i];
		}
	}
}

void prodotto(vector<vector<double>>Bt, vector<vector<double>>B, vector<vector<double>>&A){	//calcolo del prodotto fra due matrici
	double sum = 0;
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {	
			sum = 0;
			for(int k = 0; k < n; k++)
				sum += B[i][k]*Bt[j][k];
			A[i][j]=sum;
		}
	}
}

int Tr(vector<vector<double>>A){	
	double sum = 0;
	for(int i = 0; i < n; i++) {
		 sum+=A[i][i];
	}
	return sum;
}

vector<double> rademacher(){
	vector<double> u;
	int r[]={1,-1};
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	for (int i=0; i<n; i++){
		u.push_back(r[rand()%2]);
	}
	 shuffle(u.begin(), u.end(), rng);// rimescolo il vettore così ne avrò uno diverso ad ogni iterazione
    return u;
}

vector<double> prodottovet_mat(vector<vector<double>>A, vector<double>u){//prodotto vettore matrice
	double sum = 0;
	vector <double> ua;

	for(int i = 0; i < A.size(); i++) {
		sum = 0;
		for (int j = 0; j < u.size(); j++) 
			sum += u[j]*A[i][j];
		ua.push_back(sum);
	}
	return ua;
}
double prodottoX(vector<double>uA, vector<double>u){//prodotto di due vettori
	double sum = 0;
    	for (int i = 0; i < n; i++) 
        	sum += u[i]*uA[i];
    	return sum;
}

double varianza(vector<vector<double>>a)//∑(xi-x)^2/n
{	double var=0;
	for (int i = 0; i < n ; i++){
		for(int j = 0; j < i; j++){
			var += pow(a[i][j], 2);
		}
	}
	return var;
}

double frobenius(vector<vector<double>> A){
	double sum = 0;
	for (int i = 0; i < n ; i++){
		for(int j = 0; j < n; j++){
			sum += pow(A[i][j], 2);
		}
	}
	return sum;
}

