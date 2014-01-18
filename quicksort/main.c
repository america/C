#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "quicksort.h"

#define LENGTH 2000000
 
int main(void)
{
  int data[LENGTH];
  int i;

  clock_t start, stop;
  double diff;

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
  start = clock();
  quick_sort(data, LENGTH);
  stop = clock();

  diff = (double)(stop - start) / CLOCKS_PER_SEC;
  fprintf(stdout, "clock 関数 で計測: %lf[sec]\n", diff);

  fprintf(stdout, "----------\n");

  /*
  fprintf(stdout, "after\n");

  for(i = 0; i < LENGTH; i++){
    fprintf(stdout, "%d,", data[i]);
  }  
  */

  return 0;
}
