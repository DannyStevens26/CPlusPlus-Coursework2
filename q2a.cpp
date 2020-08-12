// Include the necessary packages and function prototype
#include <iostream>

double *evaluate_user_function(double (*func)(double x),double *x, int n);
double compute_f(double x);
double compute_df(double x);
void q2a();

void q2a()
{
    // Define and initialize the desired dynamic arrays and integer n
    int n = 16;  //Daniel Lea Stevens
    double *x, h, *f1, *df1;
    // h is the distance between each x and the next x value as they are uniformly distributed
    h = 2/(double(n));
    x = new double[n];
    f1 = new double[n];
    df1 = new double[n];
    // Use a for loop to set the x values
    for (int i=0;i<n;i++)
    {
        x[i] = -1 + h*i;
    }
    // Use evaluate_user_function to compute the function and the derivative values at n points
    f1 = evaluate_user_function(compute_f,x,n);
    df1 = evaluate_user_function(compute_df,x,n);


    std::cout << "Question 2a)\n\nu(x) evaluated at uniform points: ( ";
    // Output the function values and the derivative values
    for (int i=0;i<n;i++)
    {
        std::cout << f1[i] << " ";
    }

    std::cout << ")\n\nu'(x) evaluated at uniform points: ( ";

    for (int i=0;i<n;i++)
    {
        std::cout << df1[i] << " ";
    }

    std::cout << ")\n\n\n";
}
