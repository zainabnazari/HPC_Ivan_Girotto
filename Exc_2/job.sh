#!/bin/bash #

for i in {1, 2, 4,8};do
#SBATCH --job-name=matrix_multi
#SBATCH -N $i
#SBATCH --ntasks-per-node20
#SBATCH --time=04:00:00
#SBATCH --cpus-per-task=1
#SBATCH --partition=regular1
#SBATCH --mail-type=FAIL,END
#SBATCH --mail-user=znazari@ictp.it
cd $SLURM_SUBMIT_DIR
mpicc matrix_multi.c -o matrix_multi.x -Wall -Wextra
module purge
module load gnu8/8.3.0
module load openmpi3/3.1.4

mpirun ./matrix_multi.x
done
