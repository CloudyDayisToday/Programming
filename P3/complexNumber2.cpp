#include <iostream>
#include <complex>
#include "complexNum.cpp"


using namespace std;

 int main(){
	Circuit circuit;
	complexNum voltage, impedance, current;
	/*Read values in*/
	circuit.input(voltage);
	/*calculate the real part of the impedance and store it in complex form*/
	impedance.r = circuit.resistor();
	/*calculate the imagiary part of the impedance and store it in complex form*/
	impedance.i = circuit.i_impedance();
	cout<<"Total impedance: "<<impedance.r<<"+j("<<impedance.i<<")"<<endl;
	current = voltage/impedance;
	complex<double> complexCurrent (current.r,current.i);
	cout<<"Current: "<<current.r<<"+j("<<current.i<<")"<<endl;
	cout<<"The phase difference between the voltage source and current: "<<-arg(complexCurrent);
	return 0;
 }
 
