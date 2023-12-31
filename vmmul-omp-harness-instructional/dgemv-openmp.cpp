#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {
   
   #pragma omp parallel for
   for(int i = 0; i < n; i++)
   {
      double productSum = 0;
      int rowStart = n * i; //inspired by presentation of Marco Lorenz

      #pragma omp parallel for reduction (+:productSum)
      for(int j = 0; j < n; j++)
      {
         productSum += x[j] * A[rowStart + j];
      }
      y[i] += productSum;
   }
}

