#include <iostream>
#include <bitset>
#define N 4
using namespace std;

/*Declare variables that will be used in full adder operation*/
struct Adder{
	bool x, y, c_in, c_out, halfSum, sum, and1, and2;
};

int AND(int x, int y);
int OR (int x, int y);
int XOR (int x, int y);

/*It implements functions inside a full adder*/
Adder fullAdder(Adder a);

/*multiplying A with one of the bits in B*/
bitset<N> multiply(bitset<N> A, int B);


int main(){
	bitset<N> A(8),B(8); //The numbers used in the calculation is initiated here!!!
	bitset<N> temp1, temp2, adderO(0);
	bitset<2*N> P;
	Adder number;
	
	/*declare that the initial carry_in and carry_out is 0*/
	number.c_in = 0, number.c_out = 0;;
	
	for(int i=0; i<N-1; i++){
		/*store the result of multiplication between a bit of B and A in temp1*/
		temp1= multiply(A,B[i+1]);
		for(int j=0; j<N; j++){
			if(i==0){
				temp2 = multiply(A,B[i]);
				if(j<3) number.y = temp2[j+1];
				else number.y = number.c_out;
				P[i]=temp2[0];
			}else{
				if(j<3) number.y = adderO[j+1];
				else number.y = number.c_out;
			}
			number.x = temp1[j];
			number = fullAdder(number);
			number.c_in = number.c_out;
			adderO[j] = number.sum;
		}
		P[i+1] = adderO[0];

	}
	
	/*assign the last adder result into the output array*/
	for(int i=0; i<N-1; i++){
		P[i+N] = adderO[i+1];	
	}
	P[2*N-1]=number.c_out;
	cout<<"The first number: "<<(int)A.to_ulong()<<endl;
	cout<<"The second number: "<<(int)B.to_ulong()<<endl;
	cout<<"The result of multiplying the first and second number: "<<P.to_ulong()<<endl;
	return 0;
}


int AND(int x, int y){
	return (x&y);
}

int OR (int x, int y){
	return (x|y);
}

int XOR(int x, int y){
	return (x^y);
}

Adder fullAdder(Adder a){
	a.halfSum = XOR(a.x,a.y);
	a.sum = XOR (a.halfSum,a.c_in);
	a.and1 = AND (a.halfSum,a.c_in);
	a.and2 = AND (a.x,a.y);
	a.c_out = OR (a.and1, a.and2);
	return a;
}


bitset<N> multiply(bitset<N> A, int B){
	bitset<N> C;
	for(int i=0; i<N; i++){
		C[i]=AND(A[i],B);
	}
	return C;
}