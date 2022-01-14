#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//stdlib.h for memory allocation. To use for instance the malloc.

int main(int argc, char **argv[])
{


MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
int n_local = n/total_p;
int rank, total_p, n=(argv[1])
int n_shared = n*n_local;

double* a_proc_shared = (double*) malloc(n_local*n * sizeof(double));
double* b_proc_shared = (double*) malloc(n_local*n * sizeof(double));
double* c_proc_shared = (double*) malloc(n_local*n * sizeof(double));


MPI_Allgather(&a_proc_shared, n_local*n_local, MPI_DOUBLE, &ctotal, n_local*n_local, MPI_DOUBLE, MPI_COMM_WORLD);

MPI_Send(proc_elements, proc_elementShare, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

for (i=0; i<n_shared; i++){
  for (j=0; j<n_shared; j++){
    if(i==j){
      a_proc_shared[i*n+j]=1
    }
    else{a_proc_shared[i*n+j]=0}
  }
}

/*
for (int i=0; i<proc_rowShare; i++){
  proc_elements[(i+rank*proc_rowShare)*(m+1)-rank*proc_elementShare]=1;
}

if (rank!=0)
MPI_Send(proc_elements, proc_elementShare, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

if (rank==0){
  if (Matrix_size<16){
    if (m<16){
      for (int p=0;p<size;p++){
        for (int i=0;i<proc_elementShare;i++){
          printf("%lf ", proc_elements[i]);
          if ((i+1)%m==0)
          printf("\n");
        }
        if(p!=size-1)
        MPI_Recv(proc_elements, proc_elementShare, MPI_DOUBLE, p+1,0,MPI_COMM_WORLD, &status);
      }
    }
  }


}
*/
free(proc_shared);
free(b_proc_shared);
free(b_proc_shared);
MPI_Finalize();

return 0;
}
