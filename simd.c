//This is the SIMD implementation
#include<time.h>
double mmult(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols) {

//https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/ --> used to learn timing of a function
clock_t start, end;
double time_taken;

start = clock();


  int i, j, k;
  for (i = 0; i < aRows; i++) {
    for (j = 0; j < bCols; j++) {
      c[i*bCols + j] = 0;
    }
    for (k = 0; k < aCols; k++) {
      for (j = 0; j < bCols; j++) {
        c[i*bCols + j] += a[i*aCols + k] * b[k*bCols + j];
      }
    }
  }

end = clock();

time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
return time_take;

}
