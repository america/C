#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"

int main(void)
{
  char **text_data;
  int line_num;
  int i;
  FILE *fp;
  char *fname = "read_file.h";

  fp = fopen(fname, "r");
  if(fp == NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  text_data = read_file(fp, &line_num);

  for(i = 0; i < line_num; i++){
    printf("%s\n", text_data[i]);
  }

  return 0;
}
