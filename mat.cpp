// Include the necessary packages and function prototype
#include <iostream>
#include <cassert>
#include <cmath>

double *sp_matrix_multiply(double *matrix_entries, int *column_no, int *row_start, double *x, int n);
double *sp_diff_2(int n);
double **diff_cheb(int n);
double *vmax(double *x,int n);
double **allocate_matrix(int no_rows, int no_cols);
void deallocate_matrix(int no_rows, double **matrix);
double *multiply(int n, int m, double *vec, double **matrix);
double **multiply(int n, int m, int l, double **mat1, double **mat2);
double *multiply(int n, int m, double **matrix, double *vec);


double *sp_matrix_multiply(double *matrix_entries, int *column_no, int *row_start, double *x, int n)
{
    // Define and initialize the dynamic array and then the variables
    double *Ax;
    Ax = new double[n];
    int row_amount, mat_start;
    // Preset the matrix start variable as zero, this will be used so the algorithm knows where to read the matrix entries/column number array from
    mat_start = 0;
    // A for loop to find each vector value
    for (int i=0;i<n;i++)
    {
        // Preset the vector value as 0
        Ax[i]=0;
        // Find the amount of non zeros in the matrix row
        row_amount = row_start[i+1]-row_start[i];
        // Use a for loop that goes from where the row ended up to where the row ended plus the amount of row non zeros
        // The loop sums the multiplications between the non zero values and the appropriate x values
        for (int j=mat_start;j<mat_start+row_amount;j++)
        {
            Ax[i] = Ax[i] + matrix_entries[j]*x[column_no[j]-1];
        }
        // Recalculate the matrix start value
        mat_start = mat_start+row_amount;
    }
    return Ax;
}

double *sp_diff_2(int n)
{
    // Assert that the matrix is large enough
    assert(n>2);
    // Define and initialise the arrays
    double *m_e, *c_n, *r_s, *x;
    x = new double[1+(4*n)+(n+1)];
    m_e = new double[2*n];
    c_n = new double[2*n];
    r_s = new double[n+1];
    // Set the column number/matrix entries/row start array values that can't be set in a loop
    c_n[0] = 2;
    c_n[1] = n;
    c_n[2*n-1] = n-1;
    c_n[2*n-2] = 1;
    m_e[0] = 1./2.;
    m_e[1] = -1./2.;
    m_e[2*n-1] = -1./2.;
    m_e[2*n-2] = 1./2.;
    r_s[0] = 1;
    // Use a for loop to set the rest of the array values
    for (int i=1;i<n-1;i++)
    {
        m_e[2*i] = -1./2.;
        m_e[2*i+1] = 1./2.;
        c_n[2*i] = i;
        c_n[2*i+1] = i+2;
    }
    for (int i=0;i<n;i++)
    {
        r_s[i+1] = 2+r_s[i];
    }
    // As the output can only be a single array, put all the information in a single dynamic array x using a for loop
    x[0]=n;
    for (int i=1;i<1+(4*n)+(n+1);i++)
    {
        if (i<=2*n)
        {
            x[i] = m_e[i-1];
        }
        else if (i>2*n && i<=4*n)
        {
            x[i] = c_n[i-2*n-1];
        }
        else
        {
            x[i] = r_s[i-4*n-1];
        }
    }
    // Deallocate the memory for the dynamic arrays
    delete[] m_e;
    delete[] c_n;
    delete[] r_s;
    return x;
}

double **diff_cheb(int n)
{
    // Assert that the matrix is big enough
    assert(n>1);
    // Define and initialise the arrays of appropriate size
    double **D, *x, *c;
    x = new double[n+1];
    c = new double[n+1];
    D = allocate_matrix(n+1,n+1);
    // Set the c values in the array to be accessed when calculating the Chebyshev differentiation matrix values
    c[0] = 2;
    c[n] = 2;
    for (int i=1;i<n;i++)
    {
        c[i] = 1;
    }
    // Use a for loop to find the Chebyshev values
    for (int i=0;i<=n;i++)
    {
        x[i] = cos(M_PI*double(i)/double(n));
    }
    // Set the matrix values that can't be set in a for loop, i.e. the leading diagonal corners
    D[0][0] = (2*pow(n,2)+1)/6.;
    D[n][n] = -(2*pow(n,2)+1)/6.;
    // Use a for loop to set the leading diagonal values
    for (int i=1;i<n;i++)
    {
        D[i][i] = -x[i]/(2*(1-pow(x[i],2)));
    }
    // A nested for loop to set the rest of the values in the matrix with an if statement so the leading diagonal values aren't rewritten
    for (int i=0;i<=n;i++)
    {
        for (int j=0;j<=n;j++)
        {
            if (i!=j)
            {
                D[i][j] = (c[i]/c[j])*(pow(-1,i+j)/(x[i]-x[j]));
            }
        }
    }
    // Deallocate the memory for the dynamic arrays
    delete[] x;
    delete[] c;
    return D;
}

double *vmax(double *x,int n)
{
    // Define and initialize the arrays/variables
    // Use mx as the maximum x value, set it initially as less than the first value of the array, the first for loop will then set the max as the first element in the array
    double mx = x[0]-1;
    double *ans;
    ans = new double[2];
    int cnt;
    // A for loop to check each value of the array, the if statement sets mx to the new max value, the count gives the index of the max value
    for(int i=0;i<n;i++)
    {
        if (x[i]>mx)
        {
            mx = x[i];
            cnt = i;
        }
    }
    // Return the array with the max value and the location of the value
    ans[0] = mx;
    ans[1] = double(cnt);
    return ans;
}

// The rest of the functions were already given

double **allocate_matrix(int no_rows, int no_cols)
{
    double **matrix;
    matrix = new double*[no_rows];
    for (int i=0; i<no_rows; i++)
    {
        matrix[i] = new double[no_cols];
    }
    return matrix;
}

void deallocate_matrix(int no_rows, double **matrix)
{
    for (int i=0;i<no_rows;i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double *multiply(int no_rows, int no_cols, double **matrix, double *vec)
{
    double *matvecprod;

    matvecprod = new double[no_rows];
    for (int i=0;i<no_cols;i++)
    {
        matvecprod[i]=0;
        for (int j=0;j<no_cols;j++)
        {
            matvecprod[i] += matrix[i][j]*vec[j];
        }
    }
    return matvecprod;
}

double *multiply(int n, int m, double *vec, double **matrix)
{
    double *vecmatprod;
    vecmatprod = new double[n];
    for (int j=0;j<n;j++)
    {
        vecmatprod[j]=0;
        for (int i =0;i<m;i++)
        {
            vecmatprod[j]+=vec[i]*matrix[i][j];
        }
    }
    return vecmatprod;
}


double **multiply(int n, int m, int l, double **mat1, double **mat2)
{
    double **matans;
    matans = allocate_matrix(n,l);
    for (int i=0;i<n;i++)
    {
        matans[i] = multiply(m,l,mat1[i],mat2);
    }
    return matans;
}


