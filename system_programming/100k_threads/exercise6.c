#include <omp.h> /* pragma omp */
#include <stdio.h> /* printf */

/*
Reviewer: Yarin
*/

/*

         89,745.96 msec task-clock                #    7.658 CPUs utilized          
             6,271      context-switches          #   69.875 /sec                   
                70      cpu-migrations            #    0.780 /sec                   
                86      page-faults               #    0.958 /sec                   
   238,587,185,500      cycles                    #    2.658 GHz                    
    70,152,801,706      instructions              #    0.29  insn per cycle         
    15,587,490,007      branches                  #  173.685 M/sec                  
         1,209,383      branch-misses             #    0.01% of all branches        

      11.718622987 seconds time elapsed

      89.699595000 seconds user
       0.059844000 seconds sys

*/

int main()
{
	size_t sum_of_divisors = 0;
	unsigned long i = 0;
	unsigned long number = 7777777777;
	
	#pragma omp parallel for reduction(+ : sum_of_divisors)
	
		for(i = 1 ; i <= number; ++i)
		{
		      if (0 == number % i)
		      {
		          sum_of_divisors += i;
		      }
		}
    
	printf("%lu\n", sum_of_divisors);
	
	
	return 0;
}

