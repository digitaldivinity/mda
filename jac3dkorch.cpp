/* Jacobi-3 program */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mda.h"
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define KORCH_TESTING
typedef float fType;

int i, j, k, it;
fType eps;
fType MAXEPS = (fType)0.5;

int main(int an, char **as)
{
  int L = atoi(as[1]);
  int ITMAX = atoi(as[2]);

	int dim[3]={L,L,L};
	Mda<fType,3> A(dim);
	Mda<fType,3> B(dim);
	
  double startt, endt;

  for (i = 0; i < L; i++)
    for (j = 0; j < L; j++)
      for (k = 0; k < L; k++) {
        A(i,j,k) = 0;
        if (i == 0 || j == 0 || k == 0 || i == L - 1 || j == L - 1 || k == L - 1)
          B(i,j,k) = 0;
        else
          B(i,j,k) = 4 + i + j + k;
      }
      
     #ifndef KORCH_TESTING
     for (i = 0; i < L; i++)
    for (j = 0; j < L; j++)
      for (k = 0; k < L; k++)
      B(i,j,k)=L*L*i+L*j+k;
      for (i = 0; i < L; i++)
    for (j = 0; j < L; j++)
      for (k = 0; k < L; k++)
      printf("B(%d,%d,%d)=%lf\n",i,j,k,B(i,j,k));
     #endif
  startt = omp_get_wtime();
  /* iteration loop */
  for (it = 1; it <= ITMAX; it++){
    eps = 0;
    
    for (i = 1; i < L - 1; i++)
      for (j = 1; j < L - 1; j++)
        for (k = 1; k < L - 1; k++) {
          fType tmp = fabs(B(i,j,k) - A(i,j,k));
          eps = Max(tmp, eps);
          A(i,j,k) = B(i,j,k);
        }
        
    for (i = 1; i < L - 1; i++)
      for (j = 1; j < L - 1; j++)
        for (k = 1; k < L - 1; k++)
          B(i,j,k) =
            (A(i - 1,j,k) + A(i, j - 1, k) +
             A(i, j ,k - 1) + A(i , j ,k + 1) +
             A(i ,j + 1 , k) + A(i + 1, j, k)) / (fType)6.0;
       
    printf(" IT = %4i   EPS = %14.7E\n", it, eps);
    if (eps < MAXEPS)
      break;
  }
  endt = omp_get_wtime();

  printf(" Jacobi3D Benchmark Completed.\n");
  printf(" Size            = %4d x %4d x %4d\n", L, L, L);
  printf(" Iterations      =       %12d\n", ITMAX);
  printf(" Time in seconds =       %12.2lf\n", endt - startt);

  printf(" END OF Jacobi3D Benchmark\n");

  //delete [] A;
  //delete [] B;
  return 0;
}
