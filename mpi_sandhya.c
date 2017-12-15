#include <stdio.h>
#include "mpi.h"


MPI_Status status;


int main(int argc, char **argv)
{
  int numtasks,taskid,numworkers,source,dest,rows,offset,i,j,k,p,q,r,s;

  printf("\nEnter the number of rows and columns for Matrix A:::\n\n");
  scanf("%d %d", &p, &q);
  
  printf("\nEnter the number of rows and columns for Matrix B:::\n\n");
  scanf("%d %d", &r, &s);
  double a[p][q],b[r][s],c[p][s];


  //struct timeval start, stop;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  numworkers = numtasks-1;

  /*---------------------------- master ----------------------------*/
  if (taskid == 0) {
    for (i=0; i<p; i++) {
      for (j=0; j<q; j++) {
        //a[i][j]= 1.0;
	a[i][j] = rand()%5 + 1;
        //b[i][j]= 2.0;
      }
	
    for (i=0; i<r; i++) {
      for (j=0; j<s; j++) {
        //a[i][j]= 1.0;
	b[i][j] = rand()%5 + 1;
        //b[i][j]= 2.0;
      }
    }

    //gettimeofday(&start, 0);

    /* send matrix data to the worker tasks */
    rows = p/numworkers;
    offset = 0;

    for (dest=1; dest<=numworkers; dest++)
    {
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&a[offset][0], rows*p, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
      MPI_Send(&b, p*q, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
      offset = offset + rows;
    }

    /* wait for results from all worker tasks */
    for (i=1; i<=numworkers; i++)
    {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&c[offset][0], rows*p, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
    }

    //gettimeofday(&stop, 0);

    printf("Here is the result matrix:\n");
    for (i=0; i<p; i++) {
      for (j=0; j<q; j++)
        printf("%6.2f   ", c[i][j]);
      printf ("\n");
    }

    //printf(stdout,"Time = %.6f\n\n",
      //   (stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));

  }

  /*---------------------------- worker----------------------------*/
  if (taskid > 0) {
    source = 0;
    MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&a, rows*p, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&b, p*q, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

    /* Matrix multiplication */
    for (k=0; k<p; k++)
      for (i=0; i<rows; i++) {
        c[i][k] = 0.0;
        for (j=0; j<N; j++)
          c[i][k] = c[i][k] + a[i][j] * b[j][k];
      }


    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&c, rows*p, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
