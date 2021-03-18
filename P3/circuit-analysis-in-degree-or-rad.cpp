#include <iostream>
#include <complex>
#include "complex.cpp"


using namespace std;

 int main(){
	char unit,form;
	string a, b;
	Circuit circuit;
	complexNum voltage, impedance, current;
	Angle diffAngle;
	
	/*To check whether the input/output angle should be in radian or degree form*/
	cout<<"Do you want this system to work in radian or degree? (R or D): ";
	cin>>unit;
	
	/*To check whether the input/output should be in polar or cartesian form*/
	cout<<"Do you want this system to work in polar form or cartesian form? (P or C): ";
	cin>>form;
	
	/*Read values in*/
	circuit.input(voltage, unit, form);
	
	/*store the impedance in complex form*/
	impedance = {circuit.resistor(),circuit.i_impedance()};
	cout<<"Total impedance: "<<impedance.getReal()<<"+j("<<impedance.getImag()<<")"<<endl;
	
	current = voltage/impedance;
	diffAngle = {voltage.getAngle() - current.getAngle()};
	
	cout<<"-----------------------------------------------------------------------"<<endl;
	if (form=='P') a = "polar";
		else a = "cartesian";
	if (unit == 'R') b = "radian";
		else b = "degree";
	
	cout<<"The following outputs are in "<<a<<" form and the angle is in "<<b<<endl;
	
	if(unit=='D') diffAngle.radian_to_angle();
	current.output(unit, form);
	
	return 0;
 }
 
