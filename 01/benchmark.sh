!/bin/bash

 print usage if argument count is not 2
if [ $# -ne 2 ]; then
  echo "Usage: $0 <executable> <number of threads"
  exit 1
fi

 execute file at $1 with OMP_NUM_THREADS=core_count for core count 1 to $2
for ((i = 1; i <= $2; i++)); do
  export OMP_NUM_THREADS=$i
  echo "Running $1 with $i threads"
  ./"$1"
done

#for cluster

# print usage if argument count is not 1
#if [ $# -ne 1 ]; then
#  echo "Usage: $0 <executable>"
#  exit 1
#fi

#export OMP_NUM_THREADS=1
#echo "Running $1 with 1 threads"
#./"$1"
#export OMP_NUM_THREADS=8
#echo "Running $1 with 8 threads"
#./"$1"
