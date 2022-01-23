#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{

int n = atoi(argv[1]);
int rank, size;
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
  }

}

if (rank!=0){
  MPI_Send(proc_shared, n_local*n, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

if (rank==0 && size>1&&n<=16)
{
MPI_Status status;
for (int i=1; i<=size; i++){
MPI_Recv(proc_shared, n_local*n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
}
for (int i=0; i<n_local; i++){
  for (int j=0; j<n; j++){
      printf("%d,", proc_shared[i*n+j]);
    }
  printf("\n");
}
}

/*
elseif (n>=16){
FILE *fp;
fp = fopen("Output.txt", "w");
for (int i=0; i<n_local; i++){
    for (int j=0; j<n; j++){
      if(i*(n+1)+rank*n_local+modx==i*n+j){
        proc_shared[i*n+j]=1;
        fprintf(fp, "%d", proc_shared[i*n+j]);
      }
    }
    FILE *fp;
    fp = fopen("Output.txt", "w");
      fprintf(fp,"\n");
}

fclose(fp);
<<<<<<< HEAD

}
/*
if (rank!=0){
  MPI_Send(proc_shared, n_local*n, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

if (rank=0){
MPI_Recv(proc_shared, n_local*n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);}
=======
>>>>>>> a2564592be7c66c078d4c6f7938e4ff6a4b2b7a5
*/







MPI_Finalize();
free(proc_shared);
return 0;
}
