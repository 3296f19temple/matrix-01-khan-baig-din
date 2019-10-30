#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);

/**
    Program to multiply a matrix times a matrix using both
    mpi to distribute the computation among nodes and omp
    to distribute the computation among threads.
**/

int main(int argc, char* argv[])
{

    int nrows, ncols;
    double *aa;	/* the A matrix */
    double *bb;	/* the B matrix */
    double *cc1; /* A x B computed using the omp-mpi code you write */
    double *cc2; /* A x B computed using the conventional algorithm */
    int myid, numprocs;
    double starttime, endtime;
    MPI_Status status;

    int m1cols, m1rows, m2cols, m2rows;
    int dimensions, row, source;
    int rows = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    dimensions = fscanf(fp1, "rows(%d) cols(%d)", &m1rows, &m1cols);
    dimensions = fscanf(fp2, "rows(%d) cols(%d)", &m2rows, &m2cols);

    if(m1cols != m2rows)
    {
        printf("Incompatible matrices\n");
        exit(1);
    }

    if (argc > 1)
    {
        if (myid == 0)
        {
            char buffer1[50 * sizeof(double)];
            aa = malloc(sizeof(double) * m1rows * m1cols);
            int a;
            for(int i = 0; i < m1cols; i++)
            {
                for(int j = 0; j < m1rows; j++)
                {
                    a = fscanf(fp1, "%s", buffer1);
                    aa[i*m1rows + j] = atof(buffer1);
                }
            }

            char buffer2[50 * sizeof(double)];
            bb = malloc(sizeof(double) * m2rows * m2cols);
            int b;
            for(int i = 0; i < m2cols; i++)
            {
                for(int j = 0; j < m2rows; j++)
                {
                    b = fscanf(fp2, "%s", buffer2);
                    bb[i*m2rows + j] = atof(buffer2);
                }
            }

            starttime = MPI_Wtime();
            MPI_Bcast(bb, m2rows*m2cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            for(int i = 0; i < min(m1rows, numprocs-1); i++)
            {
                MPI_Send(&aa[(i)*m1rows], m1cols, MPI_DOUBLE, i+1, i+1, MPI_COMM_WORLD);
                rows++;
            }
            cc1 = malloc(sizeof(double) * m1rows * m2cols);
            double* receiveBuffer = malloc(sizeof(double) * m2cols);

            for(int i = 0; i < m1rows; i++)
            {
                MPI_Recv(receiveBuffer, m2cols, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                source = status.MPI_SOURCE;
                row = status.MPI_TAG;

                for(int k = 0; k< m2cols; k++)
                {
                    cc1[(row-1)*m2cols + k] = receiveBuffer[k];
                }
                if(rows < m1rows)
                {
                    MPI_Send(&aa[rows * m1rows], m1cols, MPI_DOUBLE, source, rows + 1,MPI_COMM_WORLD);
                    rows++;
                }
                else
                {
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, source, 0, MPI_COMM_WORLD);
                }
            }
            endtime = MPI_Wtime();
            printf("Time: %f\n",(endtime - starttime));

            cc2  = malloc(sizeof(double) * m2rows * m2cols);
            mmult(cc2, aa, m1rows, m1cols, bb, m2cols, m2rows);

            for(int i = 0; i < m1rows; i++)
            {
                for(int j = 0; j < m2cols; j++)
                {
                    printf("%f ", cc1[i*m2cols + j]);
                }
                printf("\n");
            }

            FILE* outputFile;
            outputFile = fopen("output.txt", "w");
            for(int i = 0; i < m1rows; i++)
            {
                for(int j = 0; j < m2cols; j++)
                {
                    fprintf(outputFile, "%f ", cc1[i*m2cols + j]);
                }
                fprintf(outputFile, "\n");
            }
            fclose(outputFile);

            fclose(fp1);
            fclose(fp2);

        }
        else
        {
            bb = malloc(sizeof(double) * m2rows * m2cols);
            MPI_Bcast(bb, m2rows*m2cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            if(myid <= m1rows)
            {
                while(1)
                {
                    double input[m1cols];
                    double output[m2cols];

                    MPI_Recv(&input, m1cols, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                    if(status.MPI_TAG == 0)
                    {
                        break;
                    }
                    row = status.MPI_TAG;
                    for (int i = 0; i < m2cols; i++)
                    {
                        double sum = 0;
                        for(int j = 0; j < m1cols; j++)
                        {
                            sum = sum + (input[j] * bb[j*m2cols + i]);
                        }
                        output[i] = sum;
                    }
                    MPI_Send(output, m2cols, MPI_DOUBLE, 0, row, MPI_COMM_WORLD);
                }
            }
        }
    }
    else
    {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
