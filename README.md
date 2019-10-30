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


