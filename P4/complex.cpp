#include <iostream>
#include <cmath> /* for pow()*/
#include <complex>
#define PI 3.14159
using namespace std;

class complexNum{
	public:			
	/*assign the real part of a complex number to r and imaginary part to i*/
		complexNum(double real,double imaginary){
			r = real;
			i = imaginary;
		}
		complexNum(){
			r = 0;
			i = 0;
		}
		double getReal()const ;
		double getImag()const ;
		void storeReal(double real);
		void storeImag(double imag);
		void reset();

		
	private:
		double r;
		double i;

};


/*-------------------------------------------------------------------*/
/*declaring the functions which overload operators*/
const complexNum operator +(const complexNum& v1,const complexNum& v2);
const complexNum operator -(const complexNum& v1,const complexNum& v2);
const complexNum operator *(const complexNum& v1,const complexNum& v2);
const complexNum operator /(const complexNum& v1,const complexNum& v2);
bool operator ==(const complexNum& v1,const complexNum& v2);


/*--------------------------------------------------------------------*/
/*Public functions of class complexNum are defined here*/
/*These are functions that retrieve private members' values*/
double complexNum::getReal()const {
	return r;
}
double complexNum::getImag()const { 
	return i;	
}

/*These are functions that store values to private members*/
void complexNum::storeReal(double real){
	r = real;
}
void complexNum::storeImag(double imag){
	i = imag;
}
void complexNum::reset(){
	r = 0; i = 0;
}



/*All functions for overloading operators are declared here.*/
const complexNum operator+(const complexNum& v1,const complexNum& v2)
{
	complexNum ans;
	ans.storeReal(v1.getReal() + v2.getReal());
	ans.storeImag(v1.getImag() + v2.getImag());
	return ans;
}
const complexNum operator-(const complexNum& v1,const complexNum& v2)
 {
	 complexNum ans;
	 ans.storeReal(v1.getReal() - v2.getReal());
	 ans.storeImag(v1.getImag() - v2.getImag());
	 return ans;
 }

 const complexNum operator*(const complexNum& v1,const complexNum& v2)
 {
	 complexNum ans;
	 ans.storeReal (v1.getReal()*v2.getReal() - v1.getImag()*v2.getImag());
	 ans.storeImag (v1.getReal()*v2.getImag() + v1.getImag()*v2.getReal());
	 return ans;
 }
 
 const complexNum operator/(const complexNum& v1,const complexNum& v2)
 {
	 complexNum ans;
	 ans.storeReal((v1.getReal()*v2.getReal() + v1.getImag()*v2.getImag())/(pow(v2.getReal(),2)+pow(v2.getImag(),2)));
	 ans.storeImag((v1.getImag()*v2.getReal() - v1.getReal()*v2.getImag())/(pow(v2.getReal(),2)+pow(v2.getImag(),2)));
	 return ans;
 }
 
 bool operator==(const complexNum& v1,const complexNum& v2)
 {
	 return (v1.getReal()==v2.getReal())&&(v1.getImag()==v2.getImag());
 }
