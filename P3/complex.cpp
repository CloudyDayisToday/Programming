#include <iostream>
#include <cmath> /* for pow()*/
#include <complex>
#define PI 3.14159
using namespace std;

class Angle{
	public:
		Angle(double angle){
			ang = angle;
		}
		Angle(){ ang =0;}
		void degree_to_radian();
		void radian_to_angle();
		double getAng()const;
		
	private:
		double ang;
};

class complexNum{
	public:			
	/*assign the real part of a complex number to r and imaginary part to i*/
		complexNum(double real,double imaginary){
			r = real;
			i = imaginary;
		}
		complexNum(double mag, Angle ang){
			r = real(polar(mag,ang.getAng()));
			i = imag(polar(mag,ang.getAng()));
			angle = ang;
		}
		complexNum(){
			r = 0;
			i = 0;
		}
		double getReal()const ;
		double getImag()const ;
		Angle getAngle()const;
		void storeReal(double real);
		void storeImag(double imag);
		void storeAngle(Angle ang);
		void output(char unit, char form);
		void phase();
		
	private:
		double r;
		double i;
		Angle angle;
};

class Circuit{
	 public:
		double V,R,L,C,f;
		Circuit(){
			V = 0; R = 0; L = 0; C = 0; f = 0;
		}
		void input(complexNum& voltage, char unit, char form);
		double resistor();
		double ang_frequency();
		double inductor();
		double capacitor();
		double i_impedance();
 };
 
/*-------------------------------------------------------------------*/
/*declaring the functions which overload operators*/
const complexNum operator +(const complexNum& v1,const complexNum& v2);
const complexNum operator -(const complexNum& v1,const complexNum& v2);
const complexNum operator *(const complexNum& v1,const complexNum& v2);
const complexNum operator /(const complexNum& v1,const complexNum& v2);
bool operator ==(const complexNum& v1,const complexNum& v2);

/*--------------------------------------------------------------------*/
/*public functions of class circuit are defined here.*/
/*read in all the neccessary values*/
void Circuit::input(complexNum& voltage, char unit, char form){
	double a,b;
	cout<<"This is a program which helps you to calculate the current for a series RLC circuit."<<endl;
	cout<<"<Please be aware that the values you enter should always be positive!>"<<endl;
	cout<<"Total resistance(ohm): ";
	cin>>R;
	cout<<"Total inductance(H): ";
	cin>>L;
	cout<<"Total capacitance(F): ";
	cin>>C;
	cout<<"Frequency(Hz): ";
	cin>>f;
	switch(form){
		case 'C': 
			cout<<"Real part of the voltage: ";
			cin>>a;
			cout<<"Imaginary part of the voltage: ";
			cin>>b;
			voltage = {a,b};
			break;
		case 'P':
			Angle temp;
			cout<<"The magnitude of the voltage: ";
			cin>>a;
			cout<<"The angle of the voltage: ";
			cin>>b;
			temp = b;
			if(unit=='D') temp.degree_to_radian();
			voltage = {a,temp};
			break;
	}
	
}
/*store the total resistance*/
double Circuit::resistor(){
	return R;
}
/*compute the angular frequency of the circuit by a given frequency value*/
double Circuit::ang_frequency(){
	double omega;
	omega = 2*PI*f;
	return omega;
}
/*calculate inductive impedance*/
double Circuit::inductor(){
	double impedance;
	impedance = ang_frequency()*L;
	return impedance;
}
/*calculate capacitive impedance*/
double Circuit::capacitor(){
	double impedance;
	impedance = -1/(ang_frequency()*C);
	return impedance;
}
/*Caluculate the imaginary part of the impedance*/
double Circuit::i_impedance(){
	return inductor()+ capacitor();
}
/*--------------------------------------------------------------------*/
/*Public functions of class complexNum are defined here*/
/*These are functions that retrieve private members' values*/
double complexNum::getReal()const {
	return r;
}
double complexNum::getImag()const { 
	return i;	
}
Angle complexNum::getAngle()const{
	return angle;
}
/*These are functions that store values to private members*/
void complexNum::storeReal(double real){
	r = real;
}
void complexNum::storeImag(double imag){
	i = imag;
}
void complexNum::storeAngle(Angle ang){
	angle = ang;
}
/*This calculate the phase of the complex number*/
void complexNum::phase(){
	complex<double> temp(r,i);
	angle = arg(temp);
}
/*This output the final calculation*/
void complexNum::output(char unit, char form){
	phase();
	/*This check whether to output the angle in radian or degree form.*/
	complex <double> complex(r,i);
	if(unit == 'D')	angle.radian_to_angle();
	if(form == 'P')	cout<<"Current: "<<abs(complex)<< "/_"<<angle.getAng()<<endl;
	else			cout<<"Current: "<<r<<"+j("<<i<<")"<<endl;
	
}

/*-----------------------------------------------------------------*/
/*All functions for angle defined here.*/
void Angle::degree_to_radian(){
	ang = ang*2*PI/180;
}

void Angle::radian_to_angle(){
	ang = ang*180/(2*PI);
}

double Angle::getAng()const{
	return ang;
}

/*------------------------------------------------------------------*/
/*All functions for overloading operators are declared here.*/
const complexNum operator+(const complexNum& v1,const complexNum& v2)
{
	complexNum ans;
	ans.storeReal(v1.getReal() + v2.getReal());
	ans.storeImag(v1.getImag() + v2.getImag());
	return ans;
}
const Angle operator+(const Angle& a1,const Angle& a2)
{
	Angle ans;
	return ans = a1.getAng() + a2.getAng();
}

const complexNum operator-(const complexNum& v1,const complexNum& v2)
 {
	 complexNum ans;
	 ans.storeReal(v1.getReal() - v2.getReal());
	 ans.storeImag(v1.getImag() - v2.getImag());
	 return ans;
 }
 const Angle operator-(const Angle& a1,const Angle& a2)
{
	Angle ans;
	return ans = a1.getAng() - a2.getAng();
}

 const complexNum operator*(const complexNum& v1,const complexNum& v2)
 {
	 complexNum ans;
	 ans.storeReal (v1.getReal()*v2.getReal() - v1.getImag()*v2.getImag());
	 ans.storeImag (v1.getReal()*v2.getImag() + v1.getImag()*v2.getReal());
	 ans.storeAngle (v1.getAngle()+v2.getAngle());
	 return ans;
 }
 
 const complexNum operator/(const complexNum& v1,const complexNum& v2)
 {
	 complexNum ans;
	 ans.storeReal((v1.getReal()*v2.getReal() + v1.getImag()*v2.getImag())/(pow(v2.getReal(),2)+pow(v2.getImag(),2)));
	 ans.storeImag((v1.getImag()*v2.getReal() - v1.getReal()*v2.getImag())/(pow(v2.getReal(),2)+pow(v2.getImag(),2)));
	 ans.storeAngle(v1.getAngle()-v2.getAngle());
	 return ans;
 }
 
 bool operator==(const complexNum& v1,const complexNum& v2)
 {
	 return (v1.getReal()==v2.getReal())&&(v1.getImag()==v2.getImag());
 }
