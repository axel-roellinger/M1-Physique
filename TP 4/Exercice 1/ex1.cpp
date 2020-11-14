#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

double diff_1(double x, double h, double (*func)(double)) //Equation 1, phi(h)
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

double derivF(double x)
{
	return 1 - 3*M_PI*cos(3*M_PI*x/2.)*sin(3*M_PI*x/2.);
}

double derivG(double x)
{
	return 1 + pow(tan(x),2);
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

void error_varyX(double (*deriv)(double, double, double(*func)(double), int), double (*derivF)(double), double (*derivG)(double), double** F1, double** F3, double** G1, double** G3)
{

	for(int j = 1; j < 12; j++)
	{
		F1[0][j] = M_PI*double(j-1)/10.;
		F3[0][j] = M_PI*double(j-1)/10.;
		G1[0][j] = M_PI*double(j-1)/10.;
		G3[0][j] = M_PI*double(j-1)/10.;
	}

	for(int i = 1; i < 7; i++)
	{
		double h = 1/pow(10,i);

		F1[i][0] = h;
		F3[i][0] = h;
		G1[i][0] = h;
		G3[i][0] = h;

		for (int j = 1; j < 13; j++)
		{
			double x = M_PI*double(j-1)/10;	

			F1[i][j] = abs(deriv(x, h, fx, 1) - derivF(x));
			F3[i][j] = abs(deriv(x, h, fx, 3) - derivF(x));
			G1[i][j] = abs(deriv(x, h, gx, 1) - derivG(x));
			G3[i][j] = abs(deriv(x, h, gx, 3) - derivG(x));
			
			if(j == 12)
			{
				F1[i][j] = pow(h,2);
				F3[i][j] = pow(h,4);
				G1[i][j] = pow(h,2);
				G3[i][j] = pow(h,4);
			}
		}
	}
}

void fill_files(double** F1, double** F3, double** G1, double** G3)
{
	ofstream errorF1("errorF1.txt");
	ofstream errorF3("errorF3.txt");
	ofstream errorG1("errorG1.txt");
	ofstream errorG3("errorG3.txt");

	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < 13; j++)
		{
			errorF1 << F1[i][j] << " ";

			if(j == 12)
			{
				errorF1 << endl;
			}
		}
	}

	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < 13; j++)
		{
			errorF3 << F3[i][j] << " ";
			
			if(j == 12)
			{
				errorF3 << endl;
			}
		}
	}

	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < 13; j++)
		{
			errorG1 << G1[i][j] << " ";

			if(j == 12)
			{
				errorG1 << endl;
			}
		}
	}

	for(int i = 0; i < 7; i++)
	{ 
		for(int j = 0; j < 13; j++)
		{
			errorG3 << G3[i][j] << " ";

			if(j == 12)
			{
				errorG3 << endl;
			}
		}
	}
}

int main()
{
	int N = 6;
	double x = M_PI/3.;
	
	ofstream plotError("plotError.txt");

	for (int i = 0; i < N; i++) //Curve for a given x
	{
		double h = 1/pow(10, double(i));

		double errF1 = abs(deriv(M_PI/3., h, fx, 1) - derivF(x));
		double errF3 = abs(deriv(M_PI/3., h, fx, 3) - derivF(x));
		double errG1 = abs(deriv(M_PI/3., h, gx, 1) - derivG(x));
		double errG3 = abs(deriv(M_PI/3., h, gx, 3) - derivG(x));

		plotError << h << " " << errF1 << " " << errF3 << " " << errG1 << " " << errG3 << " " << pow(h,2) << " " << pow(h,4) << endl;
	}

	double** F1 = new double*[7]; //7 rows for 6 values of h plus first line for the graph's key
	double** F3 = new double*[7];
	double** G1 = new double*[7];
	double** G3 = new double*[7];

	for(int i = 0; i < 7; i++)
	{
		F1[i] = new double[14]; //11 columns to cover x from 0 to pi
		F3[i] = new double[14];
		G1[i] = new double[14];
		G3[i] = new double[14];
	}

	error_varyX(deriv, derivF, derivG, F1, F3, G1, G3); //Curves for 11 values across the whole interval

	fill_files(F1, F3, G1, G3);

	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < 14; j++)
		{
			cout << F1[i][j] << " " << i << " " << j << " ";
			if(j == 13)
			{
				cout << endl;
			}
		}
	}

	system("gnuplot -persist plot.plt");
}