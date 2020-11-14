#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

//Interval of study : [0;1]

double fx(double x)
{
	return pow(sin(3*M_PI*x/2.), 2);
}

double gx(double x)
{
	return x - fx(x);
}

double derivF(double x)
{
	return 3*M_PI*sin(3*M_PI*x/2.)*cos(3*M_PI*x/2.);
}

double derivG(double x)
{
	return 1 - derivF(x);
}

double* find_zero_interval(double (*func)(double), int N, int i) //N : discrete criteria, interval [0,1]
{
	double* points = new double[2];
	double h = 1/double(N);

	//cout << "i*h vaut : " << i*h << endl;

	//double produit = fx(double(i)*h)*fx((double(i)+1)*h);

	//cout << "Diff : " << fx(double(i)*h)*fx(double((i+1)*h)) << endl;
	
	points[0] = double(i)*h;
	points[1] = (double(i)+1)*h;
	cout << "Zero trouvé !" << endl;
	return points;
	delete[] points;
	
}

double Newton_Raphson(double* valInit, double (*func)(double), double (*funcDeriv)(double), int N)
{
	double* estimX = new double[N+1];
	
	estimX[0] = valInit[0];
	estimX[1] = valInit[1];

	for(int i = 0; i < N; i++)
	{
		estimX[i+1] = estimX[i] - (func(estimX[i])/funcDeriv(estimX[i]));
	}

	//cout << "estimX = " << estimX[N] << endl;

	return estimX[N];
}

int main()
{
	int N = 100;
	double h = 1/double(N);

	ofstream plotF("plotF.txt");
	ofstream plotG("plotG.txt");

	ofstream zerosF("zerosF.txt");
	ofstream zerosG("zerosG.txt");
	
	for(int i = 0; i < N+5; i++)
	{
		if(fx(double(i)*h)*fx(double(i+1)*h) < pow(10,-6.5))
		{
			cout << "i vaut : " << i << endl;
			double* tabInitF = find_zero_interval(fx, N, i);
			double estimXF = Newton_Raphson(tabInitF, fx, derivF, N);

			if(!isnan(estimXF))
			{
				cout << "Estimation finale zero de f : " << estimXF << endl;
				zerosF << estimXF << endl;
			}
			else
			{
				cout << "Zero found is nan, unusable" << endl;
			}
		}

		if (gx(double(i)*h)*gx(double(i+1)*h) < 10E-9)
		{
			cout << "i vaut : " << i << endl;
			double* tabInitG = find_zero_interval(gx, N, i);
			double estimXG = Newton_Raphson(tabInitG, gx, derivG, N);

			if(!isnan(estimXG))
			{
				cout << "Estimation finale zero de g : " << estimXG << endl;
				zerosG << estimXG << endl;
			}
			else
			{
				cout << "Zero found is nan, unusable" << endl;
			}
		}
	}



	for(int i = 0; i < N+1; i++)
	{
		plotF << i*h << " " << fx(i*h) << endl;
		plotG << i*h << " " << gx(i*h) << endl;
	}
	system("gnuplot -persist plot.plt");
}