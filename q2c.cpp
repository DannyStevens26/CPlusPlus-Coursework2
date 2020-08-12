// Include the necessary packages and function prototype
#include <iostream>
#include <cmath>
#include <time.h>

void q2c();
double **diff_cheb(int n);
double *multiply(int n, int m, double *vec, double **matrix);
double *multiply(int n, int m, double **matrix, double *vec);
double **allocate_matrix(int no_rows, int no_cols);
void deallocate_matrix(int no_rows, double **matrix);
double compute_f(double x);
double compute_df(double x);
double *vmax(double *x,int n);

void q2c()
{
    // Define and initialize the required dynamic arrays and variables
    int n = 10;
    double **d_c, *x, *u, *estans, *ans, *vmx;
    d_c = allocate_matrix(n+1,n+1);
    x = new double[n+1];
    u = new double[n+1];
    ans = new double[n+1];
    estans = new double[n+1];
    vmx = new double[n+1];

    std::cout << "Question 2c)\n\nThe exact derivative is: ( ";

    // Calculate the n+1 Chebyshev points and compute the function value evaluated at those points
    // Also compute and output the exact derivative evaluated at those points
    for (int i=0;i<=n;i++)
    {
        x[i] = cos(M_PI*double(i)/double(n));
        u[i] = compute_f(x[i]);

        ans[i] = compute_df(x[i]);
        std::cout << ans[i] << " ";
    }
    // Use diff_cheb to output the matrix of size n+1

    d_c = diff_cheb(n);

    // Define t1 and t2 as clock variables
    clock_t t1, t2;
    // Take the clock time at the start (t1) and at the end (t2)
    t1 = clock();
    // Use the multiply function to multiply the differential Chebyshev matrix and the function values
    estans = multiply(n+1,n+1,d_c,u);
    t2 = clock();

    // Calculate the the time taken
    long double approx_t = (double(t2-t1))/CLOCKS_PER_SEC;

    std::cout << ")\n\nThe Chebyshev differentiation matrix gives: ( ";
    // A for loop to output the approximate answer and calculate the difference between the approximate and exact derivative
    for (int i=0;i<=n;i++)
    {
        std::cout << estans[i] << " ";
        vmx[i] = fabs(ans[i]-estans[i]);
    }
     std::cout << ")\n\nThe CPU time used is: " << approx_t << "ms\n\n";
    // Output the error as the max of the differences between the exact and approximate derivative
    std::cout << "The error is: " << vmax(vmx,n)[0] << ", it occurs at x = " << x[int(vmax(vmx,n)[1])] << "\n\n";

    // Deallocate the memory for the dynamic arrays
    delete[] x;
    delete[] u;
    delete[] ans;
    delete[] estans;
    delete[] vmx;
    delete[] d_c;
    deallocate_matrix(n+1,d_c);

    // Set the amount of n values to be tested
    // Initialise the dynamic array to hold the error values
    int m = 5;
    double *err, alpha;
    err = new double[m];

    std::cout << "The alpha values are: ( ";

    for (int j=0;j<m;j++)
    {
        // Calculate the required n value
        n = pow(2,2+j);
        // Lines 84-114 are the same as above
        d_c = allocate_matrix(n+1,n+1);
        x = new double[n+1];
        u = new double[n+1];
        ans = new double[n+1];
        estans = new double[n+1];
        vmx = new double[n+1];

        for (int i=0;i<=n;i++)
        {
            x[i] = cos(M_PI*double(i)/double(n));
            u[i] = compute_f(x[i]);
            ans[i] = compute_df(x[i]);
        }

        d_c = diff_cheb(n);

        estans = multiply(n+1,n+1,d_c,u);

        for (int i=0;i<=n;i++)
        {
            vmx[i] = fabs(ans[i]-estans[i]);
        }

        err[j] = vmax(vmx,n)[0];

        delete[] x;
        delete[] u;
        delete[] ans;
        delete[] estans;
        delete[] vmx;
        deallocate_matrix(n+1,d_c);

        // Calculate and output the alpha value
        if (j>0)
        {
            alpha = log2(err[j-1])-log2(err[j]);
            std::cout << alpha << " ";
        }
    }

    std::cout << ")\n\n\n";
    delete[] err;
}
