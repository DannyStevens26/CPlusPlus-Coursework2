// Include the necessary packages and function prototype
#include <iostream>
#include <time.h>
#include <cmath>

void q2b();
double *sp_diff_2(int n);
double *sp_matrix_multiply(double *matrix_entries, int *column_no, int *row_start, double *x, int n);
double compute_f(double x);
double compute_df(double x);
double *vmax(double *x,int n);

void q2b()
{
    // Define and initialize the needed dynamic arrays and variables
    int n = 10;
    // n1 is the total amount of values output by the function sp_diff_2(n)
    int n1 = 1+4*n+n+1;
    double *y, *m_e, h, *x, *estans, *ans, *u, *vmx;
    int *c_n, *r_s;
    u = new double[n];
    ans = new double[n];
    estans = new double[n];
    x = new double[n];
    y = new double[n1];
    m_e = new double[2*n];
    c_n = new int[2*n];
    r_s = new int[n+1];
    vmx = new double[n];
    y = sp_diff_2(n);
    // Use for loops to assign the matrix entries,column number and row start arrays
    for (int i=1;i<=2*n;i++)
    {
        m_e[i-1] = y[i];
        c_n[i-1] = y[2*n+i];
    }
    for (int i=1+4*n;i<n1;i++)
    {
        r_s[i-1-4*n] = y[i];
    }
    // h is the distance between each x and the next x value as they are uniformly distributed
    h = 2/double(n);
    // Use a for loop to compute the x values and the function value at each of those x's
    for (int i=0;i<n;i++)
    {
        x[i] = -1+(i+1)*h;
        u[i] = compute_f(x[i]);
    }
    // Define t1 ******************************************
    clock_t t1, t2;
    t1 = clock();
    // Use sp_matrix_multiply to multiply the second order differentiation matrix and the function values
    estans = sp_matrix_multiply(m_e,c_n,r_s,u,n);
    t2 = clock();


    // A for loop to compute the exact derivative
    for (int i=0;i<n;i++)
    {
        ans[i] = compute_df(x[i]);
    }


    std::cout << "Question 2b)\n\nThe exact derivative is: ( ";
    // Use a for loop to output the exact derivative
    for (int i=0;i<n;i++)
    {
        std::cout << ans[i] << " ";
    }

    long double approx_t = (double(t2-t1))/CLOCKS_PER_SEC;

    std::cout << ")\n\nThe approximate derivative is: ( ";
    // A for loop to output the approximate derivative and calculate the difference between the exact and approximate derivative
    for (int i=0;i<n;i++)
    {
        std::cout << (1/h)*estans[i] << " ";
        vmx[i] = fabs(ans[i]-(1/h)*estans[i]);
    }

    std::cout << ")\n\nThe CPU time used is: " << approx_t << "ms\n\n";
    // Output the error as the max of the differences between the exact and approximate derivative
    std::cout << "The error is: " << vmax(vmx,n)[0] << ", it occurs at x = " << x[int(vmax(vmx,n)[1])] << "\n\n";

    // Deallocate the memory for the dynamic arrays
    // This is so the variable names can be used again
    delete[] u;
    delete[] ans;
    delete[] estans;
    delete[] x;
    delete[] y;
    delete[] m_e;
    delete[] c_n;
    delete[] r_s;
    delete[] vmx;

    // Define some more dynamic arrays needed to create a loop of different n values and calculate the desired alpha/error values
    int *m;
    double alpha, *err;
    err = new double[5];
    m = new int[5];
    // A for loop to get the desired n values needed
    for (int i=0;i<5;i++)
    {
        m[i] = pow(2,i+2);
    }
    // A for loop that does almost the same as above but also stores the error value in an array and calculates the alpha values
    std::cout << "The alpha values are: ( ";
    for(int j=0;j<5;j++)
    {
        // Set n as the appropriate value given in the question
        n = m[j];
        // Lines 115-154 are the same as above
        n1 = 1+4*n+n+1;
        u = new double[n];
        ans = new double[n];
        estans = new double[n];
        x = new double[n];
        y = new double[n1];
        m_e = new double[2*n];
        c_n = new int[2*n];
        r_s = new int[n+1];
        vmx = new double[n];
        y = sp_diff_2(n);

        for (int i=1;i<=2*n;i++)
        {
            m_e[i-1] = y[i];
            c_n[i-1] = y[2*n+i];
        }
        for (int i=2+4*n;i<=n1;i++)
        {
            r_s[i-2-4*n] = y[i-1];
        }

        h = 2/double(n);
        for (int i=0;i<n;i++)
        {
            x[i] = -1+(i+1)*h;
            u[i] = compute_f(x[i]);
        }

        estans = sp_matrix_multiply(m_e,c_n,r_s,u,n);

        for (int i=0;i<n;i++)
        {
            ans[i] = compute_df(x[i]);
        }

        for (int i=0;i<n;i++)
        {
            vmx[i] = fabs(ans[i]-(1/h)*estans[i]);
        }
        // Set the error as the max of the differences between the exact and approximate derivative
        err[j] = vmax(vmx,n)[0];
        // Deallocate the memory for the dynamic arrays
        delete[] u;
        delete[] ans;
        delete[] estans;
        delete[] x;
        delete[] y;
        delete[] m_e;
        delete[] c_n;
        delete[] r_s;
        delete[] vmx;
        // Calculate and output the alpha value
        if (j>0)
        {
            alpha = log2(err[j-1])-log2(err[j]);
            std::cout << alpha << " ";
        }
    }

    std::cout << ")\n\n\n";
}
