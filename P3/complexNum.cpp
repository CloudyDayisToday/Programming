#include <iostream>
#include <cmath>
#include "complexNum.h"

using namespace std;

void Circuit::input(complexNum& voltage){
	cout<<"This is a program which helps you to calculate the current for a series RLC circuit."<<endl;
	cout<<"<Please be aware that the values you enter should always be positive!>"<<endl;
	cout<<"Total resistance(ohm): ";
	cin>>R;
	cout<<"Total inductance(H): ";
	cin>>L;
	cout<<"Total capacitance(F): ";
	cin>>C;
	cout<<"Frequency: ";
	cin>>f;
	cout<<"Voltage source(V): ";
	cin>>voltage.r;
}
double Circuit::resistor(){
	return R;
}
double Circuit::ang_frequency(){
	double omega;
	omega = 2*PI*f;
	return omega;
}

double Circuit::inductor(){
	double impedance;
	impedance = ang_frequency()*L;
	return impedance;
}
double Circuit::capacitor(){
	double impedance;
	impedance = -1/(ang_frequency()*C);
	return impedance;
}

double Circuit::i_impedance(){
	return inductor()+ capacitor();
}


const complexNum complexNum::operator+(const complexNum& v2)
{
	complexNum ans;
	ans.r = this->r + v2.r;
	ans.i = this->i + v2.i;
	return ans;
}

const complexNum complexNum::operator-(const complexNum& v2)
 {
	 complexNum ans;
	 ans.r = this->r - v2.r;
	 ans.i = this->i - v2.i;
	 return ans;
 }

 const complexNum complexNum::operator*(const complexNum& v2)
 {
	 complexNum ans;
	 ans.r = this->r*v2.r - this->i*v2.i;
	 ans.i = this->r*v2.i + this->i*v2.r;
	 return ans;
 }
 
 const complexNum complexNum::operator/(const complexNum& v2)
 {
	 complexNum ans;
	 ans.r = (this->r*v2.r + this->i*v2.i)/(pow(v2.r,2)+pow(v2.i,2));
	 ans.i = (this->i*v2.r - this->r*v2.i)/(pow(v2.r,2)+pow(v2.i,2));
	 return ans;
 }
 
 bool complexNum::operator==(const complexNum& v2)
 {
	 if((this->r==v2.r)&&(this->i==v2.i)) return true;
	 else return false;
 }
 
 