/*Doti SandhyaRani 
   (A04714047) 
    Adv OS Project 3 */

#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include <mpi.h>
#define N  10       

MPI_Status status;

int main(int argc, char **argv)
{
  int r1,c1,r2,c2,numtasks,world_rank,numworkers,source,dest,rows,offset,i,j,k;
  double a[N][N],b[N][N],c[N][N];


  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  numworkers = numtasks-1;

  /*---------------------------- master ----------------------------*/

  srand(time(NULL));
 
 if (world_rank == 0) {

	printf("Enter No.of rows for Matrix A \n");
	scanf("%d", &r1);
	printf("Enter No.of columns for Matrix A \n");
	scanf("%d", &c1);

	 for (i=0; i<r1; i++) {
     		 for (j=0; j<c1; j++) {
     			 
   			 a[i][j] = rand()%30 + 1;
     
    			   }
  		  }
	
  
	printf("Enter No.of rows for Matrix B \n");
	scanf("%d", &r2);
	printf("Enter No.of columns for Matrix B \n");
	scanf("%d", &c2);

	 for (i=0; i < r2; i++) {
     		 for (j=0; j < c2; j++) {
       
       		            b[i][j]= rand()%30 + 1;
                    
                	 }
               }	


    /* send matrix data to the worker tasks */
    rows = N/numworkers;
    offset = 0;

    for (dest=1; dest<=numworkers; dest++)
    {
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
      MPI_Send(&b, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
      offset = offset + rows;
    }

    /* wait for results from all worker tasks */
    for (i=1; i<=numworkers; i++)
    {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&c[offset][0], rows*N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
    }

 
  printf("\n\n");
	printf("******************************************\n");
    	printf("Result of Matrix Multiplication (A * B = C)\n");
     	printf("*******************************************\n");
	for (i=0; i<r1; i++) {
      for (j=0; j<c2; j++)
	        printf("%6.2f ", c[i][j]);
     		 printf ("\n");
    }

	printf("\n\n");
  }
	

  /*---------------------------- worker----------------------------*/
	 else  if (world_rank > 0) {
	source =0;
 	MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
   	MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    	MPI_Recv(&a, rows*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
    	MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

    /* Matrix multiplication */
    for (k=0; k<N; k++)
	 for (i=0; i<rows; i++) {
        	c[i][k] = 0.0;
        	for (j=0; j<N; j++)
         		 c[i][k] = c[i][k] + a[i][j] * b[j][k];
      }


	MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
  }
 
  
	if(world_rank == 0){
		printf("Its a master process :\n "); 
 		printf("rank %d out of %d processors \n",world_rank,numtasks);
	}
	else{
		
	                printf("rank %d out of %d processors \n",world_rank,numtasks);
	}
	MPI_Finalize();

}
