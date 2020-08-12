// Include the necessary packages and function prototype
#include <iostream>
#include <fstream>
#include <cassert>

double *sp_matrix_multiply(double *matrix_entries, int *column_no, int *row_start, double *x, int n);
void q1b();

void q1b()
{
    // Define an input stream called matfile
    std::ifstream matfile;
    // Open the file input.dat
    matfile.open("input.dat");
    // Assert the file is open
    assert(matfile.is_open());

    // Repeat the process as in Question 1a)
    int n, zeros;
    matfile >> n;
    matfile >> zeros;
    int nonzeros = (n*n)-zeros;
    double *matrix_entries, *x, *Ax;
    int *column_no, *row_start;
    matrix_entries = new double[nonzeros];
    column_no = new int[nonzeros];
    row_start = new int[n+1];
    Ax = new double[n];

    for (int i=0;i<nonzeros;i++)
    {
        matfile >> matrix_entries[i];
    }

    for (int i=0;i<nonzeros;i++)
    {
        matfile >> column_no[i];
    }

    for (int i=0;i<n+1;i++)
    {
        matfile >> row_start[i];
    }

    // Define the vector x that the matrix A will multiply
    x = new double[n];
    x[0] = 6.;
    x[1] = 0.5;
    x[2] = 2.;
    x[3] = -1.5;

    std::cout << "Question 1b)\n\nAx is: ( ";
    // Use the function sp_matrix_multiply
    Ax = sp_matrix_multiply(matrix_entries,column_no,row_start,x,n);
    // Use a for loop to output the dynamic array
    for (int i=0;i<n;i++)
    {
        std::cout << Ax[i] << " ";
    }

    std::cout << ")\n\n\n";
    delete[] matrix_entries;
    delete[] x;
    delete[] Ax;
    delete[] column_no;
    delete[] row_start;
}
