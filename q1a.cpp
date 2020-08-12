// Include the necessary packages and function prototype
#include <iostream>
#include <fstream>
#include <cassert>


void q1a();
void q1b();
void q2a();
void q2b();
void q2ba();
void q2c();
void q3();
void q3z();

int main(int argc, char * argv[])
{

    q1a();
    q1b();
    q2a();
    q2b();
    q2c();
    q3();
}

void q1a()
{
    // Define an input stream called matfile
    std::ifstream matfile;
    // Open the file called input.dat
    matfile.open("input.dat");
    // Assert that the file is open
    assert(matfile.is_open());

    // Define the needed variables
    int n, zeros;
    double *matrix_entries;
    int *column_no, *row_start;
    // Read the first row of the file (the number of rows/columns)
    matfile >> n;
    // Read the second row (the number of zeros in the matrix)
    matfile >> zeros;
    // Calculate the number of non zeros
    int nonzeros = (n*n)-zeros;
    // Initialize the required vectors as dynamic arrays of the right size
    matrix_entries = new double[nonzeros];
    column_no = new int[nonzeros];
    row_start = new int[n+1];

    std::cout << "Question 1a)\n\nThe matrix entries vector is: ( ";
    // Use a for loop to read from the file and fill the matrix entries array and then output the values
    // Repeat this again for the column number array and the row start array
    for (int i=0;i<nonzeros;i++)
    {
        matfile >> matrix_entries[i];
        std::cout << matrix_entries[i] << " ";
    }

    std::cout << ")\nThe column number vector is: ( ";

    for (int i=0;i<nonzeros;i++)
    {
        matfile >> column_no[i];
        std::cout << column_no[i] << " ";
    }

    std::cout << ")\nThe row start vector is: ( ";

    for (int i=0;i<n+1;i++)
    {
        matfile >> row_start[i];
        std::cout << row_start[i] << " ";
    }

    std::cout << ")\n\n\n";
    // Deallocate the memory for the dynamic arrays
    delete[] matrix_entries;
    delete[] column_no;
    delete[] row_start;
}
