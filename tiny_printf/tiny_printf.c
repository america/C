#include <stdio.h>  /* putchar */
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <stdlib.h>

int tiny_printf(const char *fmt, ...)
{
  va_list pvar;
  va_start(pvar, fmt);
  while(*fmt != '\0'){
    if(*fmt != '%'){
      putchar(*fmt);  /* %d以外はそのまま出力 */
    } else if(*++fmt == 'd'){
      putchar('0' + va_arg(pvar, int));
    } else {
      return -1;
    }
    fmt++;
  }
  va_end(pvar);
  return 0;
}

int main(void)
{
  if((tiny_printf("hello: \n")) == -1){
    perror("tiny_printf");
    exit(EXIT_FAILURE); 
  }
  if((tiny_printf("hello: %d\n", 1)) == -1){
    perror("tiny_printf");
    exit(EXIT_FAILURE); 
  }
  if((tiny_printf("hello: %d %d\n", 1 ,2)) == -1){
    perror("tiny_printf");
    exit(EXIT_FAILURE); 
  }
  exit(EXIT_SUCCESS);

}

