# Assignment 1
## Exercise 1

- How is the speedup of a parallel program defined?
  - It is defined as the ratio between the execution time with one processor compared to the execution time with n 
processors that execute in parallel.
- What is the formal definition of Amdahl's law, and what relationship does it describe for parallel programs (explain 
in your own words)? Why/How is this significant?
  - Amdahl's law states that the speedup of a parallel program is limited by the part of a program that cannot be 
parallelized. It is significant because it provides the theoretical limitations of a parallel program.
- Compute the theoretical speedup of a program that spends 10% of its time in unparallelizable, sequential regions for 
6 cores and for a hypothetically unlimited number of cores.
  - 6 cores (using amdahl's law = p/(1 + (p - 1)f)):  
    - p = 6
    - f = 0.1
    - speedup = 6 ÷ ( 1 + ( 6 - 1 ) × 0.1 ) = 4
  - unlimited cores (limit = 1/f): 
    - maximum speedup = 10
- Compute the theoretical speedup of a program that spends 20% of its time in unparallelizable, sequential regions for 
6 cores and for a hypothetically unlimited number of cores.
  - 6 cores:
    - p = 6
    - f = 0.2
    - speedup = 6 ÷ ( 1 + ( 6 - 1 ) × 0.2 ) = 3
  - unlimited cores:
    - maximum speedup = 5
- Given an algorithm of time complexity O(n^3). How large (in %) can the unparallelizable, sequential region be at most, 
such that a speedup of 10 can be achieved using 64 cores?
  - 0.086%