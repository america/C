#include <stdio.h>

int main(void)
{
  int data[] = {2, 9, 7, 100, 77, 22, 11, 82, 33, 66};
  int i;

  fprintf(stdout, "before\n");

  for(i = 0; i < 10; i++){
    fprintf(stdout, "%d\n", data[i]);
  }  

  /*quick_sort(data, sizeof(data));*/
  quick_sort(data, 10);

  fprintf(stdout, "after\n");

  for(i = 0; i < 10; i++){
    fprintf(stdout, "%d\n", data[i]);
  }  

  return 0;
}
