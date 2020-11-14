#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

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

double derivF(double x) //Analytical solutions for value comparison
{
	return 1 - 3*M_PI*sin(3*M_PI*x/2.)*cos(3*M_PI*x/2.);
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
//Fills tab with Richardson's formula
void fill_tabs(double** tabF, double** tabG, int N, double h0, double (*fx)(double), double (*gx)(double), double (*diff_1)(double, double, double(*fx)(double)), double x)
{
	for(int i = 0; i < N+1; i++)
	{
		tabF[0][i] = diff_1(x, (h0/pow(2, double(i))), fx);
		tabG[0][i] = diff_1(x, (h0/pow(2, double(i))), gx);
	}

	for(int i = 1; i < N+1; i++)
	{
		for(int j = 0; j < N - i +1; j++)
		{
			tabF[i][j] = (pow(2,double(i))*tabF[i-1][j+1] - tabF[i-1][j])/(pow(2,i) - 1);
			tabG[i][j] = (pow(2,double(i))*tabG[i-1][j+1] - tabG[i-1][j])/(pow(2,i) - 1);
		}
	}
}

//Displays the aforementioned tab
void display_tab(double** tab, int N)
{
	for(int i = 0; i < N+1; i++)
	{
		for(int j = 0; j < N+1; j++)
		{
			cout << setprecision(14) << tab[i][j] << " "; //Important precision to probe the efficiency of the algorithm
			if(j == N)
			{
				cout << endl;
			}
		}
	}
}


void error_percent(double** tab, double (*deriv)(double), double x, int N) //Displays the rank at which there is less than .1 percent of error with the analytical value
{
	for(int i = 0; i < N+1; i++)
	{
		for(int j = 0; j < N+1; j++)
		{
			if(tab[i][j] - deriv(x) < 0.001*deriv(x))
			{
				cout << "Less than .1 percent of error at i = " << i << " and j = " << j << endl;
				i = N;
				j = N;	
			}
		}
	}
}

//Finds the h for which the same precision as above is reached

double h_precision(double (*func)(double), double(*diff_1)(double, double, double(*func)(double)), double(*derivFunc)(double), double x)
{
	for(int i = 1; i < 10E8; i++)
	{
		double h = 1/(double(i));

		if(abs(diff_1(x, h, func) - derivFunc(x)) < .001*abs(derivFunc(x)))
		{
			cout << "Less than .1 percent of error for f(x) at h = " << h << endl; 
			cout << "Numerical value : " << diff_1(x, h, func) << endl;
			cout << "Analytical value : " << derivFunc(x) << endl;
			return diff_1(x, h, func);
		}
	}	
}

int main()
{
	int N = 3;
	double x = M_PI/4.;
	double h0 = 0.1;

	double** tabF = new double*[N+1];
	double** tabG = new double*[N+1];

	for(int i = 0; i < N+1; i++)
	{
		tabF[i] = new double[N+1];
		tabG[i] = new double[N+1];
	}

	ofstream plot("plot.txt");
	ofstream plot_final("plot_final.txt");

	for(int i = 0; i < 10001; i++)
	{
		plot << M_PI*double(i)/10000 << " " << fx(M_PI*double(i)/10000) << " " << gx(M_PI*double(i)/10000) << endl;
	}

	cout << "Analytical value for df/dx : " << derivF(x) << endl;
	cout << "Analytical value for dg/dx : " << derivG(x) << endl;
	cout << endl;

	fill_tabs(tabF, tabG, N, h0, fx, gx, diff_1, x);

	cout << "Tab for f(x) : \n" << endl;

	display_tab(tabF, N);

	cout << endl;
		
	cout << "Tab for g(x) : \n" << endl;

	display_tab(tabG, N);
	
	cout << endl;

	error_percent(tabF, derivF, x, N);
	
	cout << endl;
	
	error_percent(tabG, derivG, x, N);

	cout << endl;

	cout << "Required h for f(x) : \n" << endl;
	h_precision(fx, diff_1, derivF, x);
	cout << endl;

	cout <<"Required h for g(x) : \n" << endl;
	h_precision(gx, diff_1, derivG, x);

	double diffF, diffG;

	for(int i = 0 ; i < 1001; i++)
	{
		x = double(i)*M_PI/1001;
		cout << "x = " << x << endl;

		//if( x < (M_PI/2.) - 0.0001 || x > (M_PI/2.) + 0.0001 ) //Criterion to avoid the singularity of the tan(x) function
		if(x != M_PI/2)
		{
			//cout << "x vaut : " << x << endl;

			fill_tabs(tabF, tabG, N, h0, fx, gx, diff_1, x);

			//cout << "Tab for f(x) : \n" << endl;

			//display_tab(tabF, N);

			//cout << endl;
		
			//cout << "Tab for g(x) : \n" << endl;

			//display_tab(tabG, N);
	
			//cout << endl;
			cout << ".1 percent for f(x) : " << endl;
			error_percent(tabF, derivF, x, N);
	
			cout << endl;
			
			cout << ".1 percent for g(x) : " << endl;
			error_percent(tabG, derivG, x, N);	

			cout << endl;

			cout << "Required h for f(x) : \n" << endl;
			double final_f = h_precision(fx, diff_1, derivF, x);
			cout << endl;

			cout <<"Required h for g(x) : \n" << endl;
			double final_g =  h_precision(gx, diff_1, derivG, x);

			plot_final << x << " " << final_f << " " << final_g << endl;

			if(x < M_PI/2 - 0.2 || x > M_PI/2 + 0.2)
			{	
				diffF += abs(derivF(x) - tabF[3][0]);
				diffG += abs(derivG(x) - tabG[3][0]);
			}
		}
		else
		{
			//cout << "x vaut : " << x << endl;
			fill_tabs(tabF, tabG, N, h0, fx, gx, diff_1, x);
			//cout << "Tab for f(x) : \n" << endl;

			//display_tab(tabF, N);

			//cout << endl;
		
			//cout << "Tab for g(x) : \n" << endl;

			//display_tab(tabG, N);
	
			//cout << endl;

			error_percent(tabF, derivF, x, N);
	
			//cout << endl;
	
			//error_percent(tabG, derivG, x, N);	

			cout << endl;

			cout << "Required h for f(x) : \n" << endl;
			double final_f = h_precision(fx, diff_1, derivF, x);
			cout << endl;

			//cout <<"Required h for g(x) : \n" << endl;
			//double final_g =  h_precision(gx, diff_1, derivG, x);
			plot_final << x << " " << final_f << " " << 0 << endl; //Sets the value of tan(x) at zero to avoid disproportioned graphs
			diffF += abs(derivF(x) - tabF[3][0]);
			diffG += 0;
		}
	}

	cout <<"Mean error between analytical value and last value of tab for f(x) : " << diffF/1000.<< endl;
	cout <<"Mean error between analytical value and last value of tab for g(x) : " << diffG/1000. << endl;

	system("gnuplot -persist plot.plt");
}