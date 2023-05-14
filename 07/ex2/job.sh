#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

module load gcc/10.3.0

make

printf "\nfloat_seq\n"
for i in {1..10}; do ./float_seq; done
printf "\n./float_omp\n"
for i in {1..10}; do ./float_omp; done
printf "\ndouble_seq\n"
for i in {1..10}; do ./double_seq; done
printf "\ndouble_omp\n"
for i in {1..10}; do ./double_omp; done