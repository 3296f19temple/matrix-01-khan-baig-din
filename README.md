Task 2 - Non parallelized matrix multiplication - Fayaz
The first algorithm to implement is the non-parallelized matrix multiplication algorithm. With this I first initiated the matrix that will will be the one to possess the output with zeros. Then wrote two for loops to multiply the two input matrices and stored the value in the zero initialized matrix.


#Assignment#

Multiplication of two matrices has to be implemented as

* MPI standard
* OpenMp memory program

Task is to multiply two matrices, and to multiply two matrices, the number of colums of the first matrix has to match the number of lines
of the second matrix. Calculation has independent steps and parrelization is possible.

##IMPLEMENTATION#

OpenMP 
The OpenMP implementation is just the program with the omp pragma over the first for-loop. This progma can only be used in the outer loop.
There are independent implementation. Performance increases by a lot compared to the program without parrelization. 

'#pragma omp for  
                for (int k=0; k<ncols; k++){
                    for (int i=0; i<rows; i++){
                        cc1[i][k] = 0.0; 
                        for(int j=0; j<brows; j++){
                            cc1[i][k] += aa[i][j] * bb[j][k];'


MPI


