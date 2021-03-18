#ifndef NUM
#define NUM
#define PI 3.14159
class complexNum{
	public:	
		double r, i, angle;
		/*assign the real part of a complex number to r and imaginary part to i*/
		complexNum(double real, double imaginary){
			r = real;
			i = imaginary;
			
		}
		complexNum(){
			r = 0; i = 0;
		}
		void phaseAngle();
		const complexNum operator +(const complexNum& v2);
		const complexNum operator -(const complexNum& v2);
		const complexNum operator *(const complexNum& v2);
		const complexNum operator /(const complexNum& v2);
		bool operator ==(const complexNum& v2);
 };
 
 class Circuit{
	 public:
		double V,R,L,C,f;
		Circuit(){
			V = 0; R = 0; L = 0; C = 0; f = 0;
		}
		void input(complexNum& voltage);
		double resistor();
		double ang_frequency();
		double inductor();
		double capacitor();
		double i_impedance();
 };

#endif