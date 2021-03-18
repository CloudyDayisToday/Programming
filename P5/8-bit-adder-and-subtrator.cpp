#include <iostream>
#include <bitset>
#define N 8
using namespace std;

class Gates{
	public:
		Gates();
		int AND(int x, int y);
		int OR(int x, int y);
		int XOR(int x, int y);
};

Gates::Gates(){}

/*Basic logic gate functions*/
int Gates::AND(int x, int y){
	return (x&y);
}

int Gates::OR(int x, int y){
	return (x|y);
}

int Gates::XOR(int x, int y){
	return (x^y);
}


class halfAdder:public Gates{
	public:
		halfAdder();
		void halfAdderFunc(int x, int y);
		int getSum_H();
		int getCarry_H();
	private:
		int sum_H;
		int cout_H;
};

halfAdder::halfAdder():Gates(),sum_H(0),cout_H(0){}

void halfAdder::halfAdderFunc(int a, int b){
	sum_H = XOR(a,b);
	cout_H = AND(a,b);
	cout<<"Sum_H: "<<sum_H<<" coutH: "<<cout_H;
}

int halfAdder::getSum_H(){ return sum_H;}
int halfAdder::getCarry_H(){ return cout_H;}
	
class fullAdder:public halfAdder{
	public:
		fullAdder();
		void fullAdderFunc(int c_in, int a, int b);
		int getSum_F();
		int getCarry_F();
	private:
		int sum_F;
		int cout_F;
};

fullAdder::fullAdder():halfAdder(),sum_F(0),cout_F(0){}

void fullAdder::fullAdderFunc(int c_in, int a, int b){
	halfAdderFunc(a, b);
	sum_F = XOR(getSum_H(),c_in);
	cout_F = OR(AND(getSum_H(),c_in),getCarry_H());
	cout<<"Sum_F: "<<sum_F<<" coutF: "<<cout_F;
}
int fullAdder::getSum_F(){ return sum_F;}
int fullAdder::getCarry_F(){ return cout_F;}

class rippleCounter:fullAdder{
	public:
		rippleCounter();
		int rippleCounterFunc(int c_in);
		bitset<N> getVar(char c);
		bool getOverflow();
		void checkOverflow();
		void storeX(int A);
		void storeY(int B); 
	private:
		bitset<N> X, Y, S;
		int c_in;
		bool overflow;
};

rippleCounter::rippleCounter():fullAdder(),X(0),Y(0),S(0){}

bitset<N> rippleCounter::getVar(char c){
	switch (c){
		case 'X': return X; break;
		case 'Y': return Y; break;
		case 'S': return S; break;
	}
	return 0;
}

bool rippleCounter::getOverflow(){ return overflow;}
void rippleCounter::checkOverflow(){
	int k = N-1;
	if(X[k]==0&&Y[k]==0&&getSum_F()==1) overflow=true;
	else if(X[k]==1&&Y[k]==1&&getSum_F()==0) overflow=true;
}

int rippleCounter::rippleCounterFunc(int c_in){
	int a, b;
	for(int i=0; i<N; i++){
		a = X[i];
		b = Y[i];
		fullAdderFunc(c_in, a, b);
		S[i] = getSum_F();
		cout<<" X: "<<a;
		cout<<" Y: "<<b;
		cout<<" S: "<<S[i]<<endl;
	}
	return getCarry_F();
}
void rippleCounter::storeX(int A) {
	X = A;
}
void rippleCounter::storeY(int B) {
	Y = B;
}


class Adder:public rippleCounter{
	public:
		Adder();
		void adderFunc(int c_in, int A, int B);
		bitset<N> flip(bitset<8> num);
};

Adder::Adder():rippleCounter(){}

bitset<N> Adder::flip(bitset<8> num){
	int temp= (int)num.to_ulong();
	temp--;
	num = temp;
	num.flip();
	return num;
}



void Adder::adderFunc(int c_in, int A, int B){
	storeX(A); storeY(B);
	int carry = rippleCounterFunc(c_in);
	checkOverflow();
	bitset<N> output = getVar('S');
	cout<<"You perform an addition operation:"<<endl;
	if(output[N-1] == 1){
		output = flip(output);
		cout<<" This is a negative number, need to convert from 2's complement to decimal."<<endl;
		cout<<output<<endl<<"The decimal equavalent is: "<<"-"<<output.to_ulong()<<endl;
	}else
		cout<<"The binary value of the result: "<<output<<endl<<"The decimal equivalent is "<<output.to_ulong()<<endl;
	cout<<"Carry = "<<carry<<" Overflow = "<<getOverflow();
}


/*main function*/
int main(){
	bitset<N> a, b;
	int x, y, c_in;
	char sign;
	cout<<"Input your first binary number: ";
	cin>>x;
	cout<<"Input you second binary number: ";
	cin>>y;
	cout<<"Select operation (+ or -): ";
	cin>>sign;
	cout<<x<<sign<<"("<<y<<")"<<endl;
	a = x; b = y;
	cout<<"Corresponding value A in binary: "<<a<<endl;
	cout<<"Corresponding value B in binary: "<<b<<endl;
	cout<<"C_In Value is: ";
	cin>>c_in;
	
	Adder add;
	add.adderFunc(c_in,x,y);
}












