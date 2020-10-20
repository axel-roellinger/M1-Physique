#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;
//Common functions //////////////////////////////////////////////////////////////////////////////////////////

double a = 0; //Integral's limits
double b = 2*M_PI;

double intAnaG = -1.608564332773849812;//No intent to compute a Bessel function


double fx(double x) //Returns f(x)
{
    return 0.25 + x - (0.75*pow(x,2)) + ((3/32.)*pow(x,3));
}

double gx(double x) //Returns g(x)
{
    return sin(1 + M_PI*cos(x));
}

double Ifx() //Returns the integral of f(x)
{
    double Ifa = a/4 + pow(a,2)/2. - (0.75/3.)*pow(a,3) + (3/(4.*32.))*pow(a,4);
    double Ifb = b/4 + pow(b,2)/2. - (0.75/3.)*pow(b,3) + (3/(4.*32.))*pow(b,4);
} 
//Start of trapezoidal rule exercise/////////////////////////////////////////////////////////////////////////

double trapez_solver( double (*fx)(double), double a, double b, int N) //Computes the integral
{
    double sum = 0;
    double h = (b-a)/double(N);
    
    for(int i = 0; i < N; i++)
    {
        sum += ((fx(a + (double(i)+1)*h) + fx(a + h*double(i)))*0.5);
    }
    return sum*h;
}

void Trapezoidal_rule()
{
    ofstream file1("trapeze_1.txt"); //Used to plot the function
    int N = 100; //Number of values to plot f(x) and g(x)
    double x;
    int N1; 
    cout << "Max power of N for integral's subdivisions : ";
    cin >> N1;
    
    
    ofstream file2("errTra.txt");

    for(int i = 1; i < N; i++)
    {
        double x = (2*M_PI/N)*double(i);
        file1 << x << " " << fx(x) << " " << gx(x) << endl;
    }
    
    cout << "Analytical solution of f(x) : " << Ifx() << endl;
    cout << "Analytical solution of g(x) : " << intAnaG << endl;
    
    for(int j = 1; j < N1; j++)
    {
        N = pow(10,j);
        cout << "Value of N : " << N << " " << endl;

        double h = (b-a)/double(N);
        cout << "Integral of f(x) : " << setprecision(15) << trapez_solver(fx, a, b, N) << endl;
        cout << "Integral of g(x) : " << setprecision(15) << trapez_solver(gx, a, b, N) << endl;

        double error_f = abs(Ifx() - trapez_solver(fx, a, b, N));
        double error_g = abs(intAnaG - trapez_solver(gx, a, b, N));
        cout << "Error on f(x) : " << error_f << endl;
        cout << "Error on g(x) : " << error_g << endl;
        file2  << h << " " << error_f << " " << error_g << " " << pow(h,2) << endl;
    }
   
    system("gnuplot -persist multiplot_trapezoid.plt");
}

//End of trapezoidal rule exercise///////////////////////////////////////////////////////////////////////////
//Start of Simpson rule exercise/////////////////////////////////////////////////////////////////////////////

double Simpson_solver(double (*func)(double), double a, double b, int N)
{
    double h = (b-a)/double(N);
    double sum_even = 0; //Sum for values of the function where i is even
    double sum_odd = 0;

    for(int i = 1; i < N; i++) //Starts at func(a + h) and stops at func(b - h)
    {
        if(i%2 == 0) //Selection criterion
        {
            sum_even += func(a + double(i)*h);
        }
        else
        {
            sum_odd += func(a + double(i)*h);
        }
    }
    return (h/3.)*(func(a) + 4*sum_odd + 2*sum_even + func(b));
}

void Simpson_rule()
{
    ofstream fx_gx_graph("fx_gx_sim.txt");
    ofstream errSim("errSim.txt");
    
    int N = 1000; //Number of points for the curve plotting
    int N1;
    cout << "Max power for the number of steps ? : ";
    cin >> N1;

    double intAnaG = -1.608564332773849812; //No intent to compute a Bessel function

    for(int i = 0; i < N+1; i++) //Used to plot f(x) and g(x)
    {
        double x = (2*M_PI*i)/double(N);
        fx_gx_graph << x << " " << fx(x) << " " << gx(x) << endl;
    }

    //double h = 0;

    for(int i = 1; i < N1; i++) //Computes N1-1 times the integral, starts at one to avoid zero division
    {
        cout << "Number of steps : " << pow(10,i) << endl;

        double h = (b-a)/(pow(10,i)); 
        
        double fVal = Simpson_solver(fx, a, b, pow(10,i));
        double gVal = Simpson_solver(gx, a, b, pow(10,i));

        cout << "fVal : " << setprecision(15) << fVal << ", error : " << setprecision(15) << abs(fVal - Ifx()) << endl;
        cout << "gVal : " << setprecision(15) << gVal << ", error : " << setprecision(15) << abs(intAnaG - gVal) << endl;

        errSim << h << " " << abs(fVal - Ifx())  << " " << abs(gVal - intAnaG) <<  " " << pow(h,2) << endl; //Collects the error
    }

    system("gnuplot -persist multiplot_simpson.plt"); //Plots the error and the integral's evolution
}

int main()
{
    start:
    int exercise;
    cout << endl;
    cout << "List of options : " << endl;
    cout << "Trapezoidal rule : hit 1" << endl;
    cout << "Simpson rule : hit 2" << endl;
    cout << "Exit : hit 3" << endl;
    cout << "Your choice : ";
    cout << endl;
    cin >> exercise;

    switch(exercise)
    {
        case 1:
            Trapezoidal_rule();
            goto start;
        case 2:
            Simpson_rule();
            goto start;
        case 3:
            return 0;
        default:
            cout << "Error : no valid input";
            goto start;
    }
}