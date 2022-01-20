#!/bin/bash #

for i in {1, 2, 4,8};do
#SBATCH --job-name=matrix_multi
#SBATCH -N $i
#SBATCH --ntasks-per-node=1
#SBATCH --time=04:00:00
#SBATCH --cpus-per-task=1
#SBATCH --partition=regular2
#SBATCH --mail-type=FAIL,END
#SBATCH --mail-user=znazari@ictp.it

module purge
module load gnu8/8.3.0
module load openmpi3/3.1.4
cd $SLURM_SUBMIT_DIR

mpicc matrix_multi.c -o matrix_multi.x -Wall -Wextra


mpirun -np 2 ./matrix_multi.x
done
