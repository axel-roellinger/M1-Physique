#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

//Global values, making it easier to implement it in functions

double a = 0;
double b = 1;
//double h = 0.0001; //Quantization step
//int N = int(1/h); 
//double eps = 1E-4; //Selection criterion for the subinterval

double fx(double x)
{
	return pow(sin(3*M_PI*x/2.),2);
}

double gx(double x)
{
	return x - fx(x);
}

double* get_four_points(double* tab, int i, double h)
{
	//double x1, x2, x3, x4;
	//double y1, y2, y3, y4;
	
	double* Points = new double[4]; //List with the 4 x-axis values around the extremum

	if(tab[i] < tab[i+1] && tab[i] < tab[i+2] && tab[i+1] > tab[i+3] && tab[i+2] > tab[i+3]) //Selection criterion
	{
		cout << "A maximum has been found" << endl;
			
		Points[0] = a + i*h;
		Points[1] = a + (i+1)*h;
		Points[2] = a + (i+2)*h;
		Points[3] = a + (i+3)*h;
		
		goto end; //Label used as a replacement to a "break" condition which doesn't work here
	}

	if(tab[i] > tab[i+1] && tab[i] > tab[i+2] && tab[i+1] < tab[i+3] && tab[i+2] < tab[i+3]) //Selection criterion
	{
		cout << "A minimum has been found" << endl;
			
		Points[0] = a + i*h;
		Points[1] = a + (i+1)*h;
		Points[2] = a + (i+2)*h;
		Points[3] = a + (i+3)*h;

		goto end;
	}
	end:
	return Points; 
}

double* find_subinterval(double* firstPts)
{
	double w = (3 - sqrt(5))/2; //Numbers given in the sheet
	double z = 1 - 2*w;

	double* newPts = new double[4]; //List that will contain the new x-axis values around the extremum
	
	//New points
	if(firstPts[0] + 10E-6 <= firstPts[1] && firstPts[3] - 10E-6 >= firstPts[2]) //10E-6 : reduction factor, arbitrarily determined to get a good precision
	{
		double x1 = firstPts[0] + 10E-6; //Increases x1 towards the extremum
		newPts[0] = x1;

		double x4 = firstPts[3] - 10E-6; //Decreases x2 towards the extremum
		newPts[3] = x4;

		double x2 = w*(x4 - x1) + x1; //Recalculating x3 and x4
		newPts[1] = x2;

		double x3 = z*(x4 - x1) + x2;
		newPts[2] = x3;
	}

	return newPts;
}

double* find_min_max(double* newPts, double eps)
{
	if(abs(newPts[3] - newPts[0]) > eps) //Precision criterion
	{
		double* newPts2 = find_subinterval(newPts);

		find_min_max(newPts2, eps); //Rerun the function with the same values to validate the epsilon's condition
	}
	else
	{
		return newPts; //Return the list as is
	}
}



int main()
{
	double h = 0.0001; //Quantization step
	int N = int(1/h); 
	double eps = 1E-4; //Selection criterion for the subinterval
	
	ofstream plot("plot.txt");	     	//Files used for final plot
	ofstream extremaF("extremaF.txt");
	ofstream extremaG("extremaG.txt");

	double* tabF = new double[N+1]; //Tab for plotting and interval screening, go to N+1 to fully cover the interval from 0 to 1, and not from 0 to 1-h
	double* tabG = new double[N+1];

	for(int i = 0; i < N+1; i++)
	{
		tabF[i] = fx(a + i*h); //Filling tabs for final plot
		tabG[i] = gx(a + i*h);
		plot << a+i*h << " " << tabF[i] << " " << tabG[i] << endl;
	}

	cout << "Extrema for f(x) : \n" << endl; //Start searching for extrema
	
	for(int i = 0; i < N - 2; i++) //Stops at N-2 due to the way the algorithm is made, as it goes from x[i] to x[i+3] to find the extrema
	{
	start_f:
	cout << "i = " << i << endl;
		double* Points_f = get_four_points(tabF, i, h); //Returns four points around an extremum, and specifies its nature
		
		if(Points_f[0] != Points_f[1]) //Bug-avoiding criterion at x = 0
		{
			double* newPoints_f = find_subinterval(Points_f); //Returns sub-interval
		
			double* finalPoints_f = find_min_max(newPoints_f, eps); //Returns the final four points which satisfy epsilon's criterion

			cout << "finalPoints_f[0] : " << finalPoints_f[0] << " ordonnée : " << fx(finalPoints_f[0]) << endl;
			cout << "finalPoints_f[1] : " << finalPoints_f[1] << " ordonnée : " << fx(finalPoints_f[1]) << endl;
			cout << "finalPoints_f[2] : " << finalPoints_f[2] << " ordonnée : " << fx(finalPoints_f[2]) << endl;
			cout << "finalPoints_f[3] : " << finalPoints_f[3] << " ordonnée : " << fx(finalPoints_f[3]) << endl;
			cout << endl;

			if(fx(finalPoints_f[0]) > fx(finalPoints_f[1])) //If we have a minimum
			{
				if(fx(finalPoints_f[1]) < fx(finalPoints_f[2])) //If f(x2) < f(x3) => minimum is at x2, else at x3
				{
					cout << "Minimum for f at ("<< finalPoints_f[1] << "," << fx(finalPoints_f[1]) <<")" << endl;
					cout << endl; //Used for clarity in the terminal
					extremaF << finalPoints_f[1] << endl; //Added to a file to plot vertical lines		
				}
				else
				{
					cout << "Minimum for f at ("<< finalPoints_f[2] << "," << fx(finalPoints_f[2]) <<")" << endl;
					cout << endl;
					extremaF << finalPoints_f[2] << endl;
					
				}
				i++;
				goto start_f; //Labels inserted to avoid counting a maximum and minimum in the same interval
			}

			if(finalPoints_f[0] < finalPoints_f[1]) 
			{
				if(fx(finalPoints_f[1]) > fx(finalPoints_f[2])) //If f(x2) > f(x3) => maximum is at x2, else at x3
				{
					cout << "Maximum for f at ("<< finalPoints_f[1] << "," << fx(finalPoints_f[1]) <<")" << endl;
					cout << endl;
					extremaF << finalPoints_f[1] << endl;		
				}
				else
				{
					cout << "Maximum for f at ("<< finalPoints_f[2] << "," << fx(finalPoints_f[2]) <<")" << endl;
					cout << endl;
					extremaF << finalPoints_f[2] << endl;
										
				}
				i++;
				goto start_f;
			}
		}
	}

	cout << endl; //Clarity in the terminal

	cout << "Extrema for g(x) : \n" << endl; //Behaves the same way as the loop above, only for g(x)

	for(int i = 0; i < N - 2; i++)
	{
	start_g:
		double* Points_g = get_four_points(tabG, i, h);
		
		if(Points_g[0] != Points_g[1])
		{
			double* newPoints_g = find_subinterval(Points_g);
		
			double* finalPoints_g = find_min_max(newPoints_g, eps);

			cout << "finalPoints_g[0] : " << finalPoints_g[0] << " ordonnée : " << gx(finalPoints_g[0]) << endl;
			cout << "finalPoints_g[1] : " << finalPoints_g[1] << " ordonnée : " << gx(finalPoints_g[1]) << endl;
			cout << "finalPoints_g[2] : " << finalPoints_g[2] << " ordonnée : " << gx(finalPoints_g[2]) << endl;
			cout << "finalPoints_g[3] : " << finalPoints_g[3] << " ordonnée : " << gx(finalPoints_g[3]) << endl;
			cout << endl;

			if(gx(finalPoints_g[0]) > gx(finalPoints_g[1]))
			{
				if(gx(finalPoints_g[1]) < gx(finalPoints_g[2]))
				{
					cout << "Minimum for g at ("<< finalPoints_g[1] << "," << gx(finalPoints_g[1]) <<")" << endl;
					cout << endl;
					extremaG << finalPoints_g[1] << endl;
				}
				else
				{
					cout << "Minimum for g at ("<< finalPoints_g[2] << "," << gx(finalPoints_g[2]) <<")" << endl;
					cout << endl;
					extremaG << finalPoints_g[2] << endl;
				}
				i++;
				goto start_g;
			}

			if(gx(finalPoints_g[0]) < gx(finalPoints_g[1])) 
			{
				if(gx(finalPoints_g[1]) > gx(finalPoints_g[2]))
				{
					cout << "Maximum for g at ("<< finalPoints_g[1] << "," << gx(finalPoints_g[1]) <<")" << endl;
					cout << endl;
					extremaG << finalPoints_g[1] << endl;
				}
				else
				{
					cout << "Maximum for g at ("<< finalPoints_g[2] << "," << gx(finalPoints_g[2]) <<")" << endl;
					cout << endl;
					extremaG << finalPoints_g[2] << endl;
				}
				i++;
				goto start_g;
			}
		}
	}

	system("gnuplot -persist plot.plt");
}
