#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{

int rank, size, n=15;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
int n_local = n/size;
int mod= n%size;
int modx=0;
if (rank<mod){
  n_local++;
}
int* proc_shared = (int*) malloc(n_local*n * sizeof(int));
if (rank!=0){
MPI_Send(proc_shared, n_local*n, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
if(rank>=mod){
 modx=mod;
}
for (int i=0; i<n_local; i++){
    for (int j=0; j<n; j++){
      if(i*(n+1)+rank*n_local+modx==i*n+j){
        proc_shared[i*n+j]=1;}
        printf("%d,", proc_shared[i*n+j]);
    }
    printf("\n");
  }


if (rank!=0){
  MPI_Send(proc_shared, n_local*n, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

MPI_Recv(m, rows * n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
/*
    for (int i=0; i<n_local; i++){
          for (int j=0; j<n; j++){
            printf("%d,", proc_shared[i*n+j]);
            }
    printf("\n");

          }
  */


MPI_Finalize();
free(proc_shared);
return 0;
}
