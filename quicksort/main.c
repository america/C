#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "quicksort.h"

#define LENGTH 2000000
 
int main(void)
{
  int data[LENGTH];
  int i;

  clock_t start, stop;
  double diff;

  struct rusage usage;
  struct timeval ut1, ut2;
  struct timeval st1, st2;

  for(i = 0; i < LENGTH; i++){
    data[i] = rand();
  }

  /*
  fprintf(stdout, "before\n");

  for(i = 0; i < LENGTH; i++){
    fprintf(stdout, "%d,", data[i]);
  }  
  fprintf(stdout, "\n");
  */

  fprintf(stdout, "----------\n");
  getrusage(RUSAGE_SELF, &usage );
  ut1 = usage.ru_utime;
  st1 = usage.ru_stime;
  start = clock();

  quick_sort(data, LENGTH);

  stop = clock();
  getrusage(RUSAGE_SELF, &usage );
  ut2 = usage.ru_utime;
  st2 = usage.ru_stime;

  diff = (double)(stop - start) / CLOCKS_PER_SEC;
  fprintf(stdout, "clock 関数 で計測: %lf[sec]\n", diff);
  printf("user time = %lf\n", (ut2.tv_sec - ut1.tv_sec) + (ut2.tv_usec - ut1.tv_usec)*1.0E-6);
  printf("sys  time = %lf\n", (st2.tv_sec - st1.tv_sec) + (st2.tv_usec - st1.tv_usec)*1.0E-6);

  fprintf(stdout, "----------\n");

  /*
  fprintf(stdout, "after\n");

  for(i = 0; i < LENGTH; i++){
    fprintf(stdout, "%d,", data[i]);
  }  
  */

  return 0;
}
