// Include the necessary packages and function prototype
#include <iostream>
#include <cmath>

void q3();
double **allocate_matrix(int no_rows, int no_cols);
void deallocate_matrix(int no_rows, double **matrix);
double *evaluate_user_function(double (*func)(double x),double *x, int n);
double compute_f(double x);
double **diff_cheb(int n);
double **multiply(int n, int m, int l, double **mat1, double **mat2);
double *multiply(int n, int m, double **matrix, double *vec);

void q3()
{
    // Define and initialize the required variables and dynamic arrays
    int n = 10;
    int m = 2550;
    double t_end = 10;
    double k = t_end/double(m);
    double *t, *x, **u, **dcheb, *u0;
    t = new double[m+1];
    x = new double[n+1];
    u0 = new double[n+1];
    u = allocate_matrix(m+1,n+1);
    // A for loop to find the t values
    for (int i=0;i<=m;i++)
    {
        t[i] = i*k;
    }
    // A for loop to find the Chebyshev values
    for (int i=0;i<=n;i++)
    {
        x[i] = cos(M_PI*i/double(n));
    }
    // Set the first row of the matrix as the function valued at the Chebyshev points
    u[0] = evaluate_user_function(compute_f,x,n+1);
    dcheb = allocate_matrix(n+1,n+1);
    // Use the diff_cheb function to create an n+1 size matrix as a dynamic array
    dcheb = diff_cheb(n);
    // Use the multiply function to square the differential Chebyshev matrix
    dcheb = multiply(n+1,n+1,n+1,dcheb,dcheb);
    // Use a for loop to iteratively find the next row of the matrix u
    for (int i=1;i<=m;i++)
    {
        // Multiply the differential Chebyshev matrix and previous u row
        u0 = multiply(n+1,n+1,dcheb,u[i-1]);
        // A for loop to calculate each value in the matrix row using the iterative formula
        for (int j=0;j<=n;j++)
        {
            u[i][j] = u[i-1][j] + k*u0[j];
        }
        // Set the boundary conditions
        u[i][0] = 0;
        u[i][n] = 0;
    }
    // Output the final u value
    std::cout << "Question 3)\n\nThe u value for x = 0 at time T = 10 and m = " << m <<" is " << u[m][5] << "\n\n";
    delete[] t;
    delete[] x;
    delete[] u0;
    deallocate_matrix(m+1,u);
    deallocate_matrix(n+1,dcheb);
}
