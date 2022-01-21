#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{

<<<<<<< HEAD
int n=atoi(argv[1]);
int rank, size, n=15;
=======
int n = atoi(argv[1]);
int rank, size;
>>>>>>> b742187666d581ccd3c1b0cab8a0267b5ce5fa1e
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
int n_local = n/size;
int mod= n%size;
int modx=0;
if (rank<mod){
  n_local++;
}
int* proc_shared = (int*) calloc(n_local*n , sizeof(int));

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

/*
if (rank!=0){
  MPI_Send(proc_shared, n_local*n, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

if (rank=0){
MPI_Recv(proc_shared, n_local*n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);}
*/



MPI_Finalize();
free(proc_shared);
return 0;
}
