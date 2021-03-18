#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <random>
#include <complex>
#include "complex.cpp"

using namespace std;

//This is for seeding the random generator.
std::random_device rd;

void generator(vector<complexNum> &matrix, int n);
void multiply(vector <complexNum> &mat, vector <vector<complexNum>> &mat1, vector <complexNum> &mat2, int n);
complexNum T_generator(vector <vector<complexNum>> &mat, vector<complexNum> &d, int n);
vector<complexNum> TridiagonalSolve(complexNum E, vector<complexNum> D, vector<complexNum> R, vector<complexNum> L, int n);


/*This code is used to generate arrays*/
complexNum T_generator(vector <vector<complexNum>> &mat, vector<complexNum> &d, int n){
	std::default_random_engine dre;
	std::uniform_real_distribution<double> dr(10,20);
	complexNum e = {dr(dre),dr(dre)};
	for(int i=0;i<n; i++){
		d[i] = {dr(dre),dr(dre)};
	}
	
	for(int i=0; i<n;i++){
		for(int j=0; j<n; j++){
			if(i==j)
				mat[i][j] = d[i];
			else if((i-j)==1||(j-i)==1)
				mat[i][j] = e;
			else
				mat[i][j].reset();
			
		}
	}
	return e;
}

void generator(vector <complexNum> &mat, int n){
	std::default_random_engine dre;
	std::uniform_real_distribution<double> dr(10,20);
	for(int i=0; i<n;i++){
		mat[i]={dr(dre),dr(dre)};
	}
}

/*This is used to multiply 2 arrays produce a new one.*/
void multiply(vector <complexNum> &mat, vector <vector<complexNum>> &mat1, vector <complexNum> &mat2, int n){
	int k = 0;
	complexNum temp;
	for(int i=0; i<n; i++){
		temp.reset();
		k=0;
		while(k<n){
			temp = temp + mat1[i][k]*mat2[k];
			k++;
		}
		mat[i] = temp;
	}
}


vector<complexNum> TridiagonalSolve(complexNum E, vector<complexNum> D, vector<complexNum> R, vector<complexNum> L, int n){
	int i,j;
	vector<complexNum> c;
	complexNum id;
	/*set the off diagonal elements*/
	for(i=0; i<n; i++)
		c.push_back(E);
	
	/*forward bit*/
	c[0]=c[0]/D[0]; /*if /0 rearrange equations*/
	R[0]=R[0]/D[0];
	
	for(j=1; j<n ;j++){
		id = D[j] - c[j-1]*E;
		c[j] = c[j]/id; /*Last value calculated is redundant*/
		R[j] = (R[j] - R[j-1]*E) / id;
	}
	
	
	/*Now back substitute.*/
	L[n-1] = R[n-1];
	
	for(j=n-2; j>=0; j--){
		L[j] = R[j] - c[j]*L[j+1];
	}
	
	return L;
	
}