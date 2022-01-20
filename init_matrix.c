#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void print_stdout(int* matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			printf("%d ", matrix[i * cols + j]);
		}
		printf("\n");
	}
}

void print_file(int* matrix, int rows, int cols, FILE* file) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			fprintf(file, "%d ", matrix[i * cols + j]);
		}
		fprintf(file, "\n");
	}
}



int main(int argc, char** argv) {
  int r,p, n=6;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &r);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  int np = n/p;
  int x_np;
  int npMod = n%p;
  int x_npMod;
  int rType;

  if (npMod!=0 && r<npMod){
    x_np=np+1;
    x_npMod = 0;
  }else if (npMod!=0 && r>=npMod){
    x_np=np;
    x_npMod = npMod;
  }else if (npMod==0){
    x_np=np;
    x_npMod = 0;
  }
  int* m = (int*) calloc(x_np * n, sizeof(int));

  for (int i=0; i<x_np; i++){
//    m[r*x_np+i*(n+1)+x_npMod*n] = 1;
    m[(r*x_np+i+x_npMod)*(n+1)-(r*x_np+x_npMod)*n] = 1;
  }



  if (r == 0) {
    MPI_Status status;
    int flag = 0;
    int rows = x_np;
    if (n < 16) {
      print_stdout(m, x_np, n);
      for (int i = 1; i < p; i++) {
        if (i >= npMod && npMod != 0 && flag == 0) {
          rows--;
          flag = 1;
        }

        MPI_Recv(m, rows * n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        print_stdout(m, rows, n);
      }

    } else {
      FILE* file = fopen("result.out", "w");
      print_file(m, rows, n, file);
      for (int i = 1; i < p; i++) {
        if (i >= npMod && npMod != 0 && flag == 0) {
          rows--;
          flag = 1;
        }
        MPI_Recv(m, rows * n, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        print_file(m, rows, n, file);
      }
      fclose(file);
    }

  }else{
    MPI_Send(m, x_np * n, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  free(m);
	MPI_Finalize();
	return 0;
}
