//This is the non parallelized matrix multiplication

#include<math.h>
#include<time.h>

double woP(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols){
//https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/ --> used to learn timing of a function
clock_t start, end;
double time_taken;  

start = clock();

 int i, j, k;
  for (i = 0; i < aRows; i++) {
    for (j = 0; j < bCols; j++) {
      c[i][j] = 0;
    }
    for (k = 0; k < aCols; k++) {
        c[i][j] += a[i][k]* b[k][j];
      }
  }

end = clock();

time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
  return time_take;
}
