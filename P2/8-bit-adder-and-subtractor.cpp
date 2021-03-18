#include <iostream>
#include <bitset>
#define N 8
using namespace std;

class RippleCounter{
	public:
		void input();
		void output();
		void flip(bitset<8> &num);
		void AND(int x, int y);
		void OR (int x, int y);
		void XOR (int x, int y);
		void fullAdder();
		void checkSign();
		void rippleCounter();
	private:
		int x, y, c_in, c_out, halfSum, sum, and1, and2, output;
		char sign;
		bitset<N> A, B; //value in binary format
		bool overflow = false;
};


int main(){
	RippleCounter counter;
	counter.input();
	counter.checkSign();
	counter.rippleCounter();
	counter.output();
	
}

/*read all the values in*/
void RippleCounter::input(){
	int a,b;
	cout<<"Input your first binary number: ";
	cin>>a;
	cout<<"Input you second binary number: ";
	cin>>b;
	cout<<"Select operation (+ or -): ";
	cin>>sign;
	cout<<a<<sign<<"("<<b<<")"<<endl;
	A = a; B = b;
	cout<<"Corresponding value A in binary: "<<A<<endl;
	cout<<"Corresponding value B in binary: "<<B<<endl;
	cout<<"C_In Value is: ";
	cin>>c_in;
}

/*check if needs to flip the second number*/
void RippleCounter::checkSign(){
	if(((B<0)&&(sign=='-')) || ((B>0)&&(sign=='-'))){
		flip(B);
	}
}

/*conversion between positive and negative number*/
void RippleCounter::flip(bitset<8> &num){
	int temp=num;
	temp--;
	num = temp;
	num.flip();
}

/*start all the operations*/
void RippleCounter::rippleCounter(){
	for(i=0; i<N; i++){
		x = A[i];
		y = B[i];
		fullAdder();
		c_in = c_out;
		output += sum<<i;
	}
}

/*this function operates the procedure of a fulladder*/
void RippleCounter::fullAdder(){
	halfSum = XOR(x,y);
	sum = XOR (halfSum,c_in);
	and1 = AND (halfSum,c_in);
	and2 = AND (x,y);
	c_out = OR (and1, and2);
}

/*AND gate*/
void RippleCounter::AND(){
	return (x&y);
}

/*OR gate*/
void RippleCounter::OR (){
	return (x|y);
}

/*XOR gate*/
void RippleCounter::XOR(){
	return (x^y);
}


/*Output data*/
void RippleCounter::output(){
	/*Decting if the result is negative or positive*/
	bitset<N> O=output;
	if (sum==1){
		flip(O);
		cout<<"Its a negative number, need to convert from 2's complement to decimal."<<endl;
		cout<<O<<endl<<"The decimal equivalent is "<<"-"<<(int)O.to_ulong()<<endl;
	}else{
		cout<<"The binary value of the result: "<<O<<endl<<"The decimal equivalent is "<<(int)O.to_ulong()<<endl;
	}
	

	
	cout<<"Carry = "<<c_out<<" Overflow = "<<overflow;
}

