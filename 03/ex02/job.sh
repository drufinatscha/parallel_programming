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

OMP_NUM_THREADS=1 printf "1 Thread: "
./ex2 1500
#for i in {1..10}; do ./ex2 1500; done

OMP_NUM_THREADS=2 printf "2 Threads: "
./ex2 1500
#for i in {1..10}; do ./ex2 1500; done

OMP_NUM_THREADS=4 printf "4 Threads: "
./ex2 1500
#for i in {1..10}; do ./ex2 1500; done

OMP_NUM_THREADS=8 printf "8 Threads: "
./ex2 1500
#for i in {1..10}; do ./ex2 1500; done