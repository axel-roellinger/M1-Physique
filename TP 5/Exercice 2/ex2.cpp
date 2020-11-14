#include <iostream>
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

double* ABM(double* y_tilde, double* y, double h, double gamma, int N)
{
	for(int i = 2; i < N; i++)
	{
		y_tilde[i+1] = (h/12.)*(23*fty(gamma, y[i]) - 16*fty(gamma, y[i-1]) + 5*fty(gamma, y[i-2])) + y[i];
		y[i+1] = (h/12.)*(5*fty(gamma, y_tilde[i+1]) + 8*fty(gamma, y[i]) - fty(gamma, y[i-1])) + y[i];
	}
	return y;
}

int main()
{
	double a = 1;
	double b = 2;
	double gamma = 3;
	//Second scheme
	
	double* buffer = new double[2];
	double y0 = 1; //Starting coordinate on y axis
	double t0 = a; //Starting point
	double h = 0.01; //Split the itnerval [1,2] in 100 values
	 //Initialize the first values

	double eps = 10E-8;

	//ofstream plot2("second_scheme.txt");
	ofstream error2("error_second_scheme.txt");
	
	//ofstream error2("error_second_scheme.txt");
	ofstream errorABM("error_ABM.txt"); //We will track the error for one value, at x = 1.9
	
	for(int i = 1; i < 10; i++) //Counter for h values
	{
		ofstream plot2("second_scheme.txt");
		ofstream plotABM("ABM_scheme.txt");

		double h = 1/pow(2,double(i));
		int N = int(1/h);

		buffer = Euler_1(gamma, y0, h, 2);
		double* tab2 = new double[N];
	
		double* y = new double[N];
		
		for(int i = 0; i < 2; i++)
		{
			tab2[i] = buffer[i];
		}

		for(int i = 2; i < N; i++)
		{
			tab2[i] = 2*h*fty(gamma, tab2[i-1]) + tab2[i-2]; 
		}

		for(int i = 0; i < N; i++)
		{
			plot2 << a + i*h << " " << tab2[i] << " " << f_ana(a + i*h, gamma, t0, y0) << endl;
		}

		error2 << h << " " << abs(f_ana(a + 0.5, gamma, t0, y0) - tab2[int(N/2)]) << " " << pow(h,2) << endl;
	
		y[0] = tab2[0];
		y[1] = tab2[1];
		y[2] = 2*h*fty(gamma, y[1]) + y[0];

		double* y_tilde = new double[N];

		double* tabABM = ABM(y_tilde, y, h, gamma, N);

		for(int i = 0; i < N; i++)
		{
			plotABM << a + i*h << " " << tabABM[i] << endl;
		}

		errorABM << h << " " << abs(f_ana(a + 0.5, gamma, t0, y0) - tabABM[int(N/2.)]) << " " << pow(h,3) << endl;

	}

	system("gnuplot -persist plot.plt");
}