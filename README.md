## 1. Distributed parallel computing
Task 2 - Non parallelized matrix multiplication - Fayaz

The first algorithm to implement is the non-parallelized matrix multiplication algorithm. With this I first initiated the matrix that will will be the one to possess the output with zeros. Then wrote two for loops to multiply the two input matrices and stored the value in the zero initialized matrix.

2. SIMD
Single Instruction Multiple Data is described by its own name. The implementation of the algorithm involved getting multiple parts of the matrices and then doing the multiplication and adding at once, instead of multiplying adding and storing for just one spot in the matrix. In this instance, the columns of matrix C is vectorized and its information is stored. The first for loop zero initializes the column, then stores the number in that column then moves to the next one. 

### Assignment

Multiplication of two matrices has to be implemented as

* MPI standard
* OpenMp memory program

Task is to multiply two matrices, and to multiply two matrices, the number of colums of the first matrix has to match the number of lines
of the second matrix. Calculation has independent steps and parrelization is possible.

### IMPLEMENTATION

OpenMP 
The OpenMP implementation is just the program with the omp pragma over the first for-loop. This progma can only be used in the outer loop.
There are independent implementation. Performance increases by a lot compared to the program without parrelization. 

```
#pragma omp for  
                for (int k=0; k<ncols; k++){
                    for (int i=0; i<rows; i++){
                        cc1[i][k] = 0.0; 
                        for(int j=0; j<brows; j++){
                            cc1[i][k] += aa[i][j] * bb[j][k];
```


### MPI

Receive two input matrices from files entered as command line arguments.  Check matrices for compatibility and if they're not compatible, end the program and if they are compatible, go through with the rest of the execution. Generate two matrices from the two matrices from the file and send one matrix to the slaves and send rows of the other matrix to processes.  Master listens to receive info from the slaves and the processes and an A x B matrix is calculated using the data received. The result matrix is printed to the screen and is also put into an output text file. 

To compile the mpi.c file, execute the following commands in case Makefile does not compile it properly.

```
mpicc -c -fopenmp -O3 mpi.c
```
and then
```
mpicc -o mpi -fopenmp -O3 mmult.o mpi.o
```

Run the MPI multiplication with two input matrix text files with the following example command.
```
mpiexec -f ~/hosts -n x input1.txt input2.txt
```
where x is the number of processes that the program uses and input1.txt is the first matrix and input2.txt is the second matrix.

## 2. Team work
The team team consisted of 3 members, Dawud, Saad, and Fayaz. Each member was assigned about 2 tasks to complete for this project. Dawud's tasks are to "Automate running  matrix multiplication on different size matrix and generating data in tabular format for graph production." and "Matrix multiplication in C  on Wolfgand cluster with  OpenMP (easy, try mmult_omp_timing)". Saad's tasks are to implement "Matrix multiplication in C  on Wolfgand cluster with MPI (Distribitued Memory)" and "Produce graphs". The remaining 3 task, the two that are chosen from the list of four and the last task is to be worked on together. The master branch was locked and so when any new changes were committed and pushed onto private branch and then pull requested to the master branch, two reviews were required to ensure that the code was thoroughly checked and approved. 

## 3. Full project life cycle
The Trello project board was used for this lab because of its ease of access and helpful attributes. It helps in notifying everyone where the project currently is and what needs to be done further in order to succeed in finishing on time. All the tasks are given its own card and has the name of the person who is assigned the task on it. Four states were assigned to each task as it progressed through the project, "To do", "Doing", "Review Needed", "Done". This helps in staying organized and making sure the project progresses smoothly. 

Adapting to the C environment after doing the last few labs in Java was a difficult task. The team members needed to review old material from Operating Systems class and also adjust to the new information that was given. Also, the tasks were somewhat confusing because it was something that we never encountered in previous classes. Managing the project was something that required a great deal of multitasking because so many moving parts were involved. First off the team had to be coordinated in order to make sure that GitHub did not encounter any problems. This meant that we could not necessarily work on the project all at the same time. There was also the issue of SSH(ing), sometimes the connection wouldn't connect for some odd reason. Lastly, after using Netbeans to commit, push, and pull, it  required effort to get used to linux commands to do those tasks. Also, the Putty environment was something that needed some work relearning. It is not as easy as NetBeans, neither are there errors shown while typing in real time, nor is there a scrolling mechanism to speed up the process of coding.
