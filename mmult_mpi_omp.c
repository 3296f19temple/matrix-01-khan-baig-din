#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);
int get_rows(char *filename);
int get_cols(char *filename);

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
  
  int m1rows, m1cols, m2rows, m2cols;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
  m1rows = get_rows(argv[1]);
  m1cols = get_cols(argv[1]);
  m2rows = get_rows(argv[2]);
  m2cols = get_cols(argv[2]);
    
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
    } else {
      // Slave Code goes here
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}

int get_rows(char *filename){
    FILE *fp = fopen(filename, "r");
    int ch = 0;
    int rows = 1;

    if (fp == NULL){
        return 0;
    }
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            rows++;
        }
    }
    fclose(fp);
    return rows;
}

int get_cols(char *filename){
    FILE *fp = fopen(filename,"r");
    char buffer[100];
    int columns = 1;

    if(fp == NULL){
        return 0;
    }
    char *line = fgets(buffer, 100, fp);
    for(int i=0; buffer[i]; i++){
        if(buffer[i] == ' '){
            columns++;
        }
    }
    fclose(fp);
    return columns;
}
