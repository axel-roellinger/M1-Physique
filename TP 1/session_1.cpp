#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

double a = 0;
double b = 25; //Global variables, used for integration

void vases(double** aVal, double** bVal, double** cVal, double** sumVal, int N, double alpha, int i, double a, double b, double c)
{
    aVal[0][i-1] = alpha;
    bVal[0][i-1] = alpha;
    cVal[0][i-1] = alpha;
    sumVal[0][i-1] = alpha;

    aVal[1][i-1] = a;
    bVal[1][i-1] = b;
    cVal[1][i-1] = c;
    sumVal[1][i-1] = a + b + c;

    for(int j = 2; j < N+1; j++)
    {        
        b += alpha*a;
        a -= alpha*a;

        c += alpha*b;
        b -= alpha*b;

        a += alpha*c;
        c -= alpha*c;

        aVal[j][i-1] = a;
        bVal[j][i-1]= b;
        cVal[j][i-1]= c;
        sumVal[j][i-1] = a + b + c;
    }
}

void filein(double** aVal, double** bVal, double** cVal, double** sumVal, int N, int iter)
{
    ofstream a_val("a_val.txt");
    ofstream b_val("b_val.txt");
    ofstream c_val("c_val.txt");
    ofstream sum_val("sum_val.txt");

    for(int i = 0; i < N+1; i++)
    {
        a_val << i << " ";
        b_val << i << " ";
        c_val << i << " ";
        sum_val << i << " ";

        for(int j = 0; j < iter; j++)
        {
            a_val << aVal[i][j] << " ";
            b_val << bVal[i][j] << " ";
            c_val << cVal[i][j] << " ";
            sum_val << sumVal [i][j] << " ";

            if(j == iter-1)
            {
                a_val << endl;
                b_val << endl;
                c_val << endl;
                sum_val << endl;
            }
        }
    }
}
void Vases()
{  
    double a, b, c;   
    double alpha;
    int N, iter;
    a = 5;
    b = 10;
    c = 15;
    alpha = 0.5;
    N = 100;
    iter = 10;
   
    double** aVal = new double*[N+1]; 
    double** bVal = new double*[N+1];
    double** cVal = new double*[N+1];
    double** sumVal = new double*[N+1];

    for(int i = 0; i < N+1; i++)
    {
        aVal[i] = new double[iter];
        bVal[i] = new double[iter];
        cVal[i] = new double[iter];
        sumVal[i] = new double[iter];
    }
    
    double* alphaVal = new double[iter];

    for(int i = 1; i < iter+1; i++) //Start the loop at 1, because the case alpha = 0 won't make any values change
    {
        cout << "alpha : " << alpha*(double(i)/double(iter)) << endl;

        vases(aVal, bVal, cVal, sumVal, N, alpha*(double(i)/double(iter)), i, a, b, c);
        
        alphaVal[i-1] = alpha*(double(i)/20);
    }
    
    filein(aVal, bVal, cVal, sumVal, N, iter);

    system("gnuplot -persist multiplot_vases.plt");
}
//End of communicating vases exercise /////////////////////////////////////////////////////////////
//Start of Riemann exercise ///////////////////////////////////////////////////////////////////////


//fx and Ifx function are used for both Riemann and Richardson exercises


double fx(double x)
{
    if(x < a || x > b) //Validity criteria
    {
        cout << "Error ! x is not in the interval [a,b]" << 2*x << endl;
    }
    return exp(x);
}

double Ifx()
{
    return exp(b) - exp(a);
}

double solve_Riemann(int j, int N, ofstream& errEvo)
{
    double N1 = pow(N,j); //Number of subdivisions, goes up with j for the evolution of h
    double* x = new double[int(N1)]; //Tabs, must be declared dynamically or will cause a segmentation fault for a number of values bigger than 10^6
    double* y = new double[int(N1)];
    double h = (b - a)/N1; //Step
    double sum = 0;
    cout << "Value of N : " << N1 << endl;

    for(int i = 1; i < int(N1); i++) //Computes the sum
    {
        x[i] = a + double(i)*h;
        y[i] = fx(a + double(i)*h); //Uses the function described above
        sum += y[i];
    }

    errEvo << h << " " << abs(sum*h - Ifx()) <<  " " << h << endl;
    cout << "h : " << h << ", integral : " << setprecision(15) << sum*h << ", error : " << abs(sum*h - Ifx()) << endl;
}

void Riemann()
{
    cout << "Start of Riemann exercise" << endl;

    ofstream errEvo("errRiemann.txt"); //Filled with residual error and value of h
    int N; //Starting point of subdivisions
    cout << "How many subdivisons for the first integral ? : ";
    cin >> N;

    int REVal;
    cout << "Max power for N subdivisions ? : ";
    cin >> REVal;

    for(int j = 1; j < REVal; j++) //Loop to make h vary
    {
        solve_Riemann(j, N, errEvo);
    }
    system("gnuplot -persist plot_riemann.plt");

    errEvo.close();
}

//End of Riemann exercise ///////////////////////////////////////////////////////////////////////
//Start of Richardson exercise //////////////////////////////////////////////////////////////////

double solve_Riemann(double a, double b, int N, double (*func)(double)) //N : subdivisions
{  
    double h = (b-a)/double(N);
    double sum = 0;
    for(int i = 0; i < N+1; i++)
    {
        sum += func(a + double(i)*h);
    }
    return sum*h;
}

void fill_tab(double **tab, double a, double b, double (*func)(double), int N, int N1)//N : table size, N1 : initial subdivisions
{
    for(int i = 0; i < N+1; i++)
    {
        tab[0][i] = solve_Riemann(a, b, N1*pow(2,i), func);
    }

    for(int i = 1; i < N+1; i++)
    {
        for(int j = 0; j < N+1-i; j++)
        {
            tab[i][j] = (pow(2,double(i))*tab[i-1][j+1] - tab[i-1][j])/(pow(2,i) - 1); //Matrix element

            if((pow(2,double(i))*tab[i-1][j+1] - tab[i-1][j])/(pow(2,i) - 1) < 10E-300) //Use to avoid errors
            {
                tab[i][j] = 0;
            }
        }
    }
}     

double convergence(double **tab, int N)
{
    for(int i = 0; i < N+1; i++)
    {
        for(int j = 0; j < N+1-i; j++)
        {
            if(abs(tab[i][j] - Ifx()) < (tab[0][0])/1000)
            {
                cout << "At i = " << i << " and j = " << j << ", less than 0.1 percent of error with value : " << tab[i][j] << endl; 
                return tab[i][j];
            }            
        }
    }
}


void display(double **tab)
{   
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << setprecision(15) << tab[i][j] << " ";
         
            if(j==3)
            {
                cout << endl;
            }
        }
    }
}

double compa_Riemann(int N1)
{
    double intAna = 72004899336.4;
    for(int i = 0; i < N1; i++)
    {
        double R = solve_Riemann(a, b, pow(20,i), fx);

        if(abs(R - intAna) < 0.001*intAna)
        {
            cout << ".1 percent of precision for h = " << (b-a)/pow(20,i) << endl;
            cout << "Number of subdivisions : " << pow(20,i) << endl;
            break;
        }
        else
        {
            cout << "h = " << (b-a)/pow(20,i) << endl;
            cout << "Not low enough h to get 0.1 percent of precision" << endl;
        }
    }
}

void Richardson()
{

    cout <<"Start of Richardson exercise : " << endl;

    int N = 3; //Initial subdivision of the x-axis for Riemann integral
    
    int N1;
    cout << "Initial number of subdivisions (100 advised) : ";
    cin >> N1;
    
    int N2;
    cout << "Max step to compare to Riemann's integration : ";
    cin >> N2;

    double** tab = new double*[N+1];

    for(int i = 0; i < N+1; i++)
    {
        tab[i] = new double[N+1];
    }

    fill_tab(tab, a, b, fx, N, N1);
    display(tab);
    convergence(tab, N);

    cout << "Error of last value : " << tab[3][0] - Ifx()<< endl;

    compa_Riemann(N2);
}

int main()
{
    start:
    int exercise;
    cout << endl;
    cout << "List of options : " << endl;
    cout << "Vases : hit 1" << endl;
    cout << "Riemann : hit 2" << endl;
    cout << "Richardson : hit 3" << endl;
    cout << "Exit : hit 4" << endl;
    cout << "Your choice : ";
    cout << endl;
    cin >> exercise;

    switch(exercise)
    {
        case 1:
            Vases();
            goto start;
        case 2:
            Riemann();
            goto start;
        case 3:
            Richardson();
            goto start;
        case 4:
            return 0;
        default:
            cout << "Error : no valid input";
            goto start;
    }
}
