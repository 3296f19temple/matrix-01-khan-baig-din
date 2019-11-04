#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);
//Matrix multiplication in C  on Wolfgand cluster without parallelization
int woP(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);

/** 
    Program to multiply a matrix times a matrix using both
    mpi to distribute the computation among nodes and omp
    to distribute the computation among threads.
*/



int main(int argc, char* argv[])
{
  int nrows, ncols;
  double *aa;	/* the A matrix */
  double *bb;	/* the B matrix */
  double *cc1;	/* A x B computed using the omp-mpi code you write */
  double *cc2;	/* A x B computed using the conventional algorithm */
  int myid, numprocs;
  double starttime, endtime;
  MPI_Status status;

  /* insert other global variables here */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  
  
  FILE *fp1
  FILE *fp2;
  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");

  getRowsAndColumns = fscanf(fp1, "rows(%d) cols(%d)", &m1rows, &m1cols);
  getRowsAndColumns = fscanf(fp2, "rows(%d) cols(%d)", &m2rows, &m2cols);

  if(m1cols != m2rows){
      printf("Incompatible matrices\n");
  }

   if (argc > 1) {
    nrows = atoi(argv[1]);
    ncols = nrows;
    if (myid == 0) {
      // Master Code goes here
      aa = gen_matrix(nrows, ncols);
      bb = gen_matrix(ncols, nrows);
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      /* Insert your master code here to store the product into cc1 */
      endtime = MPI_Wtime();
      printf("%f\n",(endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      compare_matrices(cc2, cc1, nrows, nrows);

      woP(cc2, aa, nrows, ncols, bb, ncols, nrows);
    } else {
      // Slave Code goes here
      
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}



int woP(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols){
  int i, j, k;
  for (i = 0; i < aRows; i++) {
    for (j = 0; j < bCols; j++) {
      c[i][j] = 0;
    }
    for (k = 0; k < aCols; k++) {
        c[i][j] += a[i][k]* b[k][j];
      }
  }
  return 0 ;
}

