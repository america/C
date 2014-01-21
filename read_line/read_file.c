#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "read_line.h"

#define ALLOC_SIZE 256

char **add_line(char **text_data, char *line,
                int *line_alloc_num, int *line_num)
{
  assert(*line_alloc_num >= *line_num);
  if(*line_alloc_num == *line_num){
    text_data = realloc(text_data,
                        (*line_alloc_num + ALLOC_SIZE) + sizeof(char *));
    *line_alloc_num += ALLOC_SIZE;
  }
  text_data[*line_num] = line;
  (*line_num)++;

  return text_data;
}

char **read_file(FILE *fp, int *line_num_p)
{
  char **text_data = NULL;
  int line_num = 0;
  int line_alloc_num = 0;
  char *line;

  while((line = read_line(fp)) != NULL){
    text_data = add_line(text_data, line,
                         &line_alloc_num, &line_num);
  }
  /* text_dataを本当に必要なサイズまで縮める */
  text_data = realloc(text_data, line_num * sizeof(char*));
  *line_num_p = line_num;

  return text_data;
}
