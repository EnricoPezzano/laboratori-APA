#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>
#include <fstream>
#define n 4

using namespace std;
/*----------------------Dichiarazione delle funzioni--------------------*/
void trasmissione(vector<vector<int>>&);
int lancio_moneta();
void giri(vector<vector<int>>&);
int tally(vector<vector<int>>, int, int);
int maj(vector<vector<int>>, int);
int diagonale(vector<vector<int>>);
float media(vector<int>);
float varianza(float, vector<int>);
int prob(vector<int>, int, float);

/*------------------Funzioni-----------------*/

//lancio della moneta globale con probabilità Pr(testa)=Pr(croce)=1/2
int lancio_moneta(){
	return rand()%2;
}

//trasmissione del bit i-esimo ai n-1 processi e scelta opposta per il processo inaffidabile
void trasmissione(vector<vector<int>> &generali){
	int s;
	s=0;
	for(int i=0; i<n-1; i++){
		if(i==0){
			for(int j=0; j<n-1; j++){
				generali[i][j]=rand()%2;
			}
		}
		generali[i]=generali[0];
		generali[i][n-1]=1-generali[i][s];//processo inaffidabile
		s++;
	}
}

//numero dei valori uguali al valore maggioritario
int tally(vector<vector<int>>generali, int maj, int i){
	int tally=0;

	for(int j=0; j<n; j++){
		if (generali[i][j]==maj)
			tally++;
	}

	return tally;
}


//valore maggioritario tra quelli ricevuti dai generali
int maj(vector<vector<int>>generali, int i){
	int counter, maj;
	counter=0;
	for(int j=0; j<n; j++){
		if (generali[i][j]==1)
			counter++;
	}

	if(counter==2) maj=rand()%2;
	if(counter>2) maj=1;
	else maj=0;
	return maj;

}

//conta dell'accordo raggiunto
int diagonale(vector<vector<int>>generali){
	int diag= 0;

	for(int i=0; i<n-1;i++)
	{
		for(int j=0; j<n-1; j++)
		{
			if(i==j)
			{
				if (generali[i][j]==1)
					diag+=generali[i][j];
			}
		}
	}

	return diag; 
}

//round 
void giri(vector<vector<int>> &generali){

	int majj, a, k;
	int moneta=lancio_moneta();
	a=0;
	k=0;
	for(int i=0; i<n-1;i++){
		if(i==0){
			for(int j = 0; j < n-1; j++){
				majj=maj(generali, k);
			if(tally(generali,majj,k)>=n-1)
				generali[0][j]=majj;
			else 
				generali[0][j]=moneta; 
			k++;
			}
		}
		generali[i]=generali[0]; 
		generali[i][n-1]=1-generali[i][a]; 
		a++;
	}

}

int count(vector<int>round, int r)
{
	int c=0;
	for(int i=0;i< round.size(); i++)
	{
		if(round.at(i)==r)
		c++;
	}
	return c;
}


int prob(vector<int> round, int rip, float med){
	float sum;
	sum=0; 
	vector<int>conta(rip);
	for(int i=0; i< round.size(); i++)
	{
		conta.at(round.at(i))++;
	}
	int x=0;
	while(x<conta.size() && sum<rip*0.999)
	{
		sum+=conta.at(x);
		x++;
	}

	return x;
}

float media(vector<int>round)
{ 
	float sum, med;
	for (int i=0; i<round.size(); i++)
	{
		sum+=round.at(i);
	}
	med=sum/round.size();
	return med;
}


float varianza(float med, vector<int>round)//∑(xi-x)^2/n
{
	float sum, sumq, var;
	for(int i=0; i< round.size(); i++)
	{
		sum+=pow(round.at(i)-med,2);
	}
	var=sum/round.size();
	return var;
}

int main(){
	srand(time(NULL));
	vector <int> gen(n);
	vector<vector<int>>generali(n-1, gen); 
	vector<int>round; 
	int nr, rip;
	rip=pow(10,4);

	for (int i = 0; i < rip; i++){
		nr=0;
		trasmissione(generali); 
		while (diagonale(generali)!=n-1 && diagonale(generali)!=0 )//finchè non si raggiunge l'accordo si ripetono i giri/round 
		{ 
			giri(generali);
			nr++;//si incrementa numero di round
		}
		round.push_back(nr); //si aggiungono in un vettore il numero di round necessario per raggiungere un accordo
	} 

	float med=media(round);
	cout << "La media è: " << med << endl;
	cout << "La varianza è: " << varianza(med,round) << endl;
	cout << "Il numero di round dopo il quale la probabilità che l'accordo venga raggiunto sia più grande del 99.9%: " << prob(round, rip, med) << endl;

}
