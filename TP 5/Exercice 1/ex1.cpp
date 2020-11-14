#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

double fty(double y, double gamma)
{
	return -gamma*y;
}

double f_ana(double t, double gamma, double t0, double y0) //t0 = 1
{
	return y0*exp(gamma*(t0 - t));
}

double* Euler_1(double gamma, double y0, double h, int N)  //t = a+h*i, implements advanced scheme
{
	double* tab = new double[N+1];
	tab[0] = y0;

	for(int i = 0; i < N; i++)
	{
		tab[i+1] = tab[i] + h*fty(tab[i], gamma);
	}
	return tab;
}

double* Euler_2(double gamma, double y0, double h, int N) //Implements delayed scheme
{
	double* tab = new double[N+1];
	tab[0] = y0;

	for(int i = 1; i < N+1; i++)
	{
		tab[i] = tab[i-1]/(1 + gamma*h);
	}
	return tab;
}

double stable(double gamma, double y0, double y0_delta)
{
	ofstream stable_plot("stable_graph.txt"); //Output file
	for(int i = 10; i < 5000; i++) 
	{
		double h = 1/double(i); //Step
		double* f1 = Euler_1(gamma, y0_delta, h, i); //Studies the scheme 1 an offset delta on y0
		double* f2 = Euler_2(gamma, y0_delta, h, i); //Studies the scheme 2
		
		double K1 = (f1[i] - y0)/(f1[0] - y0); //Value of K stored in a tab, found with the equations given in the problem sheet
		double K2 = (f2[i] - y0)/(f2[0] - y0);

		stable_plot << i << " " << K1 << " " << K2 << endl;
	}
}

int main()
{
	double a = 1; //Fixing starting variables
	double b = 2;
	double gamma = 3;
	double N = 150;
	double t0 = a;
	double y0 = 1;
	double h = (b-a)/double(N);

	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "gamma : " << gamma << endl;

	ofstream plot("graph.txt");
	ofstream error("error_graph.txt");
	
	double* f1 = Euler_1(gamma, y0, h, N); //Scheme results stores in a tab for easier further use
	double* f2 = Euler_2(gamma, y0, h, N);
	
	for(int i = 0; i < N+1; i++)
	{
		double f = f_ana(a + h*i, gamma, t0, y0); //Plots analytical solution, advanced and delayed scheme
		plot << a + h*i << " " << f1[i] << " " << f2[i] << " " << f << endl;
	}

	for(int i = 1; i < 8 ; i++)
	{
		h = 1/pow(10,i);
		f1 = Euler_1(gamma, y0, h, int(1/h));
	    f2 = Euler_2(gamma, y0, h, int(1/h));
	    double f = f_ana(b, gamma, t0, y0);

		error << h << " " << abs(f1[int(1/h)] - f) << " " << abs(f2[int(1/h)] - f) << " " << h << endl;
	}
	double delta = 1E-2; //Delta offset for y0
	stable(gamma, y0, y0+delta); //Studies the stability of the scheme
	system("gnuplot -persist plot.plt");
	//K goes to -95*10^smthg for each scheme (good) one from above, the other from under (log shape)	
}