#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double diff_1(double x, double h, double (*func)(double)) //Equation 1
{
	return (func(x+h) - func(x-h))/(2*h);
}

double diff_2(double x, double h, double (*func)(double)) //Equation 2
{
	return (4/3.)*diff_1(x,h/2,func) - (1/3.)*diff_1(x,h,func);
}

double fx(double x)
{
	return x - pow(sin((3*M_PI*x)/2),2);
}

double gx(double x)
{
	return tan(x);
}

double deriv(double x, double h, double (*func)(double), int order)
{
	switch(order)
	{
		case 1:
			return diff_1(x, h, func);
		case 3:
			return diff_2(x, h, func);
		default:
			cout << "Error : wrond order !" << endl;
			break;
	}
}

//Can't work for x = pi/2 for g(x) because cos(pi/2) = 0 => g(x) doesn't exist

int main()
{	
	double devF_0 = 1; //Derivative of f(x) at x = 0
	double devG_0 = 1; //Derivative of g(x) at x = 0
	
	for(int i  = 1; i < 250; i++)
	{
		cout << "Loop start for f(x)" << endl;
		double h = 0.5/double(i);
		cout << " h = " << h << endl;
		double x = 0;
		cout << "Derivative first order of f(x) : " << deriv(x, h, fx, 1) << endl;
		cout << "Derivative third order of f(x) : " << deriv(x, h, fx, 3) << endl;
		if(abs(deriv(x, h, fx, 1) - devF_0) < 1/1000.) //If it stops for order 1, it's good for order 3 as well
		{
			cout << "f(x) : less than .1 percent of difference for h = " << h << " at x = " << x << endl;
			cout << endl;
			break;
		}
	}

	for(int i = 1; i < 250; i++)
	{
		cout << "Loop start for g(x)" << endl;
		double h = 0.5/double(i);
		cout << " h = " << h << endl;
		double x = 0;
		cout << "Derivative first order of g(x) : " << deriv(x, h, gx, 1) << endl;
		cout << "Derivative third order of g(x) : " << deriv(x, h, gx, 3) << endl;
		if(abs(deriv(x, h, gx, 1) - devG_0) < 1/1000.) //If it stops for order 1, it's good for order 3 as well
		{
			cout << "g(x) : less than .1 percent of difference for h = " << h << " at x = " << x << endl;
			break;
		}
	}
}
