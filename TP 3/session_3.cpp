#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <iomanip>
using namespace std;

double L = 2*M_PI;

double fx(double x)
{    
    if(x > 2 && x < 4)
    {
        return sqrt(2) - 1 + exp(2 - x);
    }
    
    else if(x >= 4)
    {
        return exp(4 - x);
    }
    
    return 0;
}

double maxfunc( double (*func)(double), int N) //find the maximum of a given function
{
    double max = 0;

    for(int i = 0; i < N+1; i++) //defined as N+1 to get f(2*pi)
    {
        double y = 2*M_PI*double(i)/double(N);

        if (func(y) > max)
        {
            max = func(y);
        }
    }
    return max;
}

double rdm(double N)
{
    random_device rd{}; //Random 32-bit seed
    mt19937 generator{rd()}; 
    uniform_real_distribution<double>dist(0.0, N); //goes to a given value N
    return dist(generator);
}

void rdm_gen(double** valRdm, double L, double fMax, int N)
{
    for(int i = 0; i < N; i++)
    {
        valRdm[i][0] = rdm(L); //random from 0 to L
        valRdm[i][1] = rdm(fMax);
    }
}

double Pts(double** valRdm, double L, double h, int N) //Studies the table
{
    double nGood;
    ofstream pts("ptsGood.txt");
    ofstream pts2("ptsBad.txt");

    for(int i = 0; i < N; i++)
    {
        if(valRdm[i][1] < fx(valRdm[i][0]))
        {
            nGood += 1;
            pts << valRdm[i][0] << " " << valRdm[i][1] << endl;
        }
        else
        {
            pts2 << valRdm[i][0] << " " << valRdm[i][1] << endl;
        }
    }
    return nGood;
}

void inte_calc(int N, double fMax) //Computes the integral
{
    cout << endl;
    
    cout << "Number of generated points: " << N << endl; 
    
    double** valRdm = new double*[N]; //Used to store the values
    
    for(int i = 0; i < N; i++)
    {
        valRdm[i] = new double[2];
    }
    
    rdm_gen(valRdm, L, fMax, N); //Generates N random points
    
    double nGood = Pts(valRdm, L, fMax, N); //Computes the number of good points and fills the files used for plotting
    
    cout << "Number of good points  : " << nGood << endl;
    
    cout << "Integral : " << ((nGood)/double(N)) * L * fMax << endl;
}
    
double Riemann(double (*fx)(double)) //Plot D(E) with a million points for a sufficient precision without overloading the hardware
{
    double h = (2*M_PI)/1000000.;
    double sum = 0;
    for(int i = 0; i < 1000000; i++)
    {
        sum+=fx(h*double(i));
    }
    return sum*h;
}

void exercise()
{
    int N0 = 1000000; //Number of points to plot the curve
   
    int N; //Number of generated points
    cout << "Number of random points : ";
    cin >> N;

    double* valY = new double[N0];
    
    ofstream fx_graph("fx.txt");
    
    cout << "Value of Riemannian integral with 1000000 subdivisions : " << setprecision(12) << Riemann(fx) << endl;
    cout << "Value of analytical integral : " << setprecision(12) << 2.59113292307 << endl;

    for(int i = 0; i < N0+1; i++) //Loop used to plot the graph
    {
        double x = 2*M_PI*double(i)/double(N0);
        fx_graph << x << " " << fx(x) << endl;
    }

    double fMax = maxfunc(fx, N0); //Gives the maximum value of D(E) with N0 values 

    cout << "Max value : " << setprecision(15) << fMax << endl;

    inte_calc(N, fMax); ///Compute the integral once to show the efficiency of the algorithm

    system("gnuplot -persist plot_session3.plt");
}

int main()
{
start:
    int choice;
    cout << endl;
    cout << "List of options : " << endl;
    cout << "von Neumann/Ulam methode : hit 1" << endl;
    cout << "Exit : hit 2" << endl;
    cout << "Your choice : ";
    cout << endl;
    cin >> choice;

    switch(choice)
    {
        case 1:
            exercise();
            goto start;
        case 2:
            return 0;
        default:
            cout << "Error : no valid input";
            goto start;
    }
}