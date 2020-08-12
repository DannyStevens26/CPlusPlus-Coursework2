// Include the necessary packages and function prototype
#include <iostream>
#include <cmath>

double compute_f(double x);
double compute_df(double x);
double *evaluate_user_function(double (*func)(double x),double *x, int n);


double compute_f(double x)
{
    // Return the computed function value
    return exp(sin(M_PI*x))-1;
}

double compute_df(double x)
{
    // Return the computed function value
    return M_PI*cos(M_PI*x)*exp(sin(M_PI*x));
}

double *evaluate_user_function(double (*func)(double x),double *x, int n)
{
    // Define and initialize a dynamic array y
    double *y;
    y = new double[n];
    // For each x value given calculate the function value
    for (int i=0;i<n;i++)
    {
        y[i]=(*func)(x[i]);
    }
    // Return the dynamic array
    return y;
}
