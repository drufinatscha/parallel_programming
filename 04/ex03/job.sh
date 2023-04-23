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

for i in {1..10}; do ./merge_sort_seq 100000000; done

printf "1 Thread: \n"
for i in {1..10}; do OMP_NUM_THREADS=1 ./merge_sort_omp 100000000; done

printf "\n2 Threads: \n"
for i in {1..10}; do OMP_NUM_THREADS=2 ./merge_sort_omp 100000000; done

printf "\n4 Threads: \n"
for i in {1..10}; do OMP_NUM_THREADS=4 ./merge_sort_omp 100000000; done

printf "\n8 Threads: \n"
for i in {1..10}; do OMP_NUM_THREADS=8 ./merge_sort_omp 100000000; done