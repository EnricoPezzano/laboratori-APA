#include<iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include<fstream>

using namespace std;

int confronti = 0;
int valoreMedio(int iter, vector <int>seq);
vector < int > creaSeq();
void scambia (vector < int >&v, int i, int j);
int QuickSort (vector < int >&v, int inizio, int fine);
void LVqs (vector < int >&v, int inizio, int fine);
void mergeSort(vector<int>);
int LVQuickSort (vector < int >&v);
int main();