#include <iostream>
#include <iomanip>
#include <vector>
#include "complexFunction.cpp"

using namespace std;


int main(){
	int n = 4;
	vector <vector<complexNum>> T(n,vector<complexNum>(n));
	vector <complexNum> D(n), R(n),L(n), S(n);
	complexNum E = T_generator(T, D, n);
	generator(L, n);
	
	multiply(R, T, L, n);
	cout<<"The tridiagonal matrix:"<<endl;
	
	for(auto i:T){
		for(auto j:i)
			cout<<setw(15)<<j.getReal()<<" + j("<<j.getImag()<<")";
		cout<<endl;
	}
	
	cout<<"----------------------"<<endl<<"The second matrix:"<<endl;

	for(auto j:L)
		cout<<setw(15)<<j.getReal()<<" + j("<<j.getImag()<<")";
	cout<<endl;
	
	cout<<"----------------------"<<endl<<"The multiplied matrix:"<<endl;
	
	for(auto j:R)
		cout<<setw(15)<<j.getReal()<<" + j("<<j.getImag()<<")";
	cout<<endl;
	
	S = TridiagonalSolve(E, D, R, L, n);
	
	cout<<"----------------------"<<endl<<"The matrix that is solved by tridiagonal function:"<<endl;
	for(auto j:S)
		cout<<setw(15)<<j.getReal()<<" + j("<<j.getImag()<<")";
	return 0;

}

