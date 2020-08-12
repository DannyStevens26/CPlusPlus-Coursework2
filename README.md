# CPlusPlus-Coursework2
My solutions to the second coursework in Introduction to C++ module.
This coursework initially deals with matrix operations with matrices in Compressed Sparse Row (CSR) and then approximates derivatives using finite difference in matrix form.

The file mat.cpp contains seven functions sp_matrix_multiply, sp_diff_2, diff_cheb, vmax, allocate_matrix, deallocate_matrix and multiply. 
sp_matrix_multiply multilies a matrix in CSR form and a vector
sp_diff_2 computes the periodic second order finite difference differentiation matrix of order 2 in CSR form
diff_cheb computes the Chebyshev differentiation matrix for a given n 
vmax outputs the maximum entry in an array as well as its position in the array
allocate_matrix allocates dynamic memory for a matrix
deallocate_matrix deallocates dynamic memory for a matrix
multiply is an overloaded function used to multiply matrices or matrices and vectors

The file fun.cpp contains three functions compute_f, compute_df and evaluate_user_function.
compute_f returns the exact value of the function given in the question at a point x
compute_df returns the exact derivative value of the function given in the question at a point x
evaluate_user_function ch evaluates a real function at multiple points

The file input.dat is read from by the functions.

The files q1a.cpp-q3.cpp are expamples of the functions above being used.
